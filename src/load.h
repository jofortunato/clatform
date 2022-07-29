#ifndef H_LOAD
#define H_LOAD
#include "game.h"
#define MAX_STRING 100

ACTOR *load_saved_game();
GAME *load_level(int level);
void add_platform(GAME *game, int x_start, int x_end, int y);
void add_stair(GAME *game, int x, int y_start, int y_end);
void add_coin(GAME *game, POS position);
void add_bot(GAME *game, POS position, int awarness);

#endif