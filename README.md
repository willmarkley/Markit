# Markit

Markit is a cross platform plain-text editor developed in C++ by William Markley.  It offers the ability to open, edit, and write files composed of ASCII characters.  The application relies on the SDL2 and SDL2_ttf graphics libraries to render pixels to the screen.  This desktop application is packaged for Windows(.exe), OS X(.app), RPM Linux, and Debian Linux.  Markit is installed via an .rpm (RPM Linux), .deb (Debian Linux), disk image (OS X), or installer (Windows).


###User Manual

#####Key Strokes for Main Window
**RETURN:**	     Adds new line to document  
**BACKSPACE:**   Deletes the character in the position before your current position  
**DELETE:**      Deletes the character at your current position  
**UP Arrow:**    Moves position up 1 line if available  
**DOWN Arrow:**  Moves position down 1 line if available  
**LEFT Arrow:**  Moves position left 1 position if available  
**RIGHT Arrow:** Moves position right 1 position if available  
**TAB:**         Inserts TAB_LENGTH(4) spaces at current position  
**ESC:**         Closes Window  
**HOME:**        Moves position to beginning of current line  
**END:**         Moves position to end of current line  
**F1:**          Save File  
**F2:**          Save File As  
**MOUSE Left Click:**  Moves position to position clicked by mouse (if valid position)  
**TEXTUAL INPUT:**     Adds the given input to the screen  
#####Key Strokes for Sub Windows
Blue Boxes are clickable buttons.  
**F1:**    Selects Left Boxes  
**F2:**    Selects Right Boxes  


###Download Instructions:

#####Windows
1. Download [Markit-1.0-Setup](http://willmarkley.com/markit/Markit-1.0-Setup.exe)
2. Run the installer

To Uninstall:  Run the Markit uninstaller under the Markit folder in the start menu

#####OS X
1. Download [Markit-1.0.dmg](http://willmarkley.com/markit/Markit-1.0.dmg)
2. Drag Markit.app to Applications Folder

If you are given a security warning when trying to run:

1. Right click Markit.app
2. Select Open
3. Select Yes in the dialog box

To Unistall: Drag Markit.app to the Trash

#####Linux - Debian

#####Linux - Fedora



###Assets (Licensed for non-commercial distribution)
[SDL2 library](https://www.libsdl.org/download-2.0.php)  
[SDL2 TTF library](https://www.libsdl.org/projects/SDL_ttf/)  
[Markit Icon](http://www.iconeasy.com/icon/letter-m-icon/)  
[Courier True Type Font](https://github.com/caarlos0/msfonts/blob/master/fonts/cour.ttf)  


###Known Issues
Inability to scroll when text leaves screen.  Text is still saved and can be viewed by expanding the screen.


 
