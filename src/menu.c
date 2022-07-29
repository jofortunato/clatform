#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

int main_menu(void)
{
    int menu_opt = 0;
    char user_input[3];

    print_menu_intro();

    printf("1. New Game\n");
    printf("2. Load Game\n");
    printf("3. Exit\n");

    printf("Select Option [1-3]:");
    fgets(user_input, 3, stdin);
    menu_opt = atoi(user_input);

    return menu_opt;
}

void print_menu_intro(void)
{
    printf("======================================\n");
    printf("============== Clatform ==============\n");
    printf("======== a platform adventure ========\n");
    printf("======================================\n");
    printf("\n");
}