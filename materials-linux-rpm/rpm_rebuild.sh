rm -rf /home/wmarkley/rpmbuild/BUILDROOT
rm -rf /home/wmarkley/rpmbuild/BUILD/markit-1.0/
rm -rf /home/wmarkley/rpmbuild/RPMS/x86_64/
rm -rf /home/wmarkley/rpmbuild/SRPMS/markit-1.0-1.src.rpm
rm -f /home/wmarkley/rpmbuild/SOURCES/markit-1.0.tar.gz
cd SOURCES
wget http://willmarkley.com/markit-1.0.tar.gz
cd ../SPECS
rpmbuild -ba markit.spec
rpmlint markit.spec ../RPMS/x86_64/markit-1.0-1.x86_64.rpm ../SRPMS/markit-1.0-1.src.rpm

