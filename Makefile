all: lib clean

test: lib maketest clean

# Library
lib: mk_dirs build/X11Overlay.o build/Drawing.o build/libxoverlay.o
	g++ -shared -o bin/libxoverlay.so build/libxoverlay.o build/Drawing.o build/X11Overlay.o -lX11 -lXfixes -lXcomposite -lcairo

mk_dirs:
	mkdir -p build bin

build/X11Overlay.o:
	g++ -fPIC -c src/X11Overlay.cpp -o build/X11Overlay.o

build/Drawing.o:
	g++ -fPIC -c src/Drawing.cpp -o build/Drawing.o

build/libxoverlay.o:
	g++ -fPIC -c src/libxoverlay.cpp -o build/libxoverlay.o

# Test program
maketest: build/main.o
	g++ build/Drawing.o build/X11Overlay.o build/main.o -o bin/main -lX11 -lXfixes -lXcomposite -lcairo

build/main.o: build/X11Overlay.o
	g++ -c src/main.cpp -o build/main.o

# Python interface
python: lib
	g++ -c src/interfaces/python/overlay.cpp -std=c++17 -fPIC -o build/overlay.o `pkg-config --cflags --libs python3 cairo xfixes xcomposite`
	g++ build/Drawing.o build/X11Overlay.o build/overlay.o -shared -o bin/overlay.so `pkg-config --cflags --libs python3 cairo xfixes xcomposite`

clean:
	rm -r build
