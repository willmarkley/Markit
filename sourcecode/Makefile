CC=		g++
FLAGS=		-lSDL2 -lSDL2_ttf
SOURCES=	markit.cpp
TARGETS=	markit
PREFIX=		$(DESTDIR)/usr/local
BINDIR=		$(PREFIX)/bin

all:	$(TARGETS)

$(TARGETS): $(SOURCES)
	$(CC) -o $(TARGETS) $(SOURCES) $(FLAGS)

install: markit
	install -D $(TARGET) $(BINDIR)/$(TARGET)

uninstall:
	-rm $(BINDIR)/$(TARGET)

clean:
	rm -f $(TARGETS)
