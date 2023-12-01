
#ifndef __my_tiles_H__
#define __my_tiles_H__

#define TILE_COUNT		48

#define SPRITE_1		0
#define SPRITE_2		4
#define SPRITE_3		8
#define SPRITE_4		12
#define SPRITE_5		16
#define SPRITE_6		20
#define SPRITE_7		24
#define SPRITE_8		28
#define SPRITE_9		32
#define SPRITE_10		36

//hack insert the patch and redef constant
#include "rolling_dice.patch.h"


//declared as const to save compile and execution time/space
extern const unsigned char my_tiles[]; 

#endif //__my_tiles_h__


