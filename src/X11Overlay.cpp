/*
   XOverlay.cpp
   ============

   Description:           Functions exported by libxoverlay.so.
   Author:                Michael De Pasquale <shaggyrogers>
   Creation Date:         2016-12-04
   Modification Date:     2025-05-14
   License:               MIT
*/

#include "X11Overlay.h"

// Creates a window. Returns true if successful.
bool XOverlay::createWindow(Display* display, int width, int height,
    Window* outWindow, cairo_surface_t** outSurface,
    cairo_t** outContext)
{

    Window rootWindow = DefaultRootWindow(display);

    // Find visual with required depth and class
    XVisualInfo info;

    if (!XMatchVisualInfo(display, screen, 32, TrueColor, &info)) {
        printf("Error: XMatchVisualInfo failed!\n");
        return false;
    }

    // Create colormap for window
    XSetWindowAttributes attributes;
    attributes.colormap = XCreateColormap(display, rootWindow, info.visual, AllocNone);
    attributes.border_pixel = 0;
    attributes.background_pixel = 0;

    // Create windows
    Window window = XCreateWindow(display, rootWindow,
        0, 0, width, height, 0, info.depth, InputOutput, info.visual,
        CWColormap | CWBackPixel | CWBorderPixel, &attributes);

    // Create cairo surface for each window
    cairo_surface_t* surface = cairo_xlib_surface_create(display, window,
        info.visual,
        width, height);

    // create cairo drawing context
    cairo_t* context = cairo_create(surface);

    // Set window to be always on top
    Atom fsatoms[2] = { XInternAtom(display, "_NET_WM_STATE_ABOVE", False),
        None };
    XChangeProperty(display, window, XInternAtom(display, "_NET_WM_STATE", False),
        XA_ATOM, 32, PropModeReplace, (unsigned char*)fsatoms, 1);

    // Set the window to have an empty input shape
    XserverRegion region = XFixesCreateRegion(display, 0, 0);
    XFixesSetWindowShapeRegion(display, window, ShapeBounding, 0, 0, 0);
    XFixesSetWindowShapeRegion(display, window, ShapeInput, 0, 0, region);
    XFixesDestroyRegion(display, region);

    // Display window
    if (!XMapWindow(display, window)) {
        printf("Error: XMapWindow failed!\n");
        return false;
    }

    *outWindow = window;
    *outSurface = surface;
    *outContext = context;
    return true;
}

// Takes a screen point and maps it to the window.
void XOverlay::mapToWindow(float& x, float& y)
{
    if (!mapActive)
        return;

    float screenPercentX = x / (float)width;
    float screenPercentY = y / (float)height;

    x = mapWidth * screenPercentX + mapX;
    y = mapHeight * screenPercentY + mapY;
}

// Initialise
XOverlay::XOverlay()
{

    // Get Display, default screen number, default root window
    if (!(display = XOpenDisplay((char*)0))) {
        printf("Error: XOpenDisplay failed!\n");
        return;
    }

    screen = DefaultScreen(display);
    Window rootWindow = DefaultRootWindow(display);
    XWindowAttributes rootWindowAttributes;

    // Get size of default root window
    if (!XGetWindowAttributes(display, rootWindow, &rootWindowAttributes)) {
        printf("Error: XGetWindowAttributes failed!");
        return;
    }

    width = rootWindowAttributes.width;
    height = rootWindowAttributes.height;

    // Create windows
    if (!createWindow(display, width, height, &window[0], &surface[0], &context[0])) {
        printf("Error: Failed to create window 1!\n");
        return;
    }

    if (!createWindow(display, width, height, &window[1], &surface[1], &context[1])) {
        printf("Error: Failed to create window 2!\n");
        return;
    }

    initialised = true;
}

// Clears the list of things to draw.
void XOverlay::clear()
{

    for (IDrawable* drawable : drawList)
        delete drawable;

    drawList.clear();
}

// Maps all drawing to an area with the given size and offset.
void XOverlay::setWindowMap(float x, float y, float width, float height)
{
    this->mapActive = true;
    this->mapX = x;
    this->mapY = y;
    this->mapWidth = width;
    this->mapHeight = height;
}

// Clears the current window map
void XOverlay::clearWindowMap()
{
    this->mapActive = false;
}

// Add items to draw
void XOverlay::addText(char* string, float x, float y, float size, float r, float g,
    float b, float a, bool centered)
{
    mapToWindow(x, y);
    Text* text = new Text(string, x, y, size, r, g, b, a, centered);
    drawList.push_back(text);
}

void XOverlay::addLine(float x1, float y1, float x2, float y2, float lineWidth, float r,
    float g, float b, float a)
{
    mapToWindow(x1, y1);
    mapToWindow(x2, y2);
    Line* line = new Line(x1, y1, x2, y2, lineWidth, r, g, b, a);
    drawList.push_back(line);
}

void XOverlay::addRectangle(float x1, float y1, float x2, float y2, float r, float g,
    float b, float a, bool filled, float lineWidth)
{
    mapToWindow(x1, y1);
    mapToWindow(x2, y2);
    Rectangle* rectangle = new Rectangle(x1, y1, x2, y2, r, g, b, a, filled, lineWidth);
    drawList.push_back(rectangle);
}

void XOverlay::addTriangle(float x1, float y1, float x2, float y2, float x3, float y3,
    float r, float g, float b, float a, bool filled, float lineWidth)
{
    mapToWindow(x1, y1);
    mapToWindow(x2, y2);
    mapToWindow(x3, y3);
    Triangle* triangle = new Triangle(x1, y1, x2, y2, x3, y3, r, g, b, a, filled, lineWidth);
    drawList.push_back(triangle);
}

void XOverlay::addCircle(float x, float y, float radius, float r, float g, float b, float a, bool filled, float lineWidth)
{
    mapToWindow(x, y);
    Circle* circle = new Circle(x, y, radius, r, g, b, a, filled, lineWidth);
    drawList.push_back(circle);
}

// Draws everything
void XOverlay::draw()
{

    if (drawList.size() == 0)
        return;

    // Redirect all drawing to a group
    cairo_push_group(context[num]);

    // draw everything to group
    for (IDrawable* drawable : drawList)
        drawable->draw(context[num]);

    // Draw from group to window
    cairo_pop_group_to_source(context[num]);
    cairo_paint(context[num]);
    cairo_surface_flush(surface[num]);

    // Swap window number
    num = (num + 1) % 2;

    // Clear back window
    cairo_operator_t op = cairo_get_operator(context[num]);
    cairo_set_operator(context[num], CAIRO_OPERATOR_SOURCE);
    cairo_set_source_rgba(context[num], 1.0, 1.0, 1.0, 0.0f);
    cairo_paint(context[num]);
    cairo_set_operator(context[num], op);

    // Flush output buffer
    XFlush(display);
}

// Call when exiting
void XOverlay::cleanup()
{
    initialised = false;

    cairo_surface_destroy(surface[0]);
    cairo_surface_destroy(surface[1]);
    cairo_destroy(context[0]);
    cairo_destroy(context[1]);
    XCloseDisplay(display);
}
