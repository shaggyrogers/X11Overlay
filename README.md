# README

This is a very basic library for drawing text and simple shapes over other windows using a transparent overlay window.
It supports Linux distributions using X11 only.
This has been tested on Ubuntu 24.04 (use a "Ubuntu on Xorg" session)

I originally used this as part of cheat software for the game Rust. See my post [here](https://www.unknowncheats.me/forum/general-programming-and-reversing/202747-external-w2s-guide.html) for information on implementing 3D projection in software. This is now part of my [external aimbot project](https://github.com/shaggyrogers/external-aimbot).

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
* "make test" will build the test program (main.cpp)
* "make python" will build the python interface (overlay.so)

## Usage

See python example script

## Issues

* Overlay window might flicker
* Misc. minor bugs
  - Colors are incorrectly reset by overlapping elements
  - Unfilled circles are incorrectly drawn with a radial line
  - Does not seem to clear previous elements if nothing is drawn?

## TODO

* Fix bugs
* Cleanup/refactor
* Add tests

## License

MIT - see LICENSE.md
