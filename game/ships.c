/* ######################################## */
/* #                    25.08.2024        # */
/* #  ships.c                             # */
/* #                 written by           # */
/* #                Alain Felger          # */
/* ######################################## */

#include "stellar.h"

t_ship_cluster* send_ships(int ship_amount, t_star* origin, t_star* target, t_game* game)
{
	if (!check_target_range(origin, target))
		return NULL;
	t_ship_cluster *cluster = malloc(sizeof(t_ship_cluster));
	if (cluster == NULL)
		return NULL;
	cluster->amount = ship_amount;
	cluster->cycle_start = game->cycle;
	cluster->origin = origin;
	cluster->target = target;
	cluster->owner = origin->owner;
	return cluster;
}

int check_target_range(t_star* origin, t_star* target)
{
	return (Vector2Distance(origin->position, target->position) < MAX_SHIP_RANGE);
}
