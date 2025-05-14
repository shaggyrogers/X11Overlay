/*
   libxoverlay.cpp
   ===============

   Description:           Implements functions exported by libxoverlay.so.
   Author:                Michael De Pasquale <shaggyrogers>
   Creation Date:         2016-12-04
   Modification Date:     2025-05-14
   License:               MIT
*/

#include "libxoverlay.h"

extern "C" {

// Initialise
void init()
{
    overlay = new XOverlay();
}

// Clears the list of things to draw
void clear()
{
    overlay->clear();
}

// Maps all drawing to an area with the given size and offset.
void setWindowMap(float x, float y, float width, float height)
{
    overlay->setWindowMap(x, y, width, height);
}

// Clears the current window map
void clearWindowMap()
{
    overlay->clearWindowMap();
}

// Add items to draw
void addText(char* string, float x, float y, float size, float r, float g,
    float b, float a, bool centered)
{
    overlay->addText(string, x, y, size, r, g, b, a, centered);
}

void addLine(float x1, float y1, float x2, float y2, float r,
    float g, float b, float a, float lineWidth)
{
    overlay->addLine(x1, y1, x2, y2, r, g, b, a, lineWidth);
}

void addRectangle(float x1, float y1, float x2, float y2, float r, float g,
    float b, float a, bool filled, float lineWidth)
{
    overlay->addRectangle(x1, y1, x2, y2, r, g, b, a, filled, lineWidth);
}

void addTriangle(float x1, float y1, float x2, float y2, float x3, float y3,
    float r, float g, float b, float a, bool filled, float lineWidth)
{
    overlay->addTriangle(x1, y1, x2, y2, x3, y3, r, g, b, a, filled,
        lineWidth);
}

void addCircle(float x, float y, float radius, float r, float g, float b,
    float a, bool filled, float lineWidth)
{
    overlay->addCircle(x, y, radius, r, g, b, a, filled, lineWidth);
}

// Draw everything
void draw()
{
    overlay->draw();
}

// Get width, height
int getWidth()
{
    return overlay->getWidth();
}

int getHeight()
{
    return overlay->getHeight();
}

// Call when exiting
void cleanup()
{
    overlay->cleanup();
}

} // extern "C"
