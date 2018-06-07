all: lib clean

test: maketest clean

lib: X11Overlay.o Drawing.o cswrapper.o
	g++ -shared -o libxoverlay.so cswrapper.o Drawing.o X11Overlay.o -lX11 -lXfixes -lXcomposite -lcairo

X11Overlay.o: X11Overlay.h
	g++ -fPIC -c X11Overlay.cpp 

Drawing.o: Drawing.h
	g++ -fPIC -c Drawing.cpp

cswrapper.o: cswrapper.h
	g++ -fPIC -c cswrapper.cpp

clean:
	rm X11Overlay.o Drawing.o cswrapper.o #main.o

main.o: X11Overlay.o
	g++ -c main.cpp 

maketest: main.o lib
	g++ Drawing.o X11Overlay.o main.o -o main -lX11 -lXfixes -lXcomposite -lcairo
	rm main.o
