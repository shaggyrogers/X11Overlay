/*
   Drawing.h
   =========

   Description:           Defines an interface for visual elements and a set of
                          classes that implement this interface.
   Author:                Michael De Pasquale <shaggyrogers>
   Creation Date:         2016-12-04
   Modification Date:     2018-06-06
   License:               MIT
 */

#ifndef __DRAWING_H__
#define __DRAWING_H__

#include <stdio.h>
#include <string.h>

/* cairo */
#include "/usr/include/cairo/cairo-xlib.h"
#include "/usr/include/cairo/cairo.h"

#define STRING_BUF_LEN 256

enum DrawableType { /* {{{ */
    TYPE_NONE,
    TYPE_TEXT,
    TYPE_LINE,
    TYPE_RECTANGLE,
    TYPE_TRIANGLE,
    TYPE_CIRCLE
}; /* }}} */

/*  Interface for all objects  */
class IDrawable { /* {{{ */

protected:
    /* Color */
    float r, g, b, a;

public:
    /* Returns the type of the object. */
    virtual DrawableType type() { return TYPE_NONE; }

    /* Draws the object */
    virtual void draw(cairo_t* context) = 0;
}; /* }}} */

/* Text */
class Text : public IDrawable { /* {{{ */
    float x, y;
    float size;
    bool centered;
    char string[STRING_BUF_LEN];

public:
    Text(char* string, float x, float y, float size, float r, float g, float b,
        float a, bool centered);

    DrawableType type() { return TYPE_TEXT; }

    void draw(cairo_t* context);
}; /* }}} */

/* Line */
class Line : public IDrawable { /* {{{ */
    float x1, y1;
    float x2, y2;
    float lineWidth;

public:
    Line(float x1, float y1, float x2, float y2, float lineWidth, float r,
        float g, float b, float a);

    DrawableType type() { return TYPE_LINE; }

    void draw(cairo_t* context);
}; /* }}} */

/* Rectangle */
class Rectangle : public IDrawable { /*{{{*/
    float x1, y1;
    float x2, y2;
    bool filled;
    float lineWidth; /* Only used if filled is true. */

public:
    Rectangle(float x1, float y1, float x2, float y2, float r, float g, float b, float a,
        bool filled, float lineWidth);

    DrawableType type() { return TYPE_RECTANGLE; }

    void draw(cairo_t* context);
}; /*}}}*/

/* Filled Triangle */
class Triangle : public IDrawable { /*{{{*/
    float x1, y1;
    float x2, y2;
    float x3, y3;
    bool filled;
    float lineWidth; /* Only used if filled is true. */

public:
    Triangle(float x1, float y1, float x2, float y2, float x3, float y3,
        float r, float g, float b, float a, bool filled, float lineWidth);

    DrawableType type() { return TYPE_TRIANGLE; }

    void draw(cairo_t* context);
}; /*}}}*/

/* Circle */
class Circle : public IDrawable { /*{{{*/
    float x, y;
    float radius;
    bool filled;
    float lineWidth;

public:
    Circle(float x, float y, float radius, float r, float g, float b, float a, bool filled, float lineWidth);

    DrawableType type() { return TYPE_CIRCLE; }

    void draw(cairo_t* context);
}; /*}}}*/

#endif /* __DRAWING_H__ */

/* vim: set ts=4 sw=4 tw=79 fdm=marker et :*/
