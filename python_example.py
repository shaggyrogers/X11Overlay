#!/usr/bin/env python3
"""
  python_example.py
  =================

  Description:           Python overlay test/example script
  Author:                Michael De Pasquale
  Creation Date:         2025-05-14
  Modification Date:     2025-05-23

"""

# Usage: Before running, build the python interface with 'make python'.
# This will build overlay.so and copy it to the current directory.

import signal
import sys
import time

import overlay

# pylint: disable=c-extension-no-member,invalid-name


def sigintHandler(signal, frame) -> None:
    print("Got SIGINT, cleaning up and exiting..")
    overlay.cleanup()

    sys.exit(0)


def main(*args) -> None:
    signal.signal(signal.SIGINT, sigintHandler)
    overlay.init()
    width, height = overlay.getWidth(), overlay.getHeight()

    print(f"Created overlay window with dimensions {width}x{height}")

    # Set target window, if provided
    if len(args) > 1:
        assert len(args) == 2
        targetWin = int(args[1], base=0)

        targetWidth, targetHeight = overlay.setTargetWindow(targetWin)
        print(f"Set target: Window {targetWin}, {targetWidth}x{targetHeight}")

        width, height = targetWidth, targetHeight

    while 1:
        overlay.clear()

        # Draw X to indicate bounds
        overlay.addLine(0, 0, width, height, 1, 0.5, 0.5, 1.0, 4.0)
        overlay.addLine(0, height, width, 0, 1, 0.5, 0.5, 1.0, 4.0)

        overlay.addText("TEST", 10, 10, 32, 1, 0.25, 0.25, 1, False)
        overlay.addRectangle(128, 128, 256, 256, 0, 0.8, 0.2, 0.8, True, 1)
        overlay.addCircle(96, 96, 32, 0, 1, 1, 1, False, 4)

        # FIXME: This doesn't draw anything?
        overlay.addTriangle(64, 64, 96, 96, 128, 128, 0.2, 0.2, 1, 1, False, 4)

        overlay.draw()

        time.sleep(0.005)


if __name__ == "__main__":
    sys.exit(main(*sys.argv))
