#ifndef H_ACTOR
#define H_ACTOR

#define MAX_CHARS 50

typedef struct ACTOR
{
    char name[MAX_CHARS];
    int health;
    int coins;
    int level;
} ACTOR;

#endif