#ifndef H_PLAYGROUND
#define H_PLAYGROUND
#include "game.h"
#include <ncurses.h>

WINDOW *create_playground(GAME *game, ACTOR *actor);
void draw_game(GAME *game, ACTOR *actor, WINDOW *playground);
void print_platforms(PLATFORM *platform, WINDOW *playground, int cols, int lines);
void print_stairs(STAIR *stair, WINDOW *playground, int cols, int lines);
void print_coins(COIN *coin, WINDOW *playground, int cols, int lines);
void print_actor(ACTOR *actor, WINDOW *playground, int cols, int lines);

#endif