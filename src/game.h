#ifndef _GAME_H
#define _GAME_H

#include "main.h"
#include "fps.h"
#include <stdint.h>

struct Game {
    struct Board *board;
    struct Fps   *fps;
    SDL_Renderer *renderer;
    SDL_Window   *window;
    SDL_Event    event;
    uint8_t      is_running;
};

/**
 * Instantiates a new game
 */
uint8_t game_new(struct Game **game);

uint8_t game_free(struct Game **game);

uint8_t game_run(struct Game *game);

#endif // !_GAME_H
