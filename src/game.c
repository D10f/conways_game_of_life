#include "game.h"
#include "board.h"
#include "init_sdl.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>

/**
 * Internal function to handle input events.
 */
static void game_events(struct Game *game);

/**
 * Internal function to handle the rendering process.
 */
static void game_render(struct Game *game);

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

    (*game)->is_running = 1;

    srand(time(NULL));

    if (board_new(&(*game)->board, (*game)->renderer) != 0) {
        return 1;
    }

    return 0;
}

uint8_t game_free(struct Game **game)
{
    if (*game == NULL)
        return 1;

    if ((*game)->board)
        board_free(&(*game)->board);

    struct Game *_game = *game;

    if (_game->renderer) {
        SDL_DestroyRenderer(_game->renderer);
        _game->renderer = NULL;
    }

    if (_game->window) {
        SDL_DestroyWindow(_game->window);
        _game->window = NULL;
    }

    IMG_Quit();
    SDL_Quit();

    free(_game);
    _game = NULL;

    return 0;
}

uint8_t game_run(struct Game *game)
{
    while (game->is_running) {
        game_events(game);
        game_render(game);
        SDL_Delay(17);
    }

    return 0;
}

void game_events(struct Game *game)
{
    while (SDL_PollEvent(&game->event)) {
        switch (game->event.type) {
            case SDL_KEYDOWN:
                switch (game->event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        game->is_running = 0;
                        break;
                    case SDLK_r:
                        board_reset(game->board);
                        break;
                    case SDLK_c:
                        board_clear(game->board);
                        break;
                    default:
                        break;
                }
                break;
            case SDL_QUIT:
                game->is_running = 0;
                break;
            default:
                break;
        }
    }
}

void game_render(struct Game *game)
{
    SDL_SetRenderDrawColor(game->renderer, RENDERER_COLOR);
    SDL_RenderClear(game->renderer);

    board_render(game->board);

    SDL_RenderPresent(game->renderer);
}

