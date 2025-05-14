/*
  overlay.cpp
  ===========

  Description:           Python interface.
  Author:                Michael De Pasquale
  Creation Date:         2025-05-14
  Modification Date:     2025-05-14

*/

#define PY_SSIZE_T_CLEAN
#define MODULE_NAME "overlay"

// HACK:
#include "../../libxoverlay.h"
#include <Python.h>
#include <iostream>

static PyObject* overlay_init(PyObject* self, PyObject* args)
{
    // NOTE: Expecting this to fail if arguments are provided.. test this!
    if (!PyArg_ParseTuple(args, "")) {
        PyErr_SetString(PyExc_TypeError, "Unexpected arguments");
    } else {
        init();
    }

    return NULL;
}

static PyObject* overlay_clear(PyObject* self, PyObject* args)
{
    if (!PyArg_ParseTuple(args, "")) {
        PyErr_SetString(PyExc_TypeError, "Unexpected arguments");
    } else {
        clear();
    }

    return NULL;
}

static PyObject* overlay_setWindowMap(PyObject* self, PyObject* args)
{
    // float x, float y, float width, float height
    float x, y, width, height;

    if (!PyArg_ParseTuple(args, "ffff", &x, &y, &width, &height)) {
        PyErr_SetString(PyExc_TypeError, "Failed to parse arguments");

        return NULL;
    }

    setWindowMap(x, y, width, height);

    return NULL;
}

static PyObject* overlay_clearWindowMap(PyObject* self, PyObject* args)
{
    if (!PyArg_ParseTuple(args, "")) {
        PyErr_SetString(PyExc_TypeError, "Unexpected arguments");
    } else {
        clearWindowMap();
    }

    return NULL;
}

static PyObject* overlay_addText(PyObject* self, PyObject* args)
{
    const char* text;
    float x, y, size, r, g, b, a;
    int isCentered;

    if (!PyArg_ParseTuple(args, "sffffffp", &text, &x, &y, &size, &r, &g, &b, &a, &isCentered)) {
        PyErr_SetString(PyExc_TypeError, "Failed to parse arguments");

        return NULL;
    }

    addText((char*)text, x, y, size, r, g, b, a, (bool)isCentered);

    return NULL;
}

static PyObject* overlay_addLine(PyObject* self, PyObject* args)
{
    float x1, y1, x2, y2, r, g, b, a, lineWidth;

    if (!PyArg_ParseTuple(args, "fffffffff", &x1, &y1, &x2, &y2, &r, &g, &b, &a, &lineWidth)) {
        PyErr_SetString(PyExc_TypeError, "Failed to parse arguments");

        return NULL;
    }

    addLine(x1, y1, x2, y2, r, g, b, a, lineWidth);

    return NULL;
}

static PyObject* overlay_addRectangle(PyObject* self, PyObject* args)
{
    float x1, y1, x2, y2, r, g, b, a, lineWidth;
    int isFilled;

    if (!PyArg_ParseTuple(args, "ffffffffpf", &x1, &y1, &x2, &y2, &r, &g, &b, &a, &isFilled, &lineWidth)) {
        PyErr_SetString(PyExc_TypeError, "Failed to parse arguments");

        return NULL;
    }

    addRectangle(x1, y1, x2, y2, r, g, b, a, (bool)isFilled, lineWidth);

    return NULL;
}

static PyObject* overlay_addTriangle(PyObject* self, PyObject* args)
{
    float x1, y1, x2, y2, x3, y3, r, g, b, a, lineWidth;
    int isFilled;

    if (!PyArg_ParseTuple(args, "ffffffffffffpf", &x1, &y1, &x2, &y2, &x3, &y3, &r, &g, &b, &a, &isFilled, &lineWidth)) {
        PyErr_SetString(PyExc_TypeError, "Failed to parse arguments");

        return NULL;
    }

    addTriangle(x1, y1, x2, y2, x3, y3, r, g, b, a, (bool)isFilled, lineWidth);

    return NULL;
}

static PyObject* overlay_addCircle(PyObject* self, PyObject* args)
{
    float x, y, radius, r, g, b, a, lineWidth;
    int isFilled;

    if (!PyArg_ParseTuple(args, "fffffffpf", &x, &y, &radius, &r, &g, &b, &a, &isFilled, &lineWidth)) {
        PyErr_SetString(PyExc_TypeError, "Failed to parse arguments");

        return NULL;
    }

    addCircle(x, y, radius, r, g, b, a, (bool)isFilled, lineWidth);

    return NULL;
}

static PyObject* overlay_draw(PyObject* self, PyObject* args)
{
    if (!PyArg_ParseTuple(args, "")) {
        PyErr_SetString(PyExc_TypeError, "Unexpected arguments");
    } else {
        draw();
    }

    return NULL;
}

static PyObject* overlay_getWidth(PyObject* self, PyObject* args)
{
    if (!PyArg_ParseTuple(args, "")) {
        PyErr_SetString(PyExc_TypeError, "Unexpected arguments");

        return NULL;
    }

    return PyLong_FromLong(getWidth());
}

static PyObject* overlay_getHeight(PyObject* self, PyObject* args)
{
    if (!PyArg_ParseTuple(args, "")) {
        PyErr_SetString(PyExc_TypeError, "Unexpected arguments");

        return NULL;
    }

    return PyLong_FromLong(getHeight());
}

static PyObject* overlay_cleanup(PyObject* self, PyObject* args)
{
    if (!PyArg_ParseTuple(args, "")) {
        PyErr_SetString(PyExc_TypeError, "Unexpected arguments");
    } else {
        cleanup();
    }

    return NULL;
}

static PyMethodDef overlayMethods[] = {
    { "init", overlay_init, METH_VARARGS, "Initialise" },
    { "clear", overlay_clear, METH_VARARGS, "Clear screen" },
    { "setWindowMap", overlay_setWindowMap, METH_VARARGS, "Map all drawing to a rectangle" },
    { "clearWindowMap", overlay_clearWindowMap, METH_VARARGS, "Clear current window map." },
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

int main(int argc, char* argv[])
{
    PyStatus status;
    PyConfig config;

    PyConfig_InitPythonConfig(&config);

    // Add our module as a built-in, before Py_Initialize
    if (PyImport_AppendInittab(MODULE_NAME, PyInit_overlay) == -1) {
        std::cerr << "Error: could not extend in-built modules table" << std::endl;

        return 1;
    }

    // Pass argv[0] to the Python interpreter
    status = PyConfig_SetBytesString(&config, &config.program_name, argv[0]);

    if (PyStatus_Exception(status)) {
        goto exception;
    }

    // Initialize the Python interpreter.
    status = Py_InitializeFromConfig(&config);

    if (PyStatus_Exception(status)) {
        goto exception;
    }

    PyConfig_Clear(&config);

    // Import the module
    if (!PyImport_ImportModule(MODULE_NAME)) {
        PyErr_Print();
        std::cerr << "Error: could not import module '" << MODULE_NAME << "'"
                  << std::endl;
    }

    return 0;

exception:
    PyConfig_Clear(&config);
    Py_ExitStatusException(status);
}
