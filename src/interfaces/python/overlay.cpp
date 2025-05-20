/*
  overlay.cpp
  ===========

  Description:           Python interface.
  Author:                Michael De Pasquale
  Creation Date:         2025-05-14
  Modification Date:     2025-05-20

*/

#define PY_SSIZE_T_CLEAN
#define MODULE_NAME "overlay"

#include "../../X11Overlay.h"
#include <Python.h>
#include <iostream>

XOverlay* overlay = NULL;

static PyObject* overlay_init(PyObject* self, PyObject* args)
{
    if (!PyArg_ParseTuple(args, "")) {
        PyErr_SetString(PyExc_TypeError, "Unexpected arguments");

        return NULL;
    }

    if (overlay) {
        PyErr_SetString(PyExc_RuntimeError, "init() called twice!");

        return NULL;
    }

    overlay = new XOverlay();

    return Py_BuildValue("");
}

static PyObject* overlay_clear(PyObject* self, PyObject* args)
{
    if (!PyArg_ParseTuple(args, "")) {
        PyErr_SetString(PyExc_TypeError, "Unexpected arguments");

        return NULL;
    }

    overlay->clear();

    return Py_BuildValue("");
}

static PyObject* overlay_setTargetWindow(PyObject* self, PyObject* args)
{
    unsigned int id;

    if (!PyArg_ParseTuple(args, "I", &id)) {
        PyErr_SetString(PyExc_TypeError, "Failed to parse arguments");

        return NULL;
    }

    int width = 0, height = 0;

    if (!overlay->setTargetWindow(id, width, height)) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to set target window!");

        return NULL;
    }

    return PyTuple_Pack(2, PyLong_FromLong(width), PyLong_FromLong(height));
}

static PyObject* overlay_setWindowOffset(PyObject* self, PyObject* args)
{
    int x, y;

    if (!PyArg_ParseTuple(args, "ii", &x, &y)) {
        PyErr_SetString(PyExc_TypeError, "Failed to parse arguments");

        return NULL;
    }

    overlay->setWindowOffset(x, y);

    return Py_BuildValue("");
}

static PyObject* overlay_clearWindowOffset(PyObject* self, PyObject* args)
{
    if (!PyArg_ParseTuple(args, "")) {
        PyErr_SetString(PyExc_TypeError, "Unexpected arguments");

        return NULL;
    }

    overlay->clearWindowOffset();

    return Py_BuildValue("");
}

static PyObject* overlay_addText(PyObject* self, PyObject* args)
{
    const char* text;
    float x, y, size, r, g, b, a;
    int isCentered;

    if (!PyArg_ParseTuple(args, "sfffffffp", &text, &x, &y, &size, &r, &g, &b, &a, &isCentered)) {
        PyErr_SetString(PyExc_TypeError, "Failed to parse arguments");

        return NULL;
    }

    overlay->addText((char*)text, x, y, size, r, g, b, a, (bool)isCentered);

    return Py_BuildValue("");
}

static PyObject* overlay_addLine(PyObject* self, PyObject* args)
{
    float x1, y1, x2, y2, r, g, b, a, lineWidth;

    if (!PyArg_ParseTuple(args, "fffffffff", &x1, &y1, &x2, &y2, &r, &g, &b, &a, &lineWidth)) {
        PyErr_SetString(PyExc_TypeError, "Failed to parse arguments");

        return NULL;
    }

    overlay->addLine(x1, y1, x2, y2, r, g, b, a, lineWidth);

    return Py_BuildValue("");
}

static PyObject* overlay_addRectangle(PyObject* self, PyObject* args)
{
    float x1, y1, x2, y2, r, g, b, a, lineWidth;
    int isFilled;

    if (!PyArg_ParseTuple(args, "ffffffffpf", &x1, &y1, &x2, &y2, &r, &g, &b, &a, &isFilled, &lineWidth)) {
        PyErr_SetString(PyExc_TypeError, "Failed to parse arguments");

        return NULL;
    }

    overlay->addRectangle(x1, y1, x2, y2, r, g, b, a, (bool)isFilled, lineWidth);

    return Py_BuildValue("");
}

static PyObject* overlay_addTriangle(PyObject* self, PyObject* args)
{
    float x1, y1, x2, y2, x3, y3, r, g, b, a, lineWidth;
    int isFilled;

    if (!PyArg_ParseTuple(args, "ffffffffffpf", &x1, &y1, &x2, &y2, &x3, &y3, &r, &g, &b, &a, &isFilled, &lineWidth)) {
        PyErr_SetString(PyExc_TypeError, "Failed to parse arguments");

        return NULL;
    }

    overlay->addTriangle(x1, y1, x2, y2, x3, y3, r, g, b, a, (bool)isFilled, lineWidth);

    return Py_BuildValue("");
}

static PyObject* overlay_addCircle(PyObject* self, PyObject* args)
{
    float x, y, radius, r, g, b, a, lineWidth;
    int isFilled;

    if (!PyArg_ParseTuple(args, "fffffffpf", &x, &y, &radius, &r, &g, &b, &a, &isFilled, &lineWidth)) {
        PyErr_SetString(PyExc_TypeError, "Failed to parse arguments");

        return NULL;
    }

    overlay->addCircle(x, y, radius, r, g, b, a, (bool)isFilled, lineWidth);

    return Py_BuildValue("");
}

static PyObject* overlay_draw(PyObject* self, PyObject* args)
{
    if (!PyArg_ParseTuple(args, "")) {
        PyErr_SetString(PyExc_TypeError, "Unexpected arguments");

        return NULL;
    }

    overlay->draw();

    return Py_BuildValue("");
}

static PyObject* overlay_getWidth(PyObject* self, PyObject* args)
{
    if (!PyArg_ParseTuple(args, "")) {
        PyErr_SetString(PyExc_TypeError, "Unexpected arguments");

        return NULL;
    }

    return PyLong_FromLong(overlay->getWidth());
}

static PyObject* overlay_getHeight(PyObject* self, PyObject* args)
{
    if (!PyArg_ParseTuple(args, "")) {
        PyErr_SetString(PyExc_TypeError, "Unexpected arguments");

        return NULL;
    }

    return PyLong_FromLong(overlay->getHeight());
}

static PyObject* overlay_cleanup(PyObject* self, PyObject* args)
{
    if (!PyArg_ParseTuple(args, "")) {
        PyErr_SetString(PyExc_TypeError, "Unexpected arguments");

        return NULL;
    } else {
        overlay->cleanup();
        delete overlay;
        overlay = NULL;
    }

    return Py_BuildValue("");
}

static PyMethodDef overlayMethods[] = {
    { "init", overlay_init, METH_VARARGS, "Initialise" },
    { "clear", overlay_clear, METH_VARARGS, "Clear screen" },
    { "setTargetWindow", overlay_setTargetWindow, METH_VARARGS, "Set the target window (by ID)" },
    { "setWindowOffset", overlay_setWindowOffset, METH_VARARGS, "Set offset for drawing. Prefer setTargetWindow()." },
    { "clearWindowOffset", overlay_clearWindowOffset, METH_VARARGS, "Clear current window offset." },
    { "addText", overlay_addText, METH_VARARGS, "Add text" },
    { "addLine", overlay_addLine, METH_VARARGS, "Add a line" },
    { "addRectangle", overlay_addRectangle, METH_VARARGS, "Add a rectangle" },
    { "addTriangle", overlay_addTriangle, METH_VARARGS, "Add a triangle" },
    { "addCircle", overlay_addCircle, METH_VARARGS, "Add a circle" },
    { "draw", overlay_draw, METH_VARARGS, "Draw everything" },
    { "getWidth", overlay_getWidth, METH_VARARGS, "Get overlay width" },
    { "getHeight", overlay_getHeight, METH_VARARGS, "Get overlay height" },
    { "cleanup", overlay_cleanup, METH_VARARGS, "Perform cleanup before exit" },
    { NULL, NULL, 0, NULL }
};

static struct PyModuleDef overlayModule = {
    PyModuleDef_HEAD_INIT,
    MODULE_NAME,
    "Draws to a transparent overlay window.",
    -1,
    overlayMethods
};

PyMODINIT_FUNC PyInit_overlay(void)
{
    return PyModule_Create(&overlayModule);
}
