
#ifndef __my_lib01_H__
#define __my_lib01_H__

#define my_lib01_COUNT   15


#define TILE_BLOCK_Q_NW   0
#define TILE_BLOCK_Q_SW   1
#define TILE_BLOCK_Q_NE   2
#define TILE_BLOCK_Q_SE   3
#define TILE_COIN_NW   4
#define TILE_COIN_SW   5
#define TILE_COIN_NE   6
#define TILE_COIN_SE   7
#define TILE_EMPTY   8
#define TILE_BORDER_TL   9
#define TILE_BORDER_H   10
#define TILE_BORDER_TR   11
#define TILE_BORDER_LL   12
#define TILE_BORDER_LR   13
#define TILE_BORDER_V   14


//declared as const to save compile and execution time/space
extern const unsigned char my_lib01[]; 

#endif //__my_lib01_H__


