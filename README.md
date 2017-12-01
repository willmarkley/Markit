# Markit
[![Build Status](https://travis-ci.org/willmarkley/Markit.svg?branch=master)](https://travis-ci.org/willmarkley/Markit)  


Markit is a cross platform plain-text editor developed in C++ by William Markley.  It offers the ability to open, edit, and write files composed of ASCII characters.  The application relies on the SDL2 and SDL2_ttf graphics libraries to render pixels to the screen.  This desktop application is packaged for Windows(.exe), OS X(.app), RPM Linux, and Debian Linux.  Markit is installed via an .rpm (RPM Linux), .deb (Debian Linux), disk image (OS X), or installer (Windows).

![markit1](https://raw.githubusercontent.com/willmarkley/willmarkley.com/master/img/markit1.png)  
![markit2](https://raw.githubusercontent.com/willmarkley/willmarkley.com/master/img/markit2.png)  
![markit3](https://raw.githubusercontent.com/willmarkley/willmarkley.com/master/img/markit3.png)  
![markit4](https://raw.githubusercontent.com/willmarkley/willmarkley.com/master/img/markit4.png)  
![markit5](https://raw.githubusercontent.com/willmarkley/willmarkley.com/master/img/markit5.png)  
![markit6](https://raw.githubusercontent.com/willmarkley/willmarkley.com/master/img/markit6.png)  


### User Manual

##### Key Strokes for Main Window
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
##### Key Strokes for Sub Windows
Blue Boxes are clickable buttons.  
**F1:**    Selects Left Boxes  
**F2:**    Selects Right Boxes  


### Installation Instructions:

##### Windows
1. Download [Markit-1.0-Setup](https://github.com/willmarkley/Markit/releases/download/1.0/Markit-1.0-Setup.exe)
2. Run the installer

To Uninstall: Run the Markit uninstaller under the Markit folder in the start menu

##### OS X
1. Download [Markit-1.0.dmg](https://github.com/willmarkley/Markit/releases/download/1.0/Markit-1.0.dmg)
2. Drag Markit.app to Applications Folder

If you are given a security warning when trying to run:

1. Right click Markit.app
2. Select Open
3. Select Yes in the dialog box

To Unistall: Drag Markit.app to the Trash

##### Linux - Debian

<!---
markit-1.0-.deb
--->

##### Linux - Fedora
1. Download [markit-1.0-1.x86_64.rpm](https://github.com/willmarkley/Markit/releases/download/1.0/markit-1.0-1.x86_64.rpm)
2. Open RPM with Software Installer and press "Install"

To Unistall: Open the Software application and press "Remove" next to Markit

To Install on Terminal: `sudo dnf install ~/Downloads/markit-1.0-1.x86_64.rpm`  
To Uninstall on Terminal: `sudo dnf remove markit`


### Assets (Licensed for non-commercial distribution)
[SDL2 library](https://www.libsdl.org/download-2.0.php)  
[SDL2 TTF library](https://www.libsdl.org/projects/SDL_ttf/)  
[Markit Icon](http://www.iconeasy.com/icon/letter-m-icon/)  
[Courier True Type Font](https://github.com/caarlos0/msfonts/blob/master/fonts/cour.ttf)  


### Known Issues
Inability to scroll when text leaves screen.  Text is still saved and can be viewed by expanding the screen.


 
