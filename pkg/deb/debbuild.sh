#!/bin/bash

# Setup build and download source
# sudo apt-get install dh-make libsdl2-dev libsdl2-ttf-dev
# mkdir ~/markit
# cd markit
wget https://github.com/willmarkley/Markit/archive/1.1.tar.gz
tar -xzf 1.1.tar.gz
rm 1.1.tar.gz
mv Markit-1.1 markit-1.1
sed -i -e 's/cour.ttf/\/usr\/share\/markit\/cour.ttf/' markit-1.1/src/markit.cpp
tar -czf markit-1.1.tar.gz markit-1.1/

# Setup debian package format
cd markit-1.1
echo -e "s\n" | dh_make -e willjmarkley@gmail.com -c mit -f ../markit-1.1.tar.gz       # Select 's' as type of package

# Modify the debian/ files
rm debian/*ex debian/*EX debian/README.* debian/control debian/copyright 
cp pkg/deb/control debian
cp pkg/deb/copyright debian

# Build package
dpkg-buildpackage -us -uc
