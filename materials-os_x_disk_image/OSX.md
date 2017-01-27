# OS X

# Create Executable (.app)
## Create markit.out

```
g++ -Wl,-headerpad_max_install_names -F "/Library/Frameworks/" -framework SDL2 -framework SDL2_ttf markit.cpp -o markit.out
install_name_tool -id @executable_path/../Frameworks/SDL2.framework/Versions/A/SDL2 Markit.app/Contents/Frameworks/SDL2.framework/Versions/A/SDL2
install_name_tool -id @executable_path/../Frameworks/SDL2_ttf.framework/Versions/A/SDL2_ttf Markit.app/Contents/Frameworks/SDL2_ttf.framework/Versions/A/SDL2_ttf
install_name_tool -change @rpath/SDL2.framework/Versions/A/SDL2 @executable_path/../Frameworks/SDL2.framework/Versions/A/SDL2 Markit.app/Contents/MacOS/markit.out
install_name_tool -change @rpath/SDL2_ttf.framework/Versions/A/SDL2_ttf @executable_path/../Frameworks/SDL2_ttf.framework/Versions/A/SDL2_ttf Markit.app/Contents/MacOS/markit.out
install_name_tool -change @rpath/SDL2.framework/Versions/A/SDL2 @executable_path/../Frameworks/SDL2.framework/Versions/A/SDL2 Markit.app/Contents/Frameworks/SDL2_ttf.framework/Versions/A/SDL2_ttf
install_name_tool -change @rpath/FreeType.framework/Versions/A/FreeType @executable_path/../Frameworks/SDL2_ttf.framework/Frameworks/FreeType.framework/Versions/A/FreeType Markit.app/Contents/Frameworks/SDL2_ttf.framework/Versions/A/SDL2_ttf
```

## Markit.app Structure

```
Markit.app
  --Content
    --Info.plist
    --Frameworks
      --SDL2_ttf.framework
      --SDL2.framework
    --MacOS
      --markit.out
    --Resources
      --cour.ttf
      --Markit.icns
```


# Create Disk Image
