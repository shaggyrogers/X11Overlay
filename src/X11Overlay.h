/*
  X11Overlay.h
  ============

  Description:           TODO
  Author:                Michael De Pasquale
  Creation Date:         2016-12-04
  Modification Date:     2025-05-20

*/

#ifndef __X11OVERLAY_H__
#define __X11OVERLAY_H__

#include "Drawing.h"

#include <iostream>
#include <list>
#include <stdio.h>
#include <time.h>

#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xos.h>
#include <X11/Xutil.h>

#include <X11/extensions/Xfixes.h>
#include <X11/extensions/shape.h>

#include "/usr/include/cairo/cairo-xlib.h"
#include "/usr/include/cairo/cairo.h"

class XOverlay {

private:
    std::list<IDrawable*> drawList;
    bool initialised = false;
    int width, height;
    int num = 0; //  Window number

    // X11
    Display* display;
    Window window[2];
    int screen;

    // cairo
    cairo_surface_t* surface[2];
    cairo_t* context[2];

    // Target window offset
    bool offsetActive = false;
    int offsetX = 0;
    int offsetY = 0;

    // Creates a window. Returns true if successful.
    bool createWindow(Display* display, int width, int height, Window* outWindow, cairo_surface_t** outSurface,
        cairo_t** outContext);

    // Takes a screen point and maps it to the window.
    void mapToWindow(float& x, float& y);

public:
    // Initialise
    XOverlay();

    // Clears the list of things to draw.
    void clear();

    // Specify a window to draw over.
    // Returns true if sucessful, updating width and height with the
    // width and height of the target window. Returns false if unsuccessful.
    bool setTargetWindow(unsigned int id, int& width, int& height);

    // Maps all drawing to an area with the given size and offset.
    // Prefer setTargetWindow(), which calls this
    void setWindowOffset(int x, int y);

    // Clears the current window offset.
    void clearWindowOffset();

    // Add items to draw
    void addText(char* string, float x, float y, float size, float r, float g, float b,
        float a, bool centered);
    void addLine(float x1, float y1, float x2, float y2, float r, float g, float b,
        float a, float lineWidth);
    void addRectangle(float x1, float y1, float x2, float y2, float r, float g, float b,
        float a, bool filled, float lineWidth);
    void addTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float r,
        float g, float b, float a,
        bool filled, float lineWidth);
    void addCircle(float x, float y, float radius, float r, float g, float b, float a,
        bool filled, float lineWidth);

    // Draws everything; call this every loop
    void draw();

    // Get overlay window width and height
    int getWidth() { return width; }
    int getHeight() { return height; }

    // Call when exiting
    void cleanup();
};

#endif //  __X11OVERLAY_H__
