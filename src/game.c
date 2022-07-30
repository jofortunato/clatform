#include "game.h"
#include "playground.h"

void start_game(GAME *game, ACTOR *actor)
{
    WINDOW *playground;

    actor->position.x = game->start.x;
    actor->position.y = game->start.y;

    playground = create_playground(game, actor);

    int ch;
    while ((ch = getch()) != KEY_LEFT)
    {
    }

    delwin(playground);
    endwin();
}