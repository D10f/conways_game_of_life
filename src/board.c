#include "board.h"
#include "main.h"

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

    uint8_t board_size = b->rows * b->cols;

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
