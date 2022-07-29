#ifndef H_GAME
#define H_GAME

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

#endif