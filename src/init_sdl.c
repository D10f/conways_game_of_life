#include "init_sdl.h"
#include "game.h"
#include "main.h"
#include <SDL2/SDL.h>

uint8_t game_init_sdl(struct Game *g)
{
    uint8_t is_running = SDL_Init(SDL_INIT_FLAGS);

    if (is_running != 0) {
        fprintf(stderr, "%s\n", SDL_GetError());
        return 1;
    }

    g->window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                                 WINDOW_HEIGHT, SDL_WINDOW_FLAGS);

    if (g->window == NULL) {
        fprintf(stderr, "%s\n", SDL_GetError());
        return 1;
    }

    g->renderer = SDL_CreateRenderer(g->window, -1, SDL_RENDERER_FLAGS);

    if (g->renderer == NULL) {
        fprintf(stderr, "%s\n", SDL_GetError());
        return 1;
    }

    return 0;
}
