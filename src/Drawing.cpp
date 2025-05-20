/*
   Drawing.cpp
   =========

   Description:           Implements methods defined in Drawing.h
   Author:                Michael De Pasquale <shaggyrogers>
   Creation Date:         2016-12-04
   Modification Date:     2025-05-20
   License:               MIT
*/

#include "Drawing.h"

Text::Text(char* string, float x, float y, float size, float r, float g,
    float b, float a, bool centered)
{
    /* Copy string */
    int len = strlen(string);

    if (len >= STRING_BUF_LEN) {
        len = STRING_BUF_LEN - 1;
    }

    memcpy(this->string, string, len);
    this->string[len] = '\x00';

    /* Copy the rest of the arguments */
    this->x = x;
    this->y = y;
    this->size = size;
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
    this->centered = centered;
}

void Text::draw(cairo_t* context)
{
    cairo_text_extents_t te;

    cairo_set_source_rgba(context, r, g, b, a);
    cairo_select_font_face(context, "Arial", CAIRO_FONT_SLANT_NORMAL,
        CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(context, size);
    cairo_text_extents(context, string, &te);

    if (centered) {
        cairo_move_to(context, x - te.width / 2 - te.x_bearing,
            y - te.height / 2 - te.y_bearing);
    } else {
        cairo_move_to(context, x - te.x_bearing,
            y - te.y_bearing);
    }

    cairo_show_text(context, string);
}

Line::Line(float x1, float y1, float x2, float y2, float r, float g,
    float b, float a, float lineWidth)
{
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
    this->lineWidth = lineWidth;
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

void Line::draw(cairo_t* context)
{
    cairo_set_line_width(context, lineWidth);
    cairo_set_source_rgba(context, r, g, b, a);
    cairo_move_to(context, x1, y1);
    cairo_line_to(context, x2, y2);
    cairo_stroke(context);
}

Rectangle::Rectangle(float x1, float y1, float x2, float y2, float r, float g,
    float b, float a, bool filled, float lineWidth)
{
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
    this->filled = filled;
    this->lineWidth = lineWidth;
}

void Rectangle::draw(cairo_t* context)
{
    if (!filled) {
        cairo_set_line_width(context, lineWidth);
    }

    cairo_set_source_rgba(context, r, g, b, a);
    cairo_rectangle(context, x1, y1, x2 - x1, y2 - y1);

    if (!filled) {
        cairo_stroke(context);
        return;
    }

    cairo_fill(context);
}

Triangle::Triangle(float x1, float y1, float x2, float y2, float x3, float y3,
    float r, float g, float b, float a, bool filled, float lineWidth)
{
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
    this->x3 = x3;
    this->y3 = y3;
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
    this->filled = filled;
    this->lineWidth = lineWidth;
}

void Triangle::draw(cairo_t* context)
{
    if (!filled)
        cairo_set_line_width(context, lineWidth);

    cairo_set_source_rgba(context, r, g, b, a);
    cairo_move_to(context, x1, y1);
    cairo_line_to(context, x2, y2);
    cairo_line_to(context, x3, y3);
    cairo_line_to(context, x1, y1);

    if (!filled) {
        cairo_stroke(context);

        return;
    }

    cairo_fill(context);
}

Circle::Circle(float x, float y, float radius, float r, float g, float b,
    float a, bool filled, float lineWidth)
{
    this->x = x;
    this->y = y;
    this->radius = radius;
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
    this->filled = filled;
    this->lineWidth = lineWidth;
}

void Circle::draw(cairo_t* context)
{
    if (!filled) {
        cairo_set_line_width(context, lineWidth);
    }

    // FIXME: This draws an unwanted line from the center?
    cairo_set_source_rgba(context, r, g, b, a);
    cairo_move_to(context, x, y);
    cairo_arc(context, x, y, radius, 0.0, 6.28318);

    if (!filled) {
        // cairo_stroke(context);

        return;
    }

    cairo_fill(context);
}
