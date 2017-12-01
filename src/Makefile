CXX=		g++
CXXFLAGS=	-std=c++11
LIBS=		-lSDL2 -lSDL2_ttf
SOURCE=		markit.cpp
TARGET=		markit
PREFIX=		$(DESTDIR)/usr
BINDIR=		$(PREFIX)/bin

all:	$(TARGET)

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE) $(LIBS)

install: $(TARGET)
	install -D $(TARGET) $(BINDIR)/$(TARGET)
	install -D markit.desktop $(PREFIX)/share/applications/markit.desktop
	install -D markit.png $(PREFIX)/share/pixmaps/markit.png
	install -D cour.ttf $(PREFIX)/share/markit/cour.ttf

uninstall:
	-rm $(BINDIR)/$(TARGET)
	-rm $(PREFIX)/share/applications/markit.desktop
	-rm $(PREFIX)/share/pixmaps/markit.png
	-rm $(PREFIX)/share/markit/cour.ttf

clean:
	rm -f $(TARGET)
