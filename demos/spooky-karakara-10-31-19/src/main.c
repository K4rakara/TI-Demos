// Spooky halloween demo
// Copyright (C) 2019 Karakara
// Liscensed under the MIT liscense.
// See LISCENSE for details.

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <compression.h>
#include <graphx.h>

#include "gfx/sprites.h"

gfx_UninitedSprite(tmpPumpkin, pumpkinWidth, pumpkinHeight);

void main(void) {
    // Initializations.
    // ===================================================================s
    uint8_t pumpkins[4][4] = { // X, Y, Rotation.
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
    };
    uint8_t ghosts[4][4] = { // X, Y, Sine offset, speed.
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
    };
    uint8_t i;
    gfx_Begin();
    gfx_SetDrawBuffer();
    gfx_SetPalette(spritesPal, sizeOfSpritesPal, 0);
    // Generate initial state
    for (i = 1; i < 4; i++) { // Randomly generate the positions of the pumpkins.
        pumpkins[i][1] = (rand() % (320 - 64)); // Add 32 to position later to allow 8 bit number.
        pumpkins[i][2] = (rand() % (230 - 64)) + 37;
        pumpkins[i][3] = rand() % 255;
        pumpkins[i][4] = rand() % 128;
    }
    for (i = 1; i < 4; i++) { // Randomly generate the positions of the ghosts.
        ghosts[i][1] = (rand() % (320 - 128)); // Add 32 to position later to allow 8 bit number.
        ghosts[i][2] = (rand() % (230 - 64)) + 37;
        ghosts[i][3] = rand() % 255;
        ghosts[i][4] = (rand() % 3) + 2;
    }
    // Main loop
    // ===================================================================
    while (!os_GetCSC()) {
        // Update
        for (i = 0; i < 4; i++) { // Update the pumpkins.
            pumpkins[i][2] = pumpkins[i][2] + 8;
            pumpkins[i][3] = pumpkins[i][3] + 6;
            if (pumpkins[i][2] >= 248) {
                pumpkins[i][1] = (rand() % (320 - 64)); // Add 32 to position later to allow 8 bit number.
                pumpkins[i][2] = 0;
                pumpkins[i][3] = rand() % 255;
                pumpkins[i][4] = rand() % 128;
            }
        }
        for (i = 0; i <= 4; i++) { // Update the ghosts.
            ghosts[i][2] = ghosts[i][2] - ghosts[i][4];
            ghosts[i][3] = ghosts[i][3] + 4;
            if (ghosts[i][2] <= 4) {
                ghosts[i][1] = (rand() % (320 - 128));
                ghosts[i][2] = 255;
                ghosts[i][3] = rand() % 255;
                ghosts[i][4] = (rand() % 3) + 2;
            }
        }
        // Draw
        gfx_FillScreen(3);
        gfx_SetColor(1);
        for (i = 0; i < 80; i++) { // Draw the bg.
            gfx_VertLine_NoClip(i * 4, 0, 240);
            gfx_VertLine_NoClip(i * 4 + 1, 0, 240);
        }
        for (i = 0; i < 4; i++) { // Draw the ghosts.
            uint8_t tmpXLoc = (sin((ghosts[i][3] + cos(ghosts[i][2]))/16) * 24) + (ghosts[i][1] + 32);
            gfx_TransparentSprite(ghost, tmpXLoc, ghosts[i][2] - 8);
        }
        for (i = 0; i < 4; i++) { // Draw the pumpkins.
            double tmpOffset = 32 * ((((pumpkins[i][4] + 128) / 192) * 50 + 50) / 100);
            gfx_RotateScaleSprite(pumpkin, tmpPumpkin, pumpkins[i][3], (((pumpkins[i][4] + 128) / 192) * 50 + 50));
            gfx_TransparentSprite(tmpPumpkin, pumpkins[i][1] - tmpOffset, pumpkins[i][2] - tmpOffset - 8);
        }
        gfx_BlitBuffer();
    }
    // Cleanup
    // ===================================================================
    gfx_End();
}