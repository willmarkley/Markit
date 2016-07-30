/*
	markit.cpp
	William Markley
*/

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sys/stat.h>
using namespace std;

bool init_graphics(SDL_Window**, SDL_Renderer**, string, string, bool);   // initializes graphics
bool init_text(TTF_Font**, bool);                                         // initializes text
SDL_Rect create_box(int, int);                                            // creates box with standard width and height
bool write_file(vector<string>, string, string);                          // writes data to .txt file
bool open_file(string, string, vector<string>&, vector<SDL_Rect>&, vector<SDL_Surface*>&, TTF_Font*); // opens a file
string get_home_path();                                                   // acquires home path if it exists
bool file_exists(string, string);                                         // checks if filename exists
string generate_window_title(string, string, bool);                       // generates window title
void key_mouse_click(vector<string>, int&, int&, int, int);               // determines position after left mouse click
bool subwindow_save_as(string, string&, bool);                            // subwindow to "Save As"
bool subwindow_exit_without_saving(string);                               // subwindow for exiting without saving
bool subwindow_open_file(string, string&);                                // subwindow to open file

#define BOX_HEIGHT 12
#define BOX_WIDTH 7
#define BOX_OFFSET_X 5
#define BOX_OFFSET_Y 2
#define TAB_LENGTH 4
#define SAVE_AS false
#define OPEN true

int main(int argc, char* argv[]) {	
	SDL_Window *window     = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Texture *screen    = NULL;
	TTF_Font *font         = NULL;
	SDL_Event event;
	SDL_Rect box           = create_box(0,0);
	SDL_Rect highlight_box = box;
	
	SDL_Color text_color      = {0,0,0,255};
	SDL_Color bg_color        = {255,255,255,255};
	SDL_Color highlight_color = {176,196,222,255};
	
	vector<string> line;
	vector<SDL_Rect> line_box;
	vector<SDL_Surface*> line_surface;
	string highlight_char;
	SDL_Surface *highlight = NULL;
	
	// highlighted position
	int row    = 0;
	int column = 0;
	
	bool QUIT  = false;
	bool SAVED = true;
	bool saved_change_state = false;
	bool new_file = true;
	bool initial  = true;
	string temp_filename;
	string filename = "untitled.txt";
	string path     = get_home_path();
	
	// initialize graphics and check for failure
	if (!init_graphics(&window, &renderer, path, filename, true)){
		return 1;
	}

	// initializes text and check for failure
	if (!init_text(&font, true)){
		return 1;
	}
	
	// initialize starting filename
	if(subwindow_open_file(path, filename)){             // true if file is to be opened
		temp_filename=filename;
		if(!(subwindow_save_as(path, filename, OPEN))){  // failed to get new filename: start with new file
			filename=temp_filename;
		}
		else{// proceed with open
			if(open_file(path, filename, line, line_box, line_surface, font)){         // successfully opened file
				new_file = false;
			}
			else{                                        // failed to get open file: start with new file
				filename=temp_filename;
			}
		}
	}
	if(new_file){ // start with new file
		int count=1;
		filename = "untitled.txt";
		while(file_exists(path,filename)){
			filename="untitled-"+to_string(count)+".txt";
			count++;
		}
		// initialize lines, line boxes, and line surfaces
		line.push_back("");
		line_box.push_back(box);
		line_surface.push_back(TTF_RenderText_Shaded(font, " ", text_color, bg_color));
	}
	SDL_SetWindowTitle(window,generate_window_title(filename,path,SAVED).c_str());
	
	// enable text input
	SDL_StartTextInput();
		
	// capture events until window is closed
	while (!QUIT){	
		while (SDL_PollEvent(&event)){
			if(saved_change_state){
				SDL_SetWindowTitle(window,generate_window_title(filename,path,SAVED).c_str());
				saved_change_state=false;
			}

			if(event.type!=SDL_MOUSEMOTION || initial){
				initial=false;
			
				// clear display
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
				SDL_RenderClear(renderer);
				
				// redraw lines
				if((int)line_box.size()==(int)line_surface.size()){
					for(int i=0; i<(int)line_surface.size(); i++){
						screen = SDL_CreateTextureFromSurface(renderer, line_surface[i]);
						SDL_RenderCopy(renderer, screen, NULL, &line_box[i]);
					}
				}
				
				// redraw highlight
				highlight_box.x=BOX_OFFSET_X + column*BOX_WIDTH;
				highlight_box.y=BOX_OFFSET_Y + row*BOX_HEIGHT;
				
				try{// sees if a character exists
					highlight_char=line[row].at(column);
				}
				catch (...){
					highlight_char=" ";
				}
				highlight=TTF_RenderText_Shaded(font, highlight_char.c_str(), text_color, highlight_color);
				screen = SDL_CreateTextureFromSurface(renderer, highlight);
				SDL_RenderCopy(renderer, screen, NULL, &highlight_box);
				
				SDL_RenderPresent(renderer);
			}
		
			if (event.type == SDL_QUIT){
				QUIT = true;
				break;
			}
			
			else if (event.type == SDL_TEXTINPUT){
				// add to character to line
				line[row].insert((line[row].begin()+column),event.text.text[0]);

				// update rects and surfaces
				line_box[row].w = line[row].length()*BOX_WIDTH;
				line_surface[row]=TTF_RenderText_Shaded(font, line[row].c_str(), text_color, bg_color);

				// update position
				column++;

				// update save status
				if(SAVED){saved_change_state=true;}
				SAVED=false;
			}
			
			else if(event.type==SDL_MOUSEBUTTONDOWN && event.button.button==SDL_BUTTON_LEFT){
				key_mouse_click(line, row, column, event.button.x, event.button.y);		
			}
			
			else if(event.type == SDL_KEYDOWN){
				switch(event.key.keysym.sym){
					case SDLK_RETURN:
						// insert new row
						line.insert((line.begin()+row+1), "");
						line_box.insert((line_box.begin()+row+1),box);
						line_surface.insert(line_surface.begin()+row+1, (TTF_RenderText_Shaded(font, " ", text_color, bg_color)));
	
						// before end of line when enter is pressed
						if (column<(int)line[row].size()){
							// copy column through end of line to the new row
							for(int i=column; i<((int)line[row].size()); i++){
								line[row+1]+=line[row].at(i);
							}
		
							// delete the copied characters from the old row
							line[row].erase(line[row].begin()+column, line[row].end());
							
							// update rects and surfaces (row was already updated)
							line_box[row].w = line[row].length()*BOX_WIDTH;
							line_box[row+1].w = line[row+1].length()*BOX_WIDTH;
							line_surface[row]=TTF_RenderText_Shaded(font, line[row].c_str(), text_color, bg_color);
							line_surface[row+1]=TTF_RenderText_Shaded(font, line[row+1].c_str(), text_color, bg_color);
						}
	
						// update position
						row++;
						column=0;
						
						// update box y displacement
						for(int i=0; i<(int)line_box.size(); i++){
							line_box[i].y=BOX_OFFSET_Y + ((i)*BOX_HEIGHT);
						}
						
						// update save status
						if(SAVED){saved_change_state=true;}
						SAVED=false;
						break;
						
					case SDLK_BACKSPACE:
						if (column!=0){
							line[row].erase(line[row].begin()+column-1);  // backspace deletes column before current position
							column--;
						}
						else if (row!=0){
							// run through row and append to previous row
							column=(int)line[row-1].size();
							for(int i=0; i<((int)line[row].size()); i++){
								line[row-1]+=line[row].at(i);
							}
							line.erase(line.begin()+row);  // removes row that was just appended to previous row
							line_box.erase(line_box.begin()+row);
							line_surface.erase(line_surface.begin()+row);
							row--;
						}// if row and column are 0,0, nothing is backspaced
						
						line_box[row].w = line[row].length()*BOX_WIDTH;
						line_surface[row]=TTF_RenderText_Shaded(font, line[row].c_str(), text_color, bg_color);
						
						if(SAVED){saved_change_state=true;}
						SAVED=false;
						break;
						
					case SDLK_DELETE:
						if (column<((int)line[row].size())){
							line[row].erase(line[row].begin()+column);  // deletes letter in column of current position
							line_box[row].w = line[row].length()*BOX_WIDTH;
							line_surface[row]=TTF_RenderText_Shaded(font, line[row].c_str(), text_color, bg_color);
						}

						if(SAVED){saved_change_state=true;}
						SAVED=false;
						break;
						
					case SDLK_UP:
						if(row!=0){ // if cursor is not against top of window
							row--;
							if(column>(int)line[row].size()){  // moves cursor left if column above is shorter
								column=(int)line[row].size();
							}
						}
						break;
						
					case SDLK_DOWN:
						if (row<((int)line.size()-1)){  // if cursor is above bottom row
							row++;
							if(column>((int)line[row].size())){  // moves cursor left if column below is shorter
								column=((int)line[row].size());
							}
						}
						break;
					case SDLK_RIGHT:
						if (column<(int)line[row].size()){ // if cursor is before space one after end of line  (MAX column is equal to row size)
							column++;
						}
						break;
					case SDLK_LEFT:
						if(column>0){ // if cursor is not against left edge of window
							column--;
						}
						break;
					case SDLK_TAB:
						for(int i=0; i<TAB_LENGTH; i++){
							line[row].insert((line[row].begin()+column),' ');
						}
						column+=TAB_LENGTH;
						line_box[row].w = line[row].length()*BOX_WIDTH;
						line_surface[row]=TTF_RenderText_Shaded(font, line[row].c_str(), text_color, bg_color);
						break;
						
					case SDLK_ESCAPE:
						QUIT=true;
						break;
						
					case SDLK_HOME:
						column=0;
						break;
						
					case SDLK_END:
						column=line[row].size();
						break;
						
					case SDLK_F1:
						if(write_file(line, filename, path)){						
							if(!SAVED){saved_change_state=true;}
							SAVED=true;
						}
						break;
					
					case SDLK_F2:
						temp_filename=filename;
						if(!(subwindow_save_as(path, filename, SAVE_AS))){
							filename=temp_filename;
						}
						else{
							if(write_file(line, filename, path)){
								SAVED=true;				
							}
							saved_change_state=true;
						}
						break;
						
					default:
						break;
						
				}
			}
		}
	}	
	
	// disable text input
	SDL_StopTextInput();	
	
	if(!SAVED){
		if(!subwindow_exit_without_saving(path)){
			bool finished=false;
			while(!finished){
				finished=write_file(line, filename, path);
			}
		}
	}
	
	// free Memory
	for(int i=0; i<(int)line_surface.size(); i++){
		SDL_FreeSurface(line_surface[i]);
	}
	SDL_DestroyTexture(screen);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
	return 0;
}

bool init_graphics(SDL_Window **w, SDL_Renderer **r, string path, string filename, bool first_time){
	// initialize all SDL subsystems
	if(first_time){
		if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
			return false;
		}
	}

	// create window
	if(first_time){
		*w = SDL_CreateWindow(generate_window_title(filename,path,true).c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_RESIZABLE);
	}
	else{
		*w = SDL_CreateWindow("Markit Alert Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 200, 0);
	}

	// check if window could not be created
	if (w == NULL){
		return false;
	}

	// create renderer
	*r = SDL_CreateRenderer(*w, -1, SDL_RENDERER_ACCELERATED);
	
	// check if renderer could not be created
	if (r == NULL){
		return false;
	}
	
	//set background color
	SDL_SetRenderDrawColor(*r, 255, 255, 255, 255);
	SDL_RenderClear(*r);
	SDL_RenderPresent(*r);

	// successful initilization
	return true;
}

bool init_text(TTF_Font **f, bool first_time){
	// initialize SDL_ttf
	if(first_time){
		if (TTF_Init() == -1){
			return false;
		}
	}

	// create font
	*f=TTF_OpenFont("cour.ttf", 12);
	
	// check if font could not be created
	if (f==NULL){
		return false;
	}
	
	// successful initilization
	return true;
	
}

SDL_Rect create_box(int yPosition, int xPosition){
	SDL_Rect box;
	box.x=BOX_OFFSET_X + (xPosition*BOX_WIDTH);
	box.y=BOX_OFFSET_Y + (yPosition*BOX_HEIGHT);
	box.w=BOX_WIDTH;
	box.h=BOX_HEIGHT;
	return box;
}

string get_home_path(){
	string path;
	char *cpath=NULL;
	char *cpath2=NULL;
	bool path_found = false;
	
	// find path to home environment
	cpath=getenv("HOME");   // linux and unix
	
	if(cpath!=NULL){        // linux/unix path found
		string spath(cpath);
		path=spath+"/";
		path_found=true;
	}
	else {
		cpath=getenv("HOMEDRIVE");         // windows drive
		if(cpath!=NULL){                   // windows drive found
			cpath2=getenv("HOMEPATH");     // windows path
			if(cpath!=NULL){               // windows path found
				string spath(cpath);
				string spath2(cpath2);
				path=spath+spath2+"\\";
				path_found=true;
			}
		}
	}
	
	if(!path_found){
		path="";
	}

	return path;
}

bool file_exists(string path, string filename){	
	string path_filename=path+filename;
	struct stat buffer;
	return (stat(path_filename.c_str(), &buffer)==0);
}

string generate_window_title(string filename, string path, bool saved){
	string title="";
	
	title+="Markit   -   "+path+filename+" - ";
	if(saved){
		title+="Saved:    F2=\"Save As\"";
	}
	else{
		title+="Unsaved:    F1=\"Save\"  F2=\"Save As\"";
	}
	
	return title;
}

bool write_file(vector<string> data, string filename, string path){
	char letter;
	string error;
	bool content_on_last=true;
	int last_row=data.size()-1;
	
	string path_filename=path+filename;
	
	// creates or overwrites file
	ofstream outfile;
	outfile.open(path_filename, ios::trunc);
	
	if(!outfile.is_open()){ return false; }
		
	// writes all data except the last row
	for(int i=0; i<last_row; i++){
		outfile << data[i];
		outfile << '\n';
	}
	
	// checks for data in the last row
	try{
		letter = data[last_row].at(0);
	}
	catch (const out_of_range& oor){
		content_on_last=false;
		error=oor.what();
	}
	
	// writes last row if there is content
	if(content_on_last){
		outfile << data[last_row];
	}

	outfile.close();
	return true;
}

bool open_file(string path, string filename, vector<string> &line, vector<SDL_Rect> &line_box, vector<SDL_Surface*> &line_surface, TTF_Font *font){
	string path_filename  = path+filename;
	SDL_Rect box          = create_box(0,0);
	SDL_Color text_color  = {0,0,0,255};
	SDL_Color bg_color    = {255,255,255,255};
	string line_from_file;
	
	// opens file
	ifstream infile;
	infile.open(path_filename,ios::in);
	
	if(!infile.is_open()){ return false; }
	
	while (getline(infile, line_from_file)){
		// converts tabs to spaces
		for(int i=0; i<(int)line_from_file.length(); i++){
			if(line_from_file.at(i)==9){
				line_from_file.erase(i,1);
				for(int j=0; j<TAB_LENGTH; j++){
					line_from_file.insert((line_from_file.begin()+i),' ');
				}
			}
		}
		line.push_back(line_from_file);
		
		box.w=line[(int)line.size()-1].length()*BOX_WIDTH;
		box.y=BOX_OFFSET_Y + ((int)line.size()-1)*BOX_HEIGHT;
		line_box.push_back(box);
		
		line_surface.push_back(TTF_RenderText_Shaded(font, line[(int)line.size()-1].c_str(), text_color, bg_color));
	}
	
	
	infile.close();
	return true;
}

void key_mouse_click(vector<string> line, int &row, int &column, int xPos, int yPos){
	// account for offset
	xPos-=BOX_OFFSET_X;
	yPos-=BOX_OFFSET_Y;
					
	// find x position (integer division is intentional)
	xPos=xPos/BOX_WIDTH;
	yPos=yPos/BOX_HEIGHT;

	if (yPos<(int)line.size()){
		if (xPos<=(int)line[yPos].size()){
			row=yPos;
			column=xPos;
		}
	}
}

bool subwindow_exit_without_saving(string path){
	SDL_Window *exitwindow = NULL;
	SDL_Renderer *exitrenderer = NULL;
	SDL_Texture *exitscreen = NULL;
	SDL_Surface *message[4];
	SDL_Rect box[4];

	SDL_Event event;
	SDL_Color text_color={0,0,0,255};
	SDL_Color bg_color={255,255,255,255};
	SDL_Color bg_color_box={176,196,222,255};
	TTF_Font *font = NULL;
	
	bool QUIT=false;
	bool VAL=true;
	int xPos, yPos;

	
	// initialize graphics and check for failure
	if (!init_graphics(&exitwindow, &exitrenderer, path, " ", false)){
		return VAL;
	}
	
	SDL_SetRenderDrawColor(exitrenderer, 255, 255, 255, 0);
	SDL_RenderClear(exitrenderer);
	
	// initializes text and check for failure
	if (!init_text(&font, false)){
		return VAL;
	}
		
	// fill messages and boxes
	message[0]=TTF_RenderText_Shaded(font, "Are you sure you wish to exit without saving?", text_color, bg_color);
	message[1]=TTF_RenderText_Shaded(font, " Save (F1)       ", text_color, bg_color_box);
	message[2]=TTF_RenderText_Shaded(font, " Don't Save (F2) ", text_color, bg_color_box);
	message[3]=TTF_RenderText_Shaded(font, " Please select an option ", text_color, bg_color);
	
	for(int i=0; i<4; i++){
		box[i].y=BOX_OFFSET_Y + (4)*BOX_HEIGHT;
		box[i].x=BOX_OFFSET_X + BOX_WIDTH;
		box[i].h=BOX_HEIGHT;
		box[i].w=17*BOX_WIDTH;
	}
	box[0].w=45*BOX_WIDTH;
	box[0].y=BOX_OFFSET_Y + BOX_HEIGHT;
	box[2].x=BOX_OFFSET_X + (17+11)*BOX_WIDTH;
	box[3].y=BOX_OFFSET_Y + 2*BOX_HEIGHT;
	box[3].w=25*BOX_WIDTH;
	
	for(int i=0; i<3; i++){
		exitscreen = SDL_CreateTextureFromSurface(exitrenderer, message[i]);
		SDL_RenderCopy(exitrenderer, exitscreen, NULL, &box[i]);
	}
	SDL_RenderPresent(exitrenderer);
		
	// capture events until window is closed
	while (!QUIT){
		while (SDL_PollEvent(&event)){
			if (event.type==SDL_QUIT){
				QUIT=true;
				break;
			}
			
			else if(event.type==SDL_WINDOWEVENT){
				if(event.window.event==SDL_WINDOWEVENT_CLOSE){
					SDL_SetRenderDrawColor(exitrenderer, 255, 255, 255, 0);
					SDL_RenderClear(exitrenderer);
					for(int i=0; i<4; i++){
						exitscreen = SDL_CreateTextureFromSurface(exitrenderer, message[i]);
						SDL_RenderCopy(exitrenderer, exitscreen, NULL, &box[i]);
					}
					SDL_RenderPresent(exitrenderer);
				}
			}
			
			else if(event.type==SDL_MOUSEBUTTONDOWN){
				if (event.button.button==SDL_BUTTON_LEFT){
					xPos=event.button.x;
					yPos=event.button.y;
					
					// click is in valid y range
					if ( (yPos>=(BOX_OFFSET_Y + (4)*BOX_HEIGHT)) && (yPos<(BOX_OFFSET_Y + (5)*BOX_HEIGHT)) ){
						
						// click is on save button
						if( (xPos>=(BOX_OFFSET_X + BOX_WIDTH)) && (xPos<(BOX_OFFSET_X + 18*BOX_WIDTH)) ){
							QUIT=true;
							VAL=false;
							break;
						}
						
						// click is on don't save button
						else if( (xPos>=(BOX_OFFSET_X + (17+11)*BOX_WIDTH)) && (xPos<(BOX_OFFSET_X + (45)*BOX_WIDTH)) ){
							QUIT=true;
							break;
						}
					}
				}
			}
			
			else if(event.type == SDL_KEYDOWN){
				switch(event.key.keysym.sym){
					case SDLK_F1:
						QUIT=true;
						VAL=false;
						break;
					case SDLK_F2:
						QUIT=true;
						break;
				}
			}
		}
	}
		
	for(int i=0; i<4; i++){
		SDL_FreeSurface(message[i]);
	}
	SDL_DestroyTexture(exitscreen);
	SDL_DestroyRenderer(exitrenderer);
	SDL_DestroyWindow(exitwindow);
	TTF_CloseFont(font);
	return VAL;	
}

bool subwindow_save_as(string path, string &filename, bool open){
	SDL_Window *subwindow = NULL;
	SDL_Renderer *subrenderer = NULL;
	SDL_Texture *subscreen = NULL;
	SDL_Surface *message[8];
	SDL_Rect box[8];

	SDL_Event event;
	SDL_Color text_color={0,0,0,255};
	SDL_Color bg_color={255,255,255,255};
	SDL_Color highlight_color={176,196,222,255};
	TTF_Font *font = NULL;
	
	bool QUIT=false;
	bool SUCCESS_VAL=false;
	string user_input=".txt";
	int position=0;
	string highlight_char;
	int invalid_chars[10] = {34, 42, 47, 58, 60, 62, 63, 92, 124, 126};  // " * / : < > ? \ | ~
	int ascii_value;
	string path2;
	
	// initialize graphics and check for failure
	if (!init_graphics(&subwindow, &subrenderer, path, " ", false)){
		return false;
	}
	
	SDL_SetRenderDrawColor(subrenderer, 255, 255, 255, 0);
	SDL_RenderClear(subrenderer);
	
	// initializes text and check for failure
	if (!init_text(&font, false)){
		return false;
	}
	
	// fill messages and boxes
	if(open){  // opening file prompt
		message[0]=TTF_RenderText_Shaded(font, "Please type the name of the file to open.      ", text_color, bg_color);
	}
	else{      // save as file prompt
		message[0]=TTF_RenderText_Shaded(font, "Please type a new filename under 30 characters.", text_color, bg_color);
	}
	message[1]=TTF_RenderText_Shaded(font, "   Press enter when finished.                  ", text_color, bg_color);
	message[2]=TTF_RenderText_Shaded(font, "   Close window to cancel.                     ", text_color, bg_color);
	path2="Path:  "+path;
	const char * c_string=path2.c_str();
	message[3]=TTF_RenderText_Shaded(font, c_string, text_color, bg_color);
	
	for(int i=0; i<4; i++){
		box[i].y=BOX_OFFSET_Y + (i+1)*BOX_HEIGHT;
		box[i].x=BOX_OFFSET_X + BOX_WIDTH;
		box[i].w=47*BOX_WIDTH;
		box[i].h=BOX_HEIGHT;
	}
	box[3].w=strlen(c_string)*BOX_WIDTH;
	
	// text box outline (box 4)
	int MAX_SIZE=255-strlen(c_string);
	if (MAX_SIZE>30){
		MAX_SIZE=30;
	}
	box[4].w=(MAX_SIZE+1)*BOX_WIDTH +5;
	box[4].h=BOX_HEIGHT+2;
	box[4].x=BOX_OFFSET_X + BOX_WIDTH;
	box[4].y=BOX_OFFSET_Y + 6*BOX_HEIGHT;
	message[4]=TTF_RenderText_Solid(font, " ", text_color);
	
	// user_input box (box 5)
	box[5].y=BOX_OFFSET_Y + 6*BOX_HEIGHT +1;
	box[5].x=BOX_OFFSET_X + BOX_WIDTH +2;
	box[5].h=BOX_HEIGHT;
	
	// highlight box (box 6)
	box[6].y=BOX_OFFSET_Y + 6*BOX_HEIGHT +1;
	box[6].x=BOX_OFFSET_X + BOX_WIDTH +2;
	box[6].w=BOX_WIDTH;
	box[6].h=BOX_HEIGHT;
	message[6]=TTF_RenderText_Solid(font, " ", text_color);
	
	// warning box
	box[7].y=BOX_OFFSET_Y + 8*BOX_HEIGHT +1;
	box[7].x=BOX_OFFSET_X + BOX_WIDTH;
	box[7].w=45*BOX_WIDTH;
	box[7].h=BOX_HEIGHT;
	message[7]=TTF_RenderText_Shaded(font, "                                             ", text_color, bg_color);

	// enable text input
	SDL_StartTextInput();
	
	// capture events until window is closed
	while (!QUIT){
		while (SDL_PollEvent(&event)){
			if(event.type!=SDL_MOUSEMOTION){
				// redraw display
				SDL_SetRenderDrawColor(subrenderer, 255, 255, 255, 0);
				SDL_RenderClear(subrenderer);
				
				box[5].w=(user_input.length()*BOX_WIDTH);
				message[5]=TTF_RenderText_Shaded(font, user_input.c_str(), text_color, bg_color);
				
				box[6].x=BOX_OFFSET_X+2+((position+1)*BOX_WIDTH);
				try{// sees if a character exists
					highlight_char=user_input.at(position);
				}
				catch (...){
					highlight_char=" ";
				}
				message[6]=TTF_RenderText_Shaded(font, highlight_char.c_str(), text_color, highlight_color);
				
				for(int i=0; i<4; i++){
					subscreen = SDL_CreateTextureFromSurface(subrenderer, message[i]);
					SDL_RenderCopy(subrenderer, subscreen, NULL, &box[i]);
				}
				
				SDL_SetRenderDrawColor(subrenderer, 0, 0, 0, 255);
				SDL_RenderDrawRect(subrenderer, &box[4]);
				
				for(int i=4; i<8; i++){
					subscreen = SDL_CreateTextureFromSurface(subrenderer, message[i]);
					SDL_RenderCopy(subrenderer, subscreen, NULL, &box[i]);
				}
				
				SDL_RenderPresent(subrenderer);
			}
			if (event.type==SDL_QUIT){
				QUIT=true;
				break;
			}
			else if(event.type==SDL_WINDOWEVENT){
				if(event.window.event==SDL_WINDOWEVENT_CLOSE){
					QUIT=true;
					break;
				}
			}
			else if (event.type == SDL_TEXTINPUT){
				// add character to string		
				if((int)user_input.length()<MAX_SIZE){
					ascii_value=(int)event.text.text[0];
					bool invalid=false;
					for(int i=0; i<10; i++){
						if(ascii_value==invalid_chars[i]){
							invalid=true;
						}
					}
					if(invalid){
						message[7]=TTF_RenderText_Shaded(font, "Invalid Character                            ", text_color, bg_color);
					}
					else{  // all valid characters
						user_input.insert(user_input.cbegin()+position,event.text.text[0]);
						position++;
						message[7]=TTF_RenderText_Shaded(font, "                                             ", text_color, bg_color);
					}
				}
			}
			else{
				if (event.type == SDL_KEYDOWN){
					message[7]=TTF_RenderText_Shaded(font, "                                             ", text_color, bg_color);
					switch(event.key.keysym.sym){
						case SDLK_RETURN:
							if(!open){  // save as mode
								// check to see if file exists (reserved filenames are found to exist)
								if (file_exists(path,user_input)){
									message[7]=TTF_RenderText_Shaded(font, "File Already Exists:  Please try another name", text_color, bg_color);
								}
								else{
									QUIT=true;
									filename=user_input;
									SUCCESS_VAL=true;
								}
							}
							else{ // opening a file
								// check to see if file exists (reserved filenames are found to exist)
								if (file_exists(path,user_input)){
									QUIT=true;
									filename=user_input;
									SUCCESS_VAL=true;
								}
								else{
									message[7]=TTF_RenderText_Shaded(font, "File Does Not Exist:  Please try another name", text_color, bg_color);
								}
							}
							
							break;
						
						case SDLK_BACKSPACE:  // deletes character before position
							if(position!=0){
								user_input.erase(position-1,1);
								// update position
								position--;
							}
							break;
							
						case SDLK_DELETE:
							if (position<(int)user_input.length()){
								user_input.erase(position,1);  // deletes letter in current position
							}
							break;
							
						case SDLK_RIGHT:
							if (position<(int)user_input.length()){
								position++;
							}
							break;
						
						case SDLK_LEFT:
							if(position>0){
								position--;
							}
							break;
						
						case SDLK_HOME:
							position=0;
							break;
						
						case SDLK_END:
							position=(int)user_input.length();
							break;
						default:
							break;
					}
				}
			}
		}
	}
	
	for(int i=0; i<8; i++){
		SDL_FreeSurface(message[i]);
	}
	SDL_DestroyTexture(subscreen);
	SDL_DestroyRenderer(subrenderer);
	SDL_DestroyWindow(subwindow);
	TTF_CloseFont(font);
	return SUCCESS_VAL;	
}

bool subwindow_open_file(string path, string &filename){
	SDL_Window *exitwindow = NULL;
	SDL_Renderer *exitrenderer = NULL;
	SDL_Texture *exitscreen = NULL;
	SDL_Surface *message[4];
	SDL_Rect box[4];

	SDL_Event event;
	SDL_Color text_color   = {0,0,0,255};
	SDL_Color bg_color     = {255,255,255,255};
	SDL_Color bg_color_box = {176,196,222,255};
	TTF_Font *font = NULL;
	
	bool QUIT=false;
	bool OPENED_FILE=false;
	int xPos, yPos;

	
	// initialize graphics and check for failure
	if (!init_graphics(&exitwindow, &exitrenderer, path, " ", false)){
		return OPENED_FILE;
	}
	
	SDL_SetRenderDrawColor(exitrenderer,255,255,255,255);
	SDL_RenderClear(exitrenderer);
	
	// initializes text and check for failure
	if (!init_text(&font, false)){
		return OPENED_FILE;
	}
		
	// fill messages and boxes
	message[0]=TTF_RenderText_Shaded(font, "   New File (F1)    ", text_color, bg_color_box);
	message[1]=TTF_RenderText_Shaded(font, " Open Existing (F2) ", text_color, bg_color_box);
	message[2]=TTF_RenderText_Shaded(font, " Please select an option ", text_color, bg_color);
	
	for(int i=0; i<3; i++){
		box[i].y=BOX_OFFSET_Y + (2)*BOX_HEIGHT;
		box[i].x=BOX_OFFSET_X + BOX_WIDTH;
		box[i].h=BOX_HEIGHT;
		box[i].w=20*BOX_WIDTH;
	}
	box[1].x=BOX_OFFSET_X + (20+5)*BOX_WIDTH;
	box[2].y=BOX_OFFSET_Y + 4*BOX_HEIGHT;
	box[2].w=25*BOX_WIDTH;
	
	for(int i=0; i<2; i++){
		exitscreen = SDL_CreateTextureFromSurface(exitrenderer, message[i]);
		SDL_RenderCopy(exitrenderer, exitscreen, NULL, &box[i]);
	}
	SDL_RenderPresent(exitrenderer);
	
	// capture events until window is closed
	while (!QUIT){
		while (SDL_PollEvent(&event)){
			if (event.type==SDL_QUIT){
				QUIT=true;
				break;
			}
			
			else if(event.type==SDL_WINDOWEVENT){
				if(event.window.event==SDL_WINDOWEVENT_CLOSE){
					SDL_SetRenderDrawColor(exitrenderer, 255, 255, 255, 0);
					SDL_RenderClear(exitrenderer);
					for(int i=0; i<3; i++){
						exitscreen = SDL_CreateTextureFromSurface(exitrenderer, message[i]);
						SDL_RenderCopy(exitrenderer, exitscreen, NULL, &box[i]);
					}
					SDL_RenderPresent(exitrenderer);
				}
			}
			
			else if(event.type==SDL_MOUSEBUTTONDOWN){
				if (event.button.button==SDL_BUTTON_LEFT){
					xPos=event.button.x;
					yPos=event.button.y;
					
					// click is in valid y range
					if ( (yPos>=(BOX_OFFSET_Y + (2)*BOX_HEIGHT)) && (yPos<(BOX_OFFSET_Y + (3)*BOX_HEIGHT)) ){
						
						// click is on new button
						if( (xPos>=(BOX_OFFSET_X + BOX_WIDTH)) && (xPos<(BOX_OFFSET_X + 21*BOX_WIDTH)) ){
							QUIT=true;
							break;
						}
						
						// click is on open button
						else if( (xPos>=(BOX_OFFSET_X + (20+5)*BOX_WIDTH)) && (xPos<(BOX_OFFSET_X + (45)*BOX_WIDTH)) ){
							QUIT=true;
							OPENED_FILE=true;
							break;
						}
					}
				}
			}
			
			else if(event.type == SDL_KEYDOWN){
				switch(event.key.keysym.sym){
					case SDLK_F1:
						QUIT=true;
						break;
					case SDLK_F2:
						QUIT=true;
						OPENED_FILE=true;
						break;
				}
			}
		}
	}
		
	for(int i=0; i<3; i++){
		SDL_FreeSurface(message[i]);
	}
	SDL_DestroyTexture(exitscreen);
	SDL_DestroyRenderer(exitrenderer);
	SDL_DestroyWindow(exitwindow);
	TTF_CloseFont(font);
	return OPENED_FILE;	
}
