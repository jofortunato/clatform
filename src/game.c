#include "game.h"
#include "playground.h"

void start_game(GAME *game, ACTOR *actor)
{
    WINDOW *playground;

    actor->position.x = game->start.x;
    actor->position.y = game->start.y;

    playground = create_playground(game, actor);

    int ch;
    NEXT_MOVE next_move;
    bool actor_is_falling;

    while ((ch = getch()) != 113) // Press q (ascii value 113) key to exit
    {
        actor_is_falling = is_falling(actor, game);

        switch (ch)
        {
        case KEY_RIGHT:
            next_move = RIGHT;
            if (is_valid_movement(next_move, actor, game))
            {
                actor->position.x++;

                werase(playground);
                draw_game(game, actor, playground);
            }
            break;
        case KEY_LEFT:
            next_move = LEFT;
            if (is_valid_movement(next_move, actor, game))
            {
                actor->position.x--;

                werase(playground);
                draw_game(game, actor, playground);
            }
            break;
        case KEY_UP:
            next_move = UP;
            if (is_valid_movement(next_move, actor, game))
            {
                actor->position.y++;
                werase(playground);
                draw_game(game, actor, playground);
            }
            break;
        case KEY_DOWN:
            next_move = DOWN;
            if (is_valid_movement(next_move, actor, game))
            {
                actor->position.y--;

                werase(playground);
                draw_game(game, actor, playground);
            }
            break;
        case 112: // Pause: 112 is ascii value for 'p'
            // Add Here Function to Print Paused over the screen...

            while ((ch = getch()) != 112)
            {
            }
            break;
        default:
            break;
        }

        while (actor_is_falling)
        {
            usleep(50000);
            next_move = DOWN;
            if (is_valid_movement(next_move, actor, game))
            {
                actor->position.y--;

                werase(playground);
                draw_game(game, actor, playground);
            }
            actor_is_falling = is_falling(actor, game);
        }
    }

    delwin(playground);
    endwin();
}

bool is_valid_movement(NEXT_MOVE next_move, ACTOR *actor, GAME *game)
{
    POS new_position = actor->position;

    switch (next_move)
    {
    case UP:
        new_position.y++;
        if (is_outside_playground(new_position, game))
        {
            return false;
        }
        else if (has_platform(new_position, game->platforms) && !has_stair(new_position, game->stairs))
        {
            return false;
        }

        break;
    case RIGHT:
        new_position.x++;
        if (is_outside_playground(new_position, game))
        {
            return false;
        }
        else if (has_platform(new_position, game->platforms))
        {
            return false;
        }

        break;
    case DOWN:
        new_position.y--;
        if (is_outside_playground(new_position, game))
        {
            return false;
        }
        else if (has_platform(new_position, game->platforms) && !has_stair(new_position, game->stairs))
        {
            return false;
        }

        break;
    case LEFT:
        new_position.x--;
        if (is_outside_playground(new_position, game))
        {
            return false;
        }
        else if (has_platform(new_position, game->platforms))
        {
            return false;
        }

        break;

    default:
        break;
    }
    return true;
}

bool is_outside_playground(POS position, GAME *game)
{
    if (position.x == 0)
    {
        return true;
    }
    else if (position.x == game->x_max + 1)
    {
        return true;
    }
    else if (position.y == 0)
    {
        return true;
    }
    else if (position.y == game->y_max + 1)
    {
        return true;
    }

    return false;
}

bool has_platform(POS position, PLATFORM *platform)
{
    while (platform != NULL)
    {
        if (platform->start.y == position.y && (position.x >= platform->start.x && position.x <= platform->end.x))
        {
            return true;
        }
        platform = platform->next;
    }

    return false;
}

bool has_stair(POS position, STAIR *stair)
{
    while (stair != NULL)
    {
        if (stair->start.x == position.x && (position.y >= stair->start.y && position.y <= stair->end.y))
        {
            return true;
        }
        stair = stair->next;
    }

    return false;
}

bool is_falling(ACTOR *actor, GAME *game)
{
    POS floor;
    floor.x = actor->position.x;
    floor.y = actor->position.y - 1;

    if (has_stair(actor->position, game->stairs))
    {
        return false;
    }
    else if (has_platform(floor, game->platforms))
    {
        return false;
    }

    return true;
}