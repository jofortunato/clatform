#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "load.h"
#include "game.h"

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

    fclose(f);

    return saved_actor;
}

GAME *load_level(int level)
{
    char level_filename[20];
    sprintf(level_filename, "saves/level_%d.txt", level);

    char topic[MAX_STRING];
    FILE *f = fopen(level_filename, "r");

    if (f == NULL)
    {
        return NULL;
    }

    GAME *game;
    game = (GAME *)malloc(sizeof(GAME));
    game->platforms = NULL;
    game->stairs = NULL;
    game->coins = NULL;
    game->bots = NULL;

    int platform_x_start, platform_x_end, platform_y;
    int stair_y_start, stair_y_end, stair_x;
    POS coin_position;
    POS bot_position;
    int bot_awarness;

    while (fscanf(f, "%[^-\n ] ", topic) != EOF)
    {
        if (strcmp(topic, "GAMEPLAY") == 0)
        {
            fscanf(f, "%i %i\n", &game->x_max, &game->y_max);
        }
        else if (strcmp(topic, "PLATFORM") == 0)
        {
            fscanf(f, "%i %i %i\n", &platform_x_start, &platform_x_end, &platform_y);
            add_platform(game, platform_x_start, platform_x_end, platform_y);
        }
        else if (strcmp(topic, "STAIR") == 0)
        {
            fscanf(f, "%i %i %i\n", &stair_x, &stair_y_start, &stair_y_end);
            add_stair(game, stair_x, stair_y_start, stair_y_end);
        }
        else if (strcmp(topic, "COIN") == 0)
        {
            fscanf(f, "%i %i\n", &coin_position.x, &coin_position.y);
            add_coin(game, coin_position);
        }
        else if (strcmp(topic, "BOT") == 0)
        {
            fscanf(f, "%i %i %i\n", &bot_position.x, &bot_position.y, &bot_awarness);
            add_bot(game, bot_position, bot_awarness);
        }
        else if (strcmp(topic, "START") == 0)
        {
            fscanf(f, "%i %i\n", &game->start.x, &game->start.y);
        }
        else if (strcmp(topic, "END") == 0)
        {
            fscanf(f, "%i %i\n", &game->end.x, &game->end.y);
        }
    }

    fclose(f);

    return game;
}

void add_platform(GAME *game, int x_start, int x_end, int y)
{
    PLATFORM *platform;
    platform = malloc(sizeof(PLATFORM));

    platform->start.x = x_start;
    platform->start.y = y;
    platform->end.x = x_end;
    platform->end.y = y;

    platform->next = game->platforms;
    game->platforms = platform;
}

void add_stair(GAME *game, int x, int y_start, int y_end)
{
    STAIR *stair;
    stair = malloc(sizeof(STAIR));

    stair->start.x = x;
    stair->start.y = y_start;
    stair->end.x = x;
    stair->end.y = y_end;

    stair->next = game->stairs;
    game->stairs = stair;
}

void add_coin(GAME *game, POS position)
{
    COIN *coin;
    coin = malloc(sizeof(COIN));

    coin->position = position;

    coin->next = game->coins;
    game->coins = coin;
}

void add_bot(GAME *game, POS position, int awarness)
{
    BOT *bot;
    bot = malloc(sizeof(BOT));

    bot->position = position;
    bot->awarness = awarness;

    bot->next = game->bots;
    game->bots = bot;
}

void free_game(GAME *game)
{
    PLATFORM *aux_platform;

    while (game->platforms != NULL)
    {
        aux_platform = game->platforms;
        game->platforms = game->platforms->next;
        free(aux_platform);
    }

    while (game->stairs != NULL)
    {
        STAIR *aux_stair;
        aux_stair = game->stairs;

        game->stairs = game->stairs->next;
        free(aux_stair);
    }

    while (game->coins != NULL)
    {
        COIN *aux_coin;
        aux_coin = game->coins;

        game->coins = game->coins->next;
        free(aux_coin);
    }

    while (game->bots != NULL)
    {
        BOT *aux_bot;
        aux_bot = game->bots;

        game->bots = game->bots->next;
        free(aux_bot);
    }

    free(game);
}