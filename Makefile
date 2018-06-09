all: lib clean

test: lib maketest clean

lib: build/X11Overlay.o build/Drawing.o build/libxoverlay.o
	g++ -shared -o bin/libxoverlay.so build/libxoverlay.o build/Drawing.o build/X11Overlay.o -lX11 -lXfixes -lXcomposite -lcairo

build/X11Overlay.o: src/X11Overlay.h
	g++ -fPIC -c src/X11Overlay.cpp -o build/X11Overlay.o

build/Drawing.o: src/Drawing.h
	g++ -fPIC -c src/Drawing.cpp -o build/Drawing.o

build/libxoverlay.o: src/libxoverlay.h
	g++ -fPIC -c src/libxoverlay.cpp -o build/libxoverlay.o

maketest: build/main.o
	g++ build/Drawing.o build/X11Overlay.o build/main.o -o bin/main -lX11 -lXfixes -lXcomposite -lcairo

build/main.o: build/X11Overlay.o
	g++ -c src/main.cpp -o build/main.o

clean:
	rm build/*
