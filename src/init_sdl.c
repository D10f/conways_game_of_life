#include "init_sdl.h"
#include "game.h"
#include "main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>

uint8_t game_init_sdl(struct Game *g)
{
    uint8_t is_running = SDL_Init(SDL_INIT_FLAGS);

    // IMG_INIT returns an int as a bitfield of the initialized images
    if ((IMG_Init(IMG_FLAGS) & IMG_FLAGS) != IMG_FLAGS) {
        fprintf(stderr, "Failed to load the requested SDL image modules.\n");
    }

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

    SDL_Surface *icon = IMG_Load("images/cgol.png");

    if (icon == NULL) {
        fprintf(stderr, "%s\n", IMG_GetError());
        return 1;
    }

    SDL_SetWindowIcon(g->window, icon);
    SDL_FreeSurface(icon);
    icon = NULL;

    return 0;
}
