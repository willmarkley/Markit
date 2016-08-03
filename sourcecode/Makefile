CC=		g++
FLAGS=		-lSDL2 -lSDL2_ttf
SOURCE=		markit.cpp
TARGET=		markit
PREFIX=		$(DESTDIR)/usr
BINDIR=		$(PREFIX)/bin

all:	$(TARGET)

$(TARGET): $(SOURCE)
	$(CC) -o $(TARGET) $(SOURCE) $(FLAGS)

install: $(TARGET)
	install -D $(TARGET) $(BINDIR)/$(TARGET)

uninstall:
	-rm $(BINDIR)/$(TARGET)

clean:
	rm -f $(TARGET)
