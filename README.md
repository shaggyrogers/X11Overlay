# README #

This is a very basic library for drawing an overlay using X11 and cairo. A wrapper (Overlay.cs) is provided so that it can be easily used in C# projects.

Tested and working on Ubuntu 16.10.

### Issues ###
The main issues are:

* Does not draw over fullscreen applications
* Overlay windows have title bars
* No ability to select one particular window to draw over

### Compiling ###
cd to project directory. "make" will build the library, "make test" will build both the library and test program.

### Usage ###
* Initialise by creating an instance of the XOverlay class, or calling Overlay.init() if the C# wrapper is used. Call the setWindowMap method if drawing over a window with a fixed position and dimensions is desired.
* In the main drawing loop, clear the overlay each frame using the clear() method, add objects to draw using the corresponding add method, and then use the draw() method when finished.

### TODO ###
* List dependencies
* Allow drawing over fullscreen applications
* Allow for drawing over a given window, automatically updating position and dimensions

### License ###
See Licence.md