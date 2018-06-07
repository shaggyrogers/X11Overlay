/* Simple test program for drawing an overlay using x11
   taken largely from
        http://stackoverflow.com/questions/21780789/x11-draw-on-overlay-window
   issues: flickering, only a significant issue if alpha is used
*/

#include <signal.h>
#include <stdio.h>
#include <time.h>

#include "X11Overlay.h"

bool running = true;

/*interrupt signal (Ctrl + c) callback*/
void on_sigint(int signal)
{
    running = false;
}

/*entry point*/
int main(int argc, char* args[])
{
    /*Register for interrupt signal*/
    signal(SIGINT, on_sigint);

    /*Create overlay*/
    XOverlay overlay; // = new XOverlay();

    /*Get overlay (screen) width and height*/
    int width = overlay.getWidth();
    int height = overlay.getHeight();

    /*Main drawing loop*/
    struct timespec ts = { 0, 5000000 }; /*200 Hz*/

    float i = 0;

    while (running) {
        /*Clear the overlay*/
        overlay.clear();

        /*Add items to draw*/
        /*Radar base*/
        overlay.addRectangle(i, i, (float)width / 8.0f + i,
                (float)width / 8.0f + i, 0.5f, 0.5f, 0.5f, 1.0f, true, 1.0f);

        i += 0.25f;

        /*Text*/
        overlay.addText((char*)"Test", (float)width / 2.0f, 10.0f, 10.0f, 0.2f,
                0.2f, 0.9f, 0.3f, false);

        /*Draw items*/
        overlay.draw();

        /*sleep for 5ms*/
        nanosleep(&ts, 0);
    }

    /*Cleanup*/
    overlay.cleanup();
    return 0;
}
