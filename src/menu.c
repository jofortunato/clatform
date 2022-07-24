#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

void main_menu(void)
{
    int menu_opt = 0;
    char user_input[3];

    do
    {
        print_menu_intro();

        printf("1. New Game\n");
        printf("2. Load Game\n");
        printf("3. Exit\n");

        printf("Select Option [1-3]:");
        fgets(user_input, 3, stdin);
        menu_opt = atoi(user_input);

        switch (menu_opt)
        {
        case 1:
            printf("Option 1. New Game\n");
            break;
        case 2:
            printf("Option 2. Load Game\n");
            break;
        case 3:
            // Exits the main menu via the do while condition.
            break;
        default:
            printf("Wrong option. Try again, select between 1 and 3.\n");
        }
    } while (menu_opt != 3);
}

void print_menu_intro(void)
{
    printf("======================================\n");
    printf("============== Clatform ==============\n");
    printf("======== a platform adventure ========\n");
    printf("======================================\n");
    printf("\n");
}