/*
   Overlay.cs 
   ==========

   Description:           Wrapper class - C# interface for libxoverlay
   Author:                Michael De Pasquale <shaggyrogers>
   Creation Date:         2016-12-04
   Modification Date:     2025-05-14
   License:               MIT
 */

using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace rustesp {
    public static class Overlay {
        
        [DllImport("libxoverlay.so", EntryPoint="init")]
        public static extern void init();

        [DllImport("libxoverlay.so", EntryPoint="clear")]
        public static extern void clear();

        [DllImport("libxoverlay.so", EntryPoint="setTargetWindow")]
        public static extern bool setTargetWindow(unsigned int id, int& width, int& height);

        [DllImport("libxoverlay.so", EntryPoint="setWindowOffset")]
        public static extern void setWindowOffset(int x, int y);

        [DllImport("libxoverlay.so", EntryPoint="clearWindowOffset")]
        public static extern void clearWindowOffset();

        [DllImport("libxoverlay.so", EntryPoint="addText")]
        public static extern void addText(String str, float x, float y, 
                float size, float r, float g, float b, float a, bool centered);

        [DllImport("libxoverlay.so", EntryPoint="addLine")]
        public static extern void addLine(float x1, float y1, float x2, 
                float y2, float r, float g, float b, float a, float lineWidth);

        [DllImport("libxoverlay.so", EntryPoint="addRectangle")]
        public static extern void addRectangle(float x1, float y1, float x2, 
                float y2, float r, float g, float b, float a, bool filled, 
                float lineWidth);

        [DllImport("libxoverlay.so", EntryPoint="addTriangle")]
        public static extern void addTriangle(float x1, float y1, float x2, 
                float y2, float x3, float y3, float r, float g, float b, 
                float a, bool filled, float lineWidth);

        [DllImport("libxoverlay.so", EntryPoint="addCircle")]
        public static extern void addCircle(float x, float y, float radius, 
                float r, float g, float b, float a, bool filled, 
                float lineWidth);

        [DllImport("libxoverlay.so", EntryPoint="draw")]
        public static extern void draw();
              
        [DllImport("libxoverlay.so", EntryPoint="getWidth")]
        public static extern Int32 getWidth();

        [DllImport("libxoverlay.so", EntryPoint="getHeight")]
        public static extern Int32 getHeight();
              
        [DllImport("libxoverlay.so", EntryPoint="cleanup")]
        public static extern void cleanup();
    }
}
