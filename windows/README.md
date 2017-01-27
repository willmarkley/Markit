# Windows

# Create Executable (.exe)

## Instructions
###### Set up on Visual Studio
 1. http://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/msvsnet2010u/index.php
 2. http://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/windows/msvsnet2010u/index.php
 3. Add markit.cpp to project
 4. Add "_CRT_SECURE_NO_WARNINGS" to Preprocessor Definitions (under C/C++ > Preprocessor in Project Properties)

###### Move to release
 1. Change Configuration to Active(Release)
 2. Change Runtime Library to "Multi-threaded (/MT)" (under C/C++ > Code Generation in Project Properties)

## Executable Structure
```
Markit (directory)
  --Markit.exe
  --libfreetype-6.dll
  --SDL2.dll
  --SDL2_ttf.dll
  --zlib1.dll
  --cour.ttf
```

# Create Installer (.exe)
 1. After compiling executable, use Resource Hacker to add .ico to markit.exe.
 2. Compile the markit-1.0-setup.nsi script to achieve the installer.
 3. Be sure to include the icon, License, and executable folder structure(.exe, .ttf, .dlls) files in the proper places.


### References
http://hmne.sourceforge.net/  
http://download.cnet.com/Resource-Hacker/3000-2352_4-10178587.html  
