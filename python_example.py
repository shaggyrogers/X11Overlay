#!/usr/bin/env python3
"""
  python_example.py
  =================

  Description:           Python overlay test/example script
  Author:                Michael De Pasquale
  Creation Date:         2025-05-14
  Modification Date:     2025-05-15

"""

# Usage: Compile python interface with 'make python', then copy bin/overlay.so to the
# directory containing this script and run it.

import signal
import sys
import time

import overlay

# pylint: disable=c-extension-no-member


def sigintHandler(signal, frame) -> None:
    print("Got SIGINT, cleaning up and exiting..")
    overlay.cleanup()

    sys.exit(0)


def main(*args) -> None:
    signal.signal(signal.SIGINT, sigintHandler)
    overlay.init()
    width, height = overlay.getWidth(), overlay.getHeight()

    print(f"Created overlay window with dimensions {width}x{height}")

    while 1:
        overlay.clear()

        overlay.addText("TEST", 10, 10, 12, 1, 0.25, 0.25, 1, False)
        overlay.addLine(32, 32, 512, 512, 1, 0.5, 0.5, 1.0, 4.0)
        overlay.addRectangle(0, 0, 128, 64, 0, 0.8, 0.2, 0.8, True, 1)
        overlay.addTriangle(64, 64, 96, 96, 128, 128, 0.2, 0.2, 1, 0.5, False, 4)
        overlay.addCircle(96, 96, 8, 0, 1, 1, 1, False, 1)

        overlay.draw()

        time.sleep(0.005)


if __name__ == "__main__":
    sys.exit(main(*sys.argv))
