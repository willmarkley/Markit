# Create RPM

Run the following as root user:

```
$ sudo dnf install fedora-packager @development-tools
$ sudo usermod -a -G mock wmarkley
```

Run the following from non-root user:

```
$ rpmdev-setuptree

# download markit.spec and rpm_rebuild.sh
$ wget -O ~/rpmbuild/SPECS/markit.spec https://raw.githubusercontent.com/willmarkley/Markit/master/pkg/rpm/markit.spec
$ wget -O ~/rpmbuild/rpm_rebuild.sh https://raw.githubusercontent.com/willmarkley/Markit/master/pkg/rpm/rpm_rebuild.sh

# Note: `init_text` function modified to have cour.ttf absolute path in source .tar.gz
#    *f=TTF_OpenFont("cour.ttf", 12);    -->     *f=TTF_OpenFont("/usr/share/markit/cour.ttf", 12);

$ ./rpm_rebuild.sh
```

Test install as root:

```
# rpm -ivp markit-1.1-1.x86_64.rpm
```

Unistall as root:

```
# rpm -e markit
```


### References
[How to create an RPM](https://fedoraproject.org/wiki/How_to_create_an_RPM_package)  
[How to create a GNU Hello RPM](https://fedoraproject.org/wiki/How_to_create_a_GNU_Hello_RPM_package)  
