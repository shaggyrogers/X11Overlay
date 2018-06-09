# README

This is a very basic library for drawing over other windows using a transparent overlay window.
It supports Linux distributions using X11. Wayland is not supported directly, but this should work with XWayland.
This has been tested on Ubuntu 17.10 only.

I originally used this as part of cheat software for the game Rust. See my post [here](https://www.unknowncheats.me/forum/general-programming-and-reversing/202747-external-w2s-guide.html) for information on implementing 3D projection in software.

## Dependencies

* [Cairo](https://cairographics.org/)
* Xlib
    - libXfixes
    - libXcomposite

For Ubuntu 17.10:

    sudo apt-get update; sudo apt-get install -y libcairo2 libcairo2-dev libcairo2-doc libx11-6 libx11-dev libx11-doc libxfixes3 libxfixes-dev libxcomposite1 libxcomposite-dev

## Compilation

    git clone https://github.com/shaggyrogers/X11Overlay.git
    cd X11Overlay/
    make

* "make" will build the library
* "make test" will build both the library and test program

## Usage

TODO

## Known Issues

The main issues are:

* Does not draw over fullscreen applications
* Overlay windows have title bars
* Flickering still an issue
* No ability to select one particular window to draw over

## TODO

* Clean up and refactor
* Add unit & integration tests
* Add Vector2, Vector3 structs
* Use singleton
* Add Python interface, C# and Python examples
* Allow drawing over fullscreen applications
* Ignore window manager, no title bar etc.
* Fix flickering issue
* Allow for drawing over a given window, automatically updating position and dimensions

## License

MIT - see LICENSE.md
