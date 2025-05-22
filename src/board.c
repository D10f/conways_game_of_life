#include "board.h"
#include "main.h"
#include <SDL2/SDL_render.h>
#include <stdint.h>
#include <stdlib.h>

static uint8_t count_neighbors(struct Board *board, int row, int col);

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

    b->current = calloc(1, sizeof(uint8_t) * board_size);

    if (b->current == NULL) {
        fprintf(stderr, "Error allocating memory for the board.\n");
        return 1;
    }

    b->next = calloc(1, sizeof(uint8_t) * board_size);

    if (b->current == NULL) {
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

    if (b->current) free(b->current);
    if (b->next) free(b->next);

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

    uint32_t cell_idx;

    for (int row = 0; row < board->rows; ++row) {

        cell.y = CELL_SIZE * row;

        for (int col = 0; col < board->cols; ++col) {

            cell.x = CELL_SIZE * col;
            cell_idx = row * board->cols + col;

            if (board->current[cell_idx])
                SDL_RenderFillRect(board->renderer, &cell);
        }
    }

    return 0;
}

void board_update(struct Board *board)
{
    uint32_t cell_idx;
    uint8_t neighbor_count;
    uint8_t is_alive;

    for (int row = 0; row < board->rows; ++row) {
        for (int col = 0; col < board->cols; ++col) {

            cell_idx = row * board->cols + col;
            neighbor_count = count_neighbors(board, row, col);

            is_alive = board->current[cell_idx];

            if (neighbor_count == 3) {
                board->next[cell_idx] = 1;
            } else if (is_alive && neighbor_count == 2) {
                board->next[cell_idx] = 1;
            } else {
                board->next[cell_idx] = 0;
            }
        }
    }

    uint8_t *tmp = board->current;
    board->current = board->next;
    board->next = tmp;
}

void board_reset(struct Board *board)
{
    uint32_t cell_idx;
    uint8_t random_cell_state;

    for (int row = 0; row < board->rows; ++row) {
        for (int col = 0; col < board->cols; ++col) {
            cell_idx = row * board->cols + col;
            random_cell_state = rand() % 2 == 0;
            board->current[cell_idx] = random_cell_state;
        }
    }
}

void board_clear(struct Board *board)
{
    uint32_t cell_idx;
    for (int row = 0; row < board->rows; ++row) {
        for (int col = 0; col < board->cols; ++col) {
            cell_idx = row * board->cols + col;
            board->current[cell_idx] = 0;
        }
    }
}

uint8_t count_neighbors(struct Board *b, int row, int col)
{
    uint8_t neighbor_count = 0;

    for (int r = row - 1; r <= row + 1; ++r) {
        for (int c = col - 1; c <= col + 1; ++c) {
            if (r == row && c == col) continue;
            if (WRAP_AROUND) {
                int wrap_r = (r + b->rows) % b->rows;
                int wrap_c = (c + b->cols) % b->cols;
                neighbor_count += b->current[wrap_r * b->cols + wrap_c];
            } else {
                if (r < 0 || r > b->rows || c < 0 || c > b->cols) continue;
                neighbor_count += b->current[r * b->cols + c];
            }
        }
    }

    return neighbor_count;
}
