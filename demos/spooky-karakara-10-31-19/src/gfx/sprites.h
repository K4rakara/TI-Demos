// convpng v7.2
// this file contains all the graphics sources for easy inclusion in a project
// Modified to match prefered variable naming convention.
#ifndef __sprites__
#define __sprites__
#include <stdint.h>

#define spritesTransparentColorIndex 0

#define pumpkinWidth 64
#define pumpkinHeight 64
#define pumpkinSize 4098
extern uint8_t pumpkinData[4098];
#define pumpkin ((gfx_sprite_t*)pumpkinData)
#define ghostWidth 32
#define ghostHeight 32
#define ghostSize 1026
extern uint8_t ghostData[1026];
#define ghost ((gfx_sprite_t*)ghostData)
#define sizeOfSpritesPal 26
extern uint16_t spritesPal[13];

#endif
