CC = gcc
CFLAGS = -I/opt/X11/include $(shell pkg-config --cflags imlib2)
LDFLAGS = -L/opt/X11/lib $(shell pkg-config --libs imlib2) -lX11
#CFLAGS ?= -ggdb -g3 # For debugging

all: brunch

install: brunch
	mkdir -p $(DESTDIR)/etc/brunch/
	mkdir -p $(DESTDIR)/usr/share/brunch/svgicons/
	mkdir -p $(DESTDIR)/usr/bin/
	mkdir -p $(DESTDIR)/usr/share/icons/hicolor/48x48/apps
	mkdir -p $(DESTDIR)/usr/share/applications
	cp extra/ghost.png $(DESTDIR)/usr/share/icons/hicolor/48x48/apps/brunch_ghost.png
	cp docs/logo.png $(DESTDIR)/usr/share/icons/hicolor/48x48/apps/brunch.png
	cp brunch $(DESTDIR)/usr/bin/
	cp extra/genentries $(DESTDIR)/usr/bin
	cp extra/gentriesquick $(DESTDIR)/usr/bin/brunch_genquick
	cp extra/updateentries $(DESTDIR)/usr/bin
	cp extra/genentries.desktop.sh $(DESTDIR)/usr/bin
	cp extra/genentries.desktop $(DESTDIR)/usr/share/applications/
	cp default.conf $(DESTDIR)/etc/brunch/default.conf
	bash extra/genentries --path $(DESTDIR)/usr/share/brunch/svgicons/ > $(DESTDIR)/etc/brunch/entries.dsv
	cp -r svgicons/ $(DESTDIR)/usr/share/brunch/ 2>/dev/null || :

remove:
	rm -r $(DESTDIR)/etc/brunch
	rm -r $(DESTDIR)/usr/share/brunch
	rm $(DESTDIR)/usr/bin/brunch
	rm $(DESTDIR)/usr/bin/genentries
	rm $(DESTDIR)/usr/bin/updateentries
	rm $(DESTDIR)/usr/bin/genentries.desktop.sh
	rm $(DESTDIR)/usr/share/icons/hicolor/48x48/apps/brunch_ghost.png
	rm $(DESTDIR)/usr/share/icons/hicolor/48x48/apps/brunch.png
	rm $(DESTDIR)/usr/share/applications/genentries.desktop

livetest: brunch
	./extra/gentriesquick > /tmp/brunch-tmp.dsv
	./brunch -g extra/wp.jpg -f "extra/OpenSans-Regular.ttf/10" -i /tmp/brunch-tmp.dsv -b 140 --iconpadding 20 --textpadding 10 --paddingswap --leastmargin 10 --scroll || true
	rm -f /tmp/brunch-tmp.dsv

test: brunch
	./brunch -g extra/wp.jpg -f "extra/OpenSans-Regular.ttf/10" -i extra/sample_entries.dsv -b 140 --outputonly --iconpadding 20 --textpadding 10 --paddingswap --leastmargin 10 --highlight extra/highlight.png

brunch: brunch.c
	$(CC) brunch.c -o brunch $(LDFLAGS) $(CFLAGS)

clean:
	rm -f brunch
	rm -f entries.dsv

