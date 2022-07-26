#include <stdio.h>
#include <stdlib.h>
#include "load.h"

ACTOR *load_saved_game()
{
    ACTOR *saved_actor;
    saved_actor = (ACTOR *)malloc(sizeof(ACTOR));

    return saved_actor;
}