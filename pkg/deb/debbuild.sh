#!/bin/bash

# Setup build and download source
sudo apt-get install dh-make libsdl2-dev libsdl2-ttf-dev
mkdir ~/markit
cd markit
wget https://github.com/willmarkley/Markit/archive/1.1.tar.gz
tar -xzvf 1.1.tar.gz
mv Markit-1.1 markit-1.1
sed -i -e 's/cour.ttf/\/usr\/share\/markit\/cour.ttf/' markit-1.1/src/markit.cpp
tar -czvf markit-1.1.tar.gz markit-1.1/

# Setup debian package format
cd markit-1.1
dh_make -e willjmarkley@gmail.com -c mit -f ../markit-1.1.tar.gz         # Select 's' as type of package

# Modify the debian/ files
cd debian
rm *ex *EX README.* control copyright
cp ../pkg/deb/control .
cp ../pkg/deb/copyright .
cd ..

# Build package
dpkg-buildpackage -us -uc

# Install package
sudo dpkg -i ../markit_1.1-1_amd64.deb
