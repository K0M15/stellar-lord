/* ######################################## */
/* #                    27.08.2024        # */
/* #  war.c                               # */
/* #                 written by           # */
/* #                Alain Felger          # */
/* ######################################## */

#include "stellar.h"

void execute_war(t_ship_cluster* cluster)
{
	// 1 Ship on attackers side will destroy 0.8 on defender side
	// except when there are more then 15x the ships on attackers side,
	// then 1 Ships on defender will destroy .5 on attackers side
	float ratio = (float)cluster->amount / (float) cluster->target->ships;
	int orgClusterShips = cluster->amount;
	int orgTargetShips = cluster->target->ships;
	if (ratio >= 15)
	{
		cluster->amount -= (int) ((float)orgTargetShips / .8);
		cluster->target->ships -= orgClusterShips;
	}
	else
	{
		cluster->amount -= orgTargetShips;
		cluster->target->ships -= (int) ((float)orgClusterShips / .5);
	}
	if (cluster->amount < 0)
		cluster->amount = 0;
	if (cluster->target->ships < 0)
		cluster->target->ships = 0;
	int destroyedShips = (orgClusterShips - cluster->amount)
			+ (orgTargetShips - cluster->target->ships);
	while (--destroyedShips)
		cluster->target->population *= 0.995;
	if (cluster->target->ships == 0 && cluster->amount > 0)
	{
		star_set_owner(cluster->target, cluster->owner);
		cluster->target->ships = cluster->amount;
	}
}