#python 3 - returns the ROM usage in %
#just finds from the end the first non-255 byte and consider it's the maximum position where the data ends.

import os
import sys

MAX_ROM = 32768


if len(sys.argv) <= 1:
    print("you must pass as parameter the path to the ROM file to test.")
    exit(0)

with open(str(sys.argv[1]), "rb") as f:
    i = MAX_ROM -1
    while True:
        f.seek(i)
        buf = f.read(1)
        i = i- 1

        if int(buf[0]) != 255:
            break
    
    print("Using {0:.2%} of the ROM ({1:,} bytes).".format (i / MAX_ROM, i))

