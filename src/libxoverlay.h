/*
   libxoverlay.h
   =============

   Description:           Functions exported by libxoverlay.so.
   Author:                Michael De Pasquale <shaggyrogers>
   Creation Date:         2016-12-04
   Modification Date:     2025-05-20
   License:               MIT
*/

#ifndef __CSWRAPPER_H__
#define __CSWRAPPER_H__

#include "X11Overlay.h"

extern XOverlay* overlay;

extern "C" void init();

extern "C" void clear();

extern "C" bool setTargetWindow(unsigned int id, int& width, int& height);

extern "C" void setWindowOffset(int x, int y);

extern "C" void clearWindowOffset();

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

extern "C" void draw();

extern "C" int getWidth();

extern "C" int getHeight();

extern "C" void cleanup();

#endif // __CSWRAPPER_H__
