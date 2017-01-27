# Create RPM

Run the following as root user:

```
# dnf install fedora-packager @development-tools
# usermod -a -G mock wmarkley
```

Run the following from non-root user:

```
$ rpmdev-setuptree
```

Download the .spec file to the ~/rpmbuild/SPECS directory
Download the rpm_rebuild.sh to the ~/rpmbuild/ directory
-(init_text function of source code modified for .tar.gz to have cour.ttf location)

```
$ ./rpm_rebuild.sh
```

Test install as root:

```
# rpm -ivp markit-1.0-1.x86_64.rpm
```

Unistall as root:

```
# rpm -e markit
```


### References
[How to create an RPM](https://fedoraproject.org/wiki/How_to_create_an_RPM_package)  
[How to create a GNU Hello RPM](https://fedoraproject.org/wiki/How_to_create_a_GNU_Hello_RPM_package)  