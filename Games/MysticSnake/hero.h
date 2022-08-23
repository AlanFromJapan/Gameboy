#ifndef __HERO_H__
#define __HERO_H__

#include <gb/gb.h>

#define HERO_LOOK_UP        0
#define HERO_LOOK_DOWN      1
#define HERO_LOOK_LEFT      2
#define HERO_LOOK_RIGHT     3

struct hero {
    UINT8 x;
    UINT8 y;
    UINT8 stepCount;
    UINT8 heroLook;
    //life is DOUBLED to use the "half hearts"
    UINT8 lifeMax;
    //life is DOUBLED to use the "half hearts"
    UINT8 life;
    //invincible counter: blink for a time
    UINT8 invincibleCounter;
};

extern struct hero hero;

//Move the Hero to x,y
#define MV_HERO()    move_sprite(0, MAP2SCREEN_X(hero.x), MAP2SCREEN_Y(hero.y)); move_sprite(1, MAP2SCREEN_X(hero.x)+8, MAP2SCREEN_Y(hero.y));

//Results of the checkCollision()
#define MOVE_CHECK_OK           0
#define MOVE_CHECK_COLLISION    1
#define MOVE_CHECK_TRANSITION   2

//last param of checkCollision() only the hero needs to check transition
#define IGNORE_TRANSITION       0
#define CHECK_FOR_TRANSITION    1

//checks if the next move from x,y is possible regarding collision
UINT8  checkCollision (UINT8 mapx, UINT8 mapy, INT8 *dx, INT8 *dy, UINT8 checkTransition);

//Hero tiles have the alternate (left foot / right foot) stored one after the other, so once you have one the rest is just adding offset
inline void updateHeroSprite(const UINT8 baseSprite);

//hero was hit by dmg points
void heroDamaged(UINT8 dmg);

#endif // __HERO_H__