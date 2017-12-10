# Create DEB

```
$ sudo apt-get install dh-make
$ mkdir ~/markit
$ cd markit
$ wget https://github.com/willmarkley/Markit/archive/1.1.tar.gz
$ mv 1.1.tar.gz markit-1.1.tar.gz
$ tar -xzvf markit-1.1.tar.gz
$ mv Markit-1.1 markit-1.1
$ cd markit-1.1
$ dh_make -e willjmarkley@gmail.com -c mit -f ../markit-1.1.tar.gz         # Select 's' as type of package
$ cd debian
$ rm *ex *EX README.* control copyright
$ cp ../pkg/deb/control .
$ cp ../pkg/deb/copyright .
$ dkpg-buildpackage -us -uc


```

[Debian Packaging Intro](https://wiki.debian.org/IntroDebianPackaging)  
[Debian Package Maintainers Guide](https://www.debian.org/doc/manuals/maint-guide/)  
