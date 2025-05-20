#ifndef _BOARD_H
#define _BOARD_H

#include "main.h"

struct Board {
    SDL_Renderer *renderer;
    uint8_t *current_iteration;
    uint8_t *next_iteration;
    uint32_t rows;
    uint32_t cols;
};

uint8_t board_new(struct Board **board, SDL_Renderer *renderer);

uint8_t board_render(const struct Board *board);

uint8_t board_free(struct Board **board);

void board_reset(struct Board *board);

void board_clear(struct Board *board);

#endif // !_BOARD_H
