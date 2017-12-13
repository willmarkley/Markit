CXX=		g++
CXXFLAGS=	-std=c++11
LIBS=		-lSDL2 -lSDL2_ttf
SRCDIR=		src/
BUILDDIR=	build/
SOURCE=		markit.cpp
TARGET=		markit
PREFIX=		$(DESTDIR)/usr
BINDIR=		$(PREFIX)/bin

all:	$(BUILDDIR)$(TARGET)

$(BUILDDIR)$(TARGET): $(SRCDIR)$(SOURCE)
	mkdir -p $(BUILDDIR)
	cd $(BUILDDIR) && ln -s ../$(SRCDIR)/cour.ttf cour.ttf && cd ..
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)$(TARGET) $(SRCDIR)$(SOURCE) $(LIBS)

install: $(BUILDDIR)$(TARGET)
	install -D $(BUILDDIR)$(TARGET) $(BINDIR)/$(TARGET)
	install -D $(SRCDIR)markit.desktop $(PREFIX)/share/applications/markit.desktop
	install -D $(SRCDIR)markit.png $(PREFIX)/share/pixmaps/markit.png
	install -D $(SRCDIR)cour.ttf $(PREFIX)/share/markit/cour.ttf

uninstall:
	-rm $(BINDIR)/$(TARGET)
	-rm $(PREFIX)/share/applications/markit.desktop
	-rm $(PREFIX)/share/pixmaps/markit.png
	-rm $(PREFIX)/share/markit/cour.ttf

clean:
	rm -rf $(BUILDDIR)
