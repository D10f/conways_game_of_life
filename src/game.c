#include "game.h"
#include "init_sdl.h"
#include <SDL2/SDL.h>

uint8_t game_new(struct Game **game)
{
    *game = calloc(1, sizeof(struct Game));

    if (*game == NULL)
    {
        fprintf(stderr, "Something went wrong.\n");
        return 1;
    }

    if (game_init_sdl(*game) != 0) {
        return 1;
    }

    return 0;
}

uint8_t game_free(struct Game **game)
{
    if (*game == NULL)
        return 1;

    struct Game *_game = *game;

    if (_game->renderer) {
        SDL_DestroyRenderer(_game->renderer);
        _game->renderer = NULL;
    }

    if (_game->window) {
        SDL_DestroyWindow(_game->window);
        _game->window = NULL;
    }

    SDL_Quit();

    free(_game);
    _game = NULL;

    return 0;
}

uint8_t game_run(struct Game **g)
{
    printf("Hello, world\n");
    return 0;
}

