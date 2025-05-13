#ifndef _GAME_H
#define _GAME_H

#include "main.h"
#include <stdint.h>

struct Game {
    SDL_Renderer *renderer;
    SDL_Window   *window;
};

/**
 * Instantiates a new game
 */
uint8_t game_new(struct Game **game);

uint8_t game_free(struct Game **game);

uint8_t game_run(struct Game *game);

#endif // !_GAME_H
