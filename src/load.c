#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "load.h"

ACTOR *load_saved_game()
{
    char topic[MAX_STRING];
    FILE *f = fopen("saves/last_game.txt", "r");

    if (f == NULL)
    {
        return NULL;
    }

    ACTOR *saved_actor;
    saved_actor = (ACTOR *)malloc(sizeof(ACTOR));

    while (fscanf(f, "%[^-\n ] ", topic) != EOF)
    {
        if (strcmp(topic, "NAME") == 0)
        {
            fscanf(f, "%s\n", saved_actor->name);
        }
        else if (strcmp(topic, "HEALTH") == 0)
        {
            fscanf(f, "%i\n", &saved_actor->health);
        }
        else if (strcmp(topic, "COINS_NUMBER") == 0)
        {
            fscanf(f, "%i\n", &saved_actor->coins);
        }
        else if (strcmp(topic, "CURRENT_LEVEL") == 0)
        {
            fscanf(f, "%i\n", &saved_actor->level);
        }
    }

    return saved_actor;
}