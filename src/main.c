#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include "load.h"
#include "actor.h"
#include "game.h"

int main(void)
{
    ACTOR *actor = NULL;
    GAME *game = NULL;

    int user_input;

    do
    {
        user_input = main_menu();
        switch (user_input)
        {
        case 1:
            printf("Option 1. New Game\n");
            break;
        case 2:
            printf("Option 2. Load Game\n");
            if ((actor == NULL) & (game == NULL))
            {
                actor = load_saved_game();
                if (actor == NULL)
                {
                    printf("Saved game file not found!\n");
                }
                else
                {
                    game = load_level(actor->level);
                    if (game == NULL)
                    {
                        printf("Level file not found\n");
                        free(actor);
                        actor = NULL;
                    }
                }
            }
            else
            {
                printf("Game already loaded.\n");
            }
            break;
        case 3:
            // Exits the main menu via the do while condition.
            if ((actor == NULL) & (game == NULL))
            {
                free(actor);
                free(game);
            }
            break;
        default:
            printf("Wrong option. Try again, select between 1 and 3.\n");
        }
    } while (user_input != 3);

    return 0;
}