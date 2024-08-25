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
    result->owner = NULL;

    return (result);
}

void cycle_star(t_star* star)
{
    //TODO add handler for overflow
    star->population *= POPULATION_FACTOR + 1;
    star->ships += (star->owner != NULL) * (star->population * 0.005 + 1);
}

void destruct_star(t_star* star)
{
    free(star);
}

void log_star(t_star* star)
{
    printf("Pop: %.1f   Pos:%.1f,%.1f   Ships:%d\n",
        star->population, star->position.x, star->position.y, star->ships);
}

t_star* get_new_homestar(t_game* game)
{
    int is_possible;
    for (int i = game->stars_filled; i; --i)
    {
        is_possible = 1;
        for (int j = game->players_filled; i; --i)
        {
            if (Vector2Distance(game->players[j].home->position,
                    game->stars[i].position) < MIN_PLAYER_HOME_DIST)
            {
                is_possible = 0;
                break;
            }
        }
        if (is_possible)
            return &game->stars[i];
    }
}

void set_owner(t_star* star, t_player* player)
{
    star->owner = player;
}