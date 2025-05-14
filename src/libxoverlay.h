/*
   libxoverlay.h
   =============

   Description:           Functions exported by libxoverlay.so.
   Author:                Michael De Pasquale <shaggyrogers>
   Creation Date:         2016-12-04
   Modification Date:     2025-05-14
   License:               MIT
*/

#ifndef __CSWRAPPER_H__
#define __CSWRAPPER_H__

#include "X11Overlay.h"

extern XOverlay* overlay;

// Initialise
extern "C" void init();

// Clears the list of things to draw
extern "C" void clear();

// Maps all drawing to an area with the given size and offset.
extern "C" void setWindowMap(float x, float y, float width, float height);

// Clears the current window map
extern "C" void clearWindowMap();

// Add items to draw
extern "C" void addText(char* string, float x, float y, float size, float r,
    float g, float b, float a, bool centered);

extern "C" void addLine(float x1, float y1, float x2, float y2, float r,
    float g, float b, float a, float lineWidth);

extern "C" void addRectangle(float x1, float y1, float x2, float y2, float r,
    float g, float b, float a, bool filled, float lineWidth);

extern "C" void addTriangle(float x1, float y1, float x2, float y2, float x3,
    float y3, float r, float g, float b, float a, bool filled,
    float lineWidth);

extern "C" void addCircle(float x, float y, float radius, float r, float g,
    float b, float a, bool filled, float lineWidth);

// Draw everything
extern "C" void draw();

// Get width, height
extern "C" int getWidth();

extern "C" int getHeight();

// Call when exiting
extern "C" void cleanup();

#endif // __CSWRAPPER_H__
