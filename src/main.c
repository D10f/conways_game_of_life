#include "main.h"
#include "game.h"

int main(void)
{
    int exit_status = 1;

    struct Game *game = NULL;

    if (game_new(&game) == 0) {
        game_run(game);
        exit_status = 0;
    }

    game_free(&game);

    return exit_status;
}
