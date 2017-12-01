Set-up:
```
$ mkdir ~/markit
$ cd markit
$ wget https://github.com/willmarkley/Markit/archive/1.1.tar.gz
$ mv 1.1.tar.gz markit-1.1.tar.gz
$ tar -xzvf markit-1.1.tar.gz
$ cd Markit-1.0
$ dh_make -f ../markit-1.1.tar.gz
```
Select the type of package you want: s

Download the control file to `debian/` directory  
