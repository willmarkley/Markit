Name:           markit
Version:        1.1 
Release:        1
Summary:        Cross Platform Plain-Text editor

LICENSE:        MIT
URL:            https://github.com/willmarkley/Markit
GROUP:          Applications/Editors
Source0:        https://github.com/willmarkley/Markit/archive/1.1.tar.gz

BuildRequires:  gcc-c++ 
BuildRequires:  SDL2-devel
BuildRequires:  SDL2_ttf-devel
Requires:       SDL2
Requires:       SDL2_ttf

%description
Markit is a cross-platform plain text editor developed in C++ by William Markley
Offers the ability to open, edit, and write files composed of ASCII characters

%prep
%autosetup -n Markit-1.1

%build
cd src
sed -i -e 's/cour.ttf/\/usr\/share\/markit\/cour.ttf/' markit.cpp 
make

%install
rm -rf $RPM_BUILD_ROOT
%make_install

%files
%{_bindir}/markit
/usr/share/applications/markit.desktop
/usr/share/pixmaps/markit.png
/usr/share/markit/cour.ttf


%changelog
* Thu Nov 30 2017 William Markley
- Set sources to be github release

* Tue Aug  2 2016 William Markley
- Initial