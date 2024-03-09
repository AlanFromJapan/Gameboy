# Games/Tools

## GameBoyClock-emu

Just a helper tool for testing/debuging. Send/Receive one byte of data, byte per byte or continuously. 

## GameBoyClock-commtest

Closer to target: allows to get data regularily from the Serial port, using the GB as master clock. Still just a helper tool, mainly for testing the SoftSPI library.

## GameBoyClock-rcvdbg

Needed a little more help to debug the reception part: this one shows the received bytes in detail.

# Links

## Micro-controller counterpart of that project

See here https://github.com/AlanFromJapan/GameboyClock 

This holds the code of the micro-controller helper programs and the final one.
In a nutshell reads the RTC and returns the time when asked by the GB.

## Ideas
- https://blog.gbplay.io/2021/05/29/Connecting-to-a-Game-Boy-Link-Cable-From-a-PC.html
- https://gbdev.gg8.se/wiki/articles/Serial_Data_Transfer_(Link_Cable)
