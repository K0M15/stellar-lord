/* ######################################## */
/* #                    23.08.2024        # */
/* #  star.c                              # */
/* #                 written by           # */
/* #                Alain Felger          # */
/* ######################################## */

#include "stellar.h"

t_star* generate_star(t_star* result, t_position pos, float population)
{
    result->position.x = pos.x;
    result->position.y = pos.y;
    result->population = population;
    result->ships = 0;
    result->owner = NULL;

    return (result);
}

void cycle_star(t_star* star)
{
    //TODO add handler for overflow
    star->population *= POPULATION_FACTOR + 1;
    Clamp(star->population, 0, MAX_POPULATION);
    star->ships += (star->owner != NULL) * (star->population * 0.005 + 1);
}

void destruct_star(t_star* star)
{
    free(star);
}

void log_star(t_star* star)
{
    printf("Pop: %.1f   Pos:%.1f,%.1f   Ships:%d    Owner: %s\n",
        star->population, star->position.x, star->position.y,
        star->ships, star->owner == NULL?NULL: star->owner->name);
}

void get_new_homestar(t_game* game, t_star** star)
{
    int is_possible, j, i = 0;
    while (i < game->stars_filled)
    {
        is_possible = 1;
        j = 0;
        while (j < game->players_filled)
        {
            if (Vector2Distance(game->players[j].home->position,
                    game->stars[i].position) < MIN_PLAYER_HOME_DIST)
            {
                is_possible = 0;
                break;
            }
            j++;
        }
        if (is_possible && game->stars[i].owner == NULL)
        {
            *star = &game->stars[i];
            return;
        }
        i++;
    }
}

void set_owner(t_star* star, t_player* player)
{
    star->owner = player;
}