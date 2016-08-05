Name:           markit
Version:        1.0 
Release:        1
Summary:        Cross Platform Plain-Text editor

LICENSE:        MIT
URL:            http://willmarkley.com/markit/
GROUP:          Applications/Editors
Source0:        http://willmarkley.com/markit/markit-1.0.tar.gz

BuildRequires:  gcc-c++ 
BuildRequires:  SDL2-devel
BuildRequires:  SDL2_ttf-devel
Requires:       SDL2
Requires:       SDL2_ttf

%description
Markit is a cross-platform plain text editor developed in C++ by William Markley
Offers the ability to open, edit, and write files composed of ASCII characters

%prep
%autosetup


%build
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
* Tue Aug  2 2016 William Markley
- 
