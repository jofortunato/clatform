#include "playground.h"

WINDOW *create_playground(GAME *game, ACTOR *actor)
{
    initscr();
    cbreak();
    timeout(500);
    keypad(stdscr, TRUE);
    noecho();

    refresh();

    WINDOW *local_win;

    int start_y = (LINES - game->y_max + 2) / 2;
    int start_x = (COLS - game->x_max + 2) / 2;

    local_win = newwin(game->y_max + 2, game->x_max + 2, start_y, start_x);

    draw_game(game, actor, local_win);

    return local_win;
}

void draw_game(GAME *game, ACTOR *actor, WINDOW *playground)
{
    box(playground, 0, 0);
    print_stairs(game->stairs, playground, game->x_max + 1, game->y_max + 1);
    print_platforms(game->platforms, playground, game->x_max + 1, game->y_max + 1);
    print_coins(game->coins, playground, game->x_max + 1, game->y_max + 1);

    print_actor(actor, playground, game->x_max + 1, game->y_max + 1);

    wrefresh(playground);
}

void print_platforms(PLATFORM *platform, WINDOW *playground, int cols, int lines)
{
    int i;
    while (platform != NULL)
    {
        for (i = 0; platform->start.x + i <= platform->end.x; i++)
        {
            mvwprintw(playground, lines - platform->start.y, platform->start.x + i, "#");
        }

        platform = platform->next;
    }
}

void print_stairs(STAIR *stair, WINDOW *playground, int cols, int lines)
{
    int i;
    while (stair != NULL)
    {
        for (i = 0; stair->start.y + i <= stair->end.y; i++)
        {
            mvwprintw(playground, lines - (stair->start.y + i), stair->start.x, "H");
        }

        stair = stair->next;
    }
}

void print_coins(COIN *coin, WINDOW *playground, int cols, int lines)
{
    attron(A_STANDOUT);
    while (coin != NULL)
    {
        mvwprintw(playground, lines - coin->position.y, coin->position.x, "$");

        coin = coin->next;
    }
    attroff(A_STANDOUT);
}

void print_actor(ACTOR *actor, WINDOW *playground, int cols, int lines)
{
    mvwprintw(playground, lines - actor->position.y, actor->position.x, "@");
    wmove(playground, lines - actor->position.y, actor->position.x);
}