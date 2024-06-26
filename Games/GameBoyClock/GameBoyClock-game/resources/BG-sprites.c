#include "BG-sprites.h"

//declared as const to save compile and execution time/space
const unsigned char my_tiles[] =
{
// Sprite #1 at (line 0, col 0)
0x00,0x00,0x00,0x01,0x00,0x02,0x00,0x04,0x00,0x04,0x01,0x1a,0x08,0x25,0x04,0x42,

// Sprite #2 at (line 0, col 1)
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0xff,0x00,0x00,

// Sprite #3 at (line 0, col 2)
0x00,0x00,0x00,0x80,0x00,0x40,0x00,0x20,0x40,0x20,0x80,0x58,0x08,0xa4,0x04,0x42,

// Sprite #4 at (line 0, col 3)
0x00,0x00,0x01,0x01,0x03,0x02,0x06,0x04,0x06,0x04,0x1a,0x1b,0x35,0x2d,0x62,0x46,

// Sprite #5 at (line 0, col 4)
0x00,0x00,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0x00,0x00,

// Sprite #6 at (line 0, col 5)
0x00,0x00,0x80,0x80,0xc0,0x40,0x20,0x20,0x20,0x60,0x58,0xd8,0xb4,0xac,0x62,0x46,

// Sprite #7 at (line 0, col 6)
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x08,0x24,0x04,0x42,

// Sprite #8 at (line 0, col 7)
0x04,0x42,0x18,0x24,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

// Sprite #9 at (line 1, col 0)
0x04,0x42,0x04,0x42,0x04,0x42,0x04,0x42,0x04,0x42,0x04,0x42,0x04,0x42,0x04,0x42,

// Sprite #10 at (line 1, col 1)
0x00,0x00,0x00,0x00,0x00,0x18,0x10,0x24,0x00,0x24,0x00,0x18,0x00,0x00,0x00,0x00,

// Sprite #11 at (line 1, col 2)
0x04,0x42,0x04,0x42,0x04,0x42,0x04,0x42,0x04,0x42,0x04,0x42,0x04,0x42,0x04,0x42,

// Sprite #12 at (line 1, col 3)
0x62,0x46,0x62,0x46,0x62,0x46,0x62,0x46,0x62,0x46,0x62,0x46,0x62,0x46,0x62,0x46,

// Sprite #13 at (line 1, col 4)
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

// Sprite #14 at (line 1, col 5)
0x62,0x46,0x62,0x46,0x62,0x46,0x62,0x46,0x62,0x46,0x62,0x46,0x62,0x46,0x62,0x46,

// Sprite #15 at (line 1, col 6)
0x00,0x00,0x00,0x01,0x00,0x02,0x00,0x04,0x00,0x04,0x01,0x02,0x00,0x01,0x00,0x00,

// Sprite #16 at (line 1, col 7)
0x00,0x00,0x00,0x80,0x00,0x40,0x00,0x20,0x40,0x20,0x80,0x40,0x00,0x80,0x00,0x00,

// Sprite #17 at (line 2, col 0)
0x04,0x42,0x18,0x25,0x00,0x1a,0x00,0x04,0x00,0x04,0x01,0x02,0x00,0x01,0x00,0x00,

// Sprite #18 at (line 2, col 1)
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0xff,0x00,0x00,

// Sprite #19 at (line 2, col 2)
0x04,0x42,0x18,0xa4,0x00,0x58,0x00,0x20,0x40,0x20,0x80,0x40,0x00,0x80,0x00,0x00,

// Sprite #20 at (line 2, col 3)
0x62,0x46,0x25,0x3d,0x1b,0x1a,0x06,0x04,0x06,0x04,0x02,0x03,0x01,0x01,0x00,0x00,

// Sprite #21 at (line 2, col 4)
0x00,0x00,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0x00,0x00,

// Sprite #22 at (line 2, col 5)
0x62,0x46,0xa4,0xbc,0xd8,0x58,0x20,0x20,0x20,0x60,0x40,0xc0,0x80,0x80,0x00,0x00,

// Sprite #23 at (line 2, col 6)
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

// Sprite #24 at (line 2, col 7)
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

// Sprite #25 at (line 3, col 0)
0x04,0x42,0x18,0x25,0x00,0x1a,0x00,0x04,0x00,0x04,0x01,0x1a,0x08,0x25,0x04,0x42,

// Sprite #26 at (line 3, col 1)
0x04,0x42,0x18,0xa4,0x00,0x58,0x00,0x20,0x40,0x20,0x80,0x58,0x08,0xa4,0x04,0x42,

// Sprite #27 at (line 3, col 2)
0x00,0x08,0x00,0x0c,0x00,0x3e,0x00,0x4c,0x00,0x48,0x00,0x41,0x00,0x22,0x00,0x1c,

// Sprite #28 at (line 3, col 3)
0x62,0x46,0x25,0x3d,0x1b,0x1a,0x06,0x04,0x06,0x04,0x1a,0x1b,0x35,0x2d,0x62,0x46,

// Sprite #29 at (line 3, col 4)
0x62,0x46,0xa4,0xbc,0xd8,0x58,0x20,0x20,0x20,0x60,0x58,0xd8,0xb4,0xac,0x62,0x46,

// Sprite #30 at (line 3, col 5)
0x00,0xff,0x19,0x99,0x21,0xa1,0x21,0xa1,0x2d,0xad,0x25,0xa5,0x19,0x99,0x00,0xff,

// Sprite #31 at (line 3, col 6)
0x00,0xff,0x8d,0x8d,0x51,0x51,0x51,0x51,0x91,0x91,0x51,0x51,0x8d,0x8d,0x00,0xff,

// Sprite #32 at (line 3, col 7)
0x00,0xff,0x14,0x15,0x14,0x15,0x18,0x19,0x18,0x19,0x14,0x15,0xd4,0xd5,0x00,0xff,

// Sprite #33 at (line 4, col 0)
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x34,0x2c,0x62,0x46,

// Sprite #34 at (line 4, col 1)
0x62,0x46,0x24,0x3c,0x18,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

// Sprite #35 at (line 4, col 2)
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

// Sprite #36 at (line 4, col 3)
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

// Sprite #37 at (line 4, col 4)
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

// Sprite #38 at (line 4, col 5)
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

// Sprite #39 at (line 4, col 6)
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

// Sprite #40 at (line 4, col 7)
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

// Sprite #41 at (line 5, col 0)
0x00,0x00,0x01,0x01,0x03,0x02,0x06,0x04,0x06,0x04,0x02,0x03,0x01,0x01,0x00,0x00,

// Sprite #42 at (line 5, col 1)
0x00,0x00,0x80,0x80,0xc0,0x40,0x20,0x20,0x20,0x60,0x40,0xc0,0x80,0x80,0x00,0x00,

// Sprite #43 at (line 5, col 2)
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

// Sprite #44 at (line 5, col 3)
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

// Sprite #45 at (line 5, col 4)
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

// Sprite #46 at (line 5, col 5)
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

// Sprite #47 at (line 5, col 6)
0x00,0x18,0x00,0x24,0x00,0x24,0x00,0x24,0x00,0x24,0x00,0x24,0x00,0x24,0x00,0x18,

// Sprite #48 at (line 5, col 7)
0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x04,

// Sprite #49 at (line 6, col 0)
0x00,0x18,0x00,0x04,0x00,0x04,0x00,0x18,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x18,

// Sprite #50 at (line 6, col 1)
0x00,0x18,0x00,0x04,0x00,0x04,0x00,0x18,0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x18,

// Sprite #51 at (line 6, col 2)
0x00,0x24,0x00,0x24,0x00,0x24,0x00,0x18,0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x04,

// Sprite #52 at (line 6, col 3)
0x00,0x18,0x00,0x20,0x00,0x20,0x00,0x18,0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x18,

// Sprite #53 at (line 6, col 4)
0x00,0x18,0x00,0x20,0x00,0x20,0x00,0x18,0x00,0x24,0x00,0x24,0x00,0x24,0x00,0x18,

// Sprite #54 at (line 6, col 5)
0x00,0x18,0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x04,

// Sprite #55 at (line 6, col 6)
0x00,0x18,0x00,0x24,0x00,0x24,0x00,0x18,0x00,0x24,0x00,0x24,0x00,0x24,0x00,0x18,

// Sprite #56 at (line 6, col 7)
0x00,0x18,0x00,0x24,0x00,0x24,0x00,0x18,0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x18,

// Sprite #57 at (line 7, col 0)
0x04,0x00,0x04,0x00,0x24,0x00,0x54,0x00,0x74,0x00,0x44,0x00,0x32,0x00,0x00,0x00,

// Sprite #58 at (line 7, col 1)
0x00,0x00,0x00,0x00,0x46,0x00,0xa8,0x00,0xe8,0x00,0x88,0x00,0x66,0x00,0x00,0x00,

// Sprite #59 at (line 7, col 2)
0x80,0x00,0x80,0x00,0xd4,0x00,0x99,0x00,0x91,0x00,0x91,0x00,0x50,0x00,0x00,0x00,

// Sprite #60 at (line 7, col 3)
0x00,0x00,0x00,0x00,0x88,0x00,0x55,0x00,0x55,0x00,0x4d,0x00,0x84,0x00,0x18,0x00,

// Sprite #61 at (line 7, col 4)
0x01,0x00,0x01,0x00,0x89,0x00,0x55,0x00,0xdd,0x00,0x11,0x00,0xcd,0x00,0x00,0x00,

// Sprite #62 at (line 7, col 5)
0x00,0x00,0x00,0x00,0x03,0x00,0x44,0x00,0x84,0x00,0x44,0x00,0x53,0x00,0x00,0x00,

// Sprite #63 at (line 7, col 6)
0x00,0x00,0x00,0x00,0x30,0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x30,0x00,0x00,0x00,

// Sprite #64 at (line 7, col 7)
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};