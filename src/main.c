#include "main.h"
#include "game.h"

int main(void)
{
    int exit_status = 0;

    struct Game *game = NULL;

    if (game_new(&game) != 0) {
        fprintf(stderr, "Something went wrong.\n");
        exit_status = 1;
    }

    game_run(&game);

    return exit_status;
}
