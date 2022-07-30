#include "game.h"
#include "playground.h"

void start_game(GAME *game, ACTOR *actor)
{
    WINDOW *playground;

    actor->position.x = game->start.x;
    actor->position.y = game->start.y;

    playground = create_playground(game, actor);

    int ch;
    while ((ch = getch()) != 113) // Press q (ascii value 113) key to exit
    {
        switch (ch)
        {
        case KEY_RIGHT:
            actor->position.x++;

            werase(playground);
            draw_game(game, actor, playground);
            break;
        case KEY_LEFT:
            actor->position.x--;

            werase(playground);
            draw_game(game, actor, playground);
            break;
        case KEY_UP:
            actor->position.y++;

            werase(playground);
            draw_game(game, actor, playground);
            break;
        case KEY_DOWN:
            actor->position.y--;

            werase(playground);
            draw_game(game, actor, playground);
            break;
        default:
            break;
        }
    }

    delwin(playground);
    endwin();
}