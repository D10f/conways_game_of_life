#include "board.h"
#include "main.h"
#include <SDL2/SDL_render.h>
#include <stdint.h>
#include <stdlib.h>

uint8_t board_new(struct Board **board, SDL_Renderer *renderer)
{
    *board = calloc(1, sizeof(struct Board));

    if (*board == NULL) {
        fprintf(stderr, "Error allocating memory for the board.\n");
        return 1;
    }

    struct Board *b = *board;

    b->renderer = renderer;
    b->cols = WINDOW_WIDTH / CELL_SIZE;
    b->rows = WINDOW_HEIGHT / CELL_SIZE;

    uint32_t board_size = b->rows * b->cols;

    b->current_iteration = calloc(1, sizeof(uint8_t) * board_size);

    if (b->current_iteration == NULL) {
        fprintf(stderr, "Error allocating memory for the board.\n");
        return 1;
    }

    b->next_iteration = calloc(1, sizeof(uint8_t) * board_size);

    if (b->current_iteration == NULL) {
        fprintf(stderr, "Error allocating memory for the board.\n");
        return 1;
    }

    board_reset(b);

    return 0;
}

uint8_t board_free(struct Board **board)
{
    if (*board == NULL) return 1;

    struct Board *b = *board;

    if (b->current_iteration) free(b->current_iteration);
    if (b->next_iteration) free(b->next_iteration);

    b->renderer = NULL;

    free(*board);
    *board = NULL;

    return 0;
}


uint8_t board_render(const struct Board *board)
{
    SDL_SetRenderDrawColor(board->renderer, CELL_COLOR);

    // Subtract 1 from width and height to make padding around each cell drawn.
    struct SDL_Rect cell = {
        .w = CELL_SIZE - 1,
        .h = CELL_SIZE - 1,
    };

    uint32_t board_idx;

    for (int row = 0; row < board->rows; ++row) {

        cell.y = CELL_SIZE * row;

        for (int col = 0; col < board->cols; ++col) {

            cell.x = CELL_SIZE * col;
            board_idx = row * board->cols + col;

            if (board->current_iteration[board_idx])
                SDL_RenderFillRect(board->renderer, &cell);
        }
    }

    return 0;
}

void board_reset(struct Board *board)
{
    uint32_t board_idx;
    uint8_t random_cell_state;

    for (int row = 0; row < board->rows; ++row) {
        for (int col = 0; col < board->cols; ++col) {
            board_idx = row * board->cols + col;
            random_cell_state = rand() % 2 == 0;
            board->current_iteration[board_idx] = random_cell_state;
        }
    }
}
