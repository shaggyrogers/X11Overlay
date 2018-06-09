/* XOverlay.h */

#ifndef __XOVERLAY_H__
#define __XOVERLAY_H__

#include "Drawing.h"

#include <list>
#include <stdio.h>
#include <time.h>

/* X11 */
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xos.h>
#include <X11/Xutil.h>

/* X11 extensions */
#include <X11/extensions/Xfixes.h>
#include <X11/extensions/shape.h>

/* cairo */
#include "/usr/include/cairo/cairo-xlib.h"
#include "/usr/include/cairo/cairo.h"

class XOverlay {

private:
    std::list<IDrawable*> drawList;
    bool initialised = false;
    int width, height;
    int num = 0; /* Window number */

    /* X11 */
    Display* display;
    Window window[2];
    int screen;

    /* cairo */
    cairo_surface_t* surface[2];
    cairo_t* context[2];

    /* Window map */
    bool mapActive = false;
    float mapX, mapY;
    float mapWidth, mapHeight;

    /* Creates a window. Returns true if successful. */
    bool createWindow(Display* display, int width, int height, Window* outWindow, cairo_surface_t** outSurface,
        cairo_t** outContext);

    /* Takes a screen point and maps it to the window. */
    void mapToWindow(float& x, float& y);

public:
    /* Iniitalise */
    XOverlay();

    /* Clears the list of things to draw. */
    void clear();

    /* Maps all drawing to an area with the given size and offset. */
    void setWindowMap(float x, float y, float width, float height);

    /* Clears the current window map */
    void clearWindowMap();

    /* Add items to draw */
    void addText(char* string, float x, float y, float size, float r, float g, float b, float a, bool centered);
    void addLine(float x1, float y1, float x2, float y2, float r, float g, float b, float a, float lineWidth);
    void addRectangle(float x1, float y1, float x2, float y2, float r, float g, float b, float a, bool filled, float lineWidth);
    void addTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b, float a,
        bool filled, float lineWidth);
    void addCircle(float x, float y, float radius, float r, float g, float b, float a, bool filled, float lineWidth);

    /* Draws everything; call this every 5ms */
    void draw();

    /* Get overlay width and height */
    int getWidth() { return width; }
    int getHeight() { return height; }

    /* Call when exiting */
    void cleanup();
};

#endif /* __XOVERLAY_H__ */
