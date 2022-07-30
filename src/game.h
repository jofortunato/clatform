#ifndef H_GAME
#define H_GAME
#include <ncurses.h>
#include <stdbool.h>
#define MAX_CHARS 50

typedef enum
{
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3,
} NEXT_MOVE;

typedef struct POS
{
    int x;
    int y;
} POS;

typedef struct PLATFORM
{
    POS start;
    POS end;

    struct PLATFORM *next;
} PLATFORM;

typedef struct STAIR
{
    POS start;
    POS end;

    struct STAIR *next;
} STAIR;

typedef struct COIN
{
    POS position;

    struct COIN *next;
} COIN;

typedef struct BOT
{
    POS position;
    int awarness;

    struct BOT *next;
} BOT;

typedef struct GAME
{
    int x_max;
    int y_max;

    POS start;
    POS end;

    PLATFORM *platforms;
    STAIR *stairs;
    COIN *coins;
    BOT *bots;

} GAME;

typedef struct ACTOR
{
    char name[MAX_CHARS];
    int health;
    int coins;
    int level;
    POS position;
} ACTOR;

void start_game(GAME *game, ACTOR *actor);
bool is_valid_movement(NEXT_MOVE next_move, ACTOR *actor, GAME *game);
bool is_outside_playground(POS position, GAME *game);
bool has_platform(POS position, PLATFORM *platform);
bool has_stair(POS position, STAIR *stair);
#endif