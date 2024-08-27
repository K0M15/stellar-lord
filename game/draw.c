/* ######################################## */
/* #                    25.08.2024        # */
/* #  draw.c                              # */
/* #                 written by           # */
/* #                Alain Felger          # */
/* ######################################## */

#include "stellar.h"

int calc_star_size(t_star* star)
{
	return Clamp((star->population / 150), 0, 8);
}

void draw_star(t_star* star)
{
	if (star->owner != NULL)
	{
			if (star->owner->home == star)
			{
				DrawRectangle((int)star->position.x, (int)star->position.y - 1, 1, 3, RAYWHITE);
				DrawRectangle((int)star->position.x - 1, (int)star->position.y, 3, 1, RAYWHITE);
			}
		DrawCircle((int)star->position.x,
			(int)star->position.y, calc_star_size(star)+3, star->owner->color);
	}
	else
		DrawCircle((int)star->position.x,
			(int)star->position.y, calc_star_size(star), DARKGRAY);
}

void draw_ship_cluster(t_ship_cluster* cluster)
{
	t_position pos = get_cluster_pos(cluster, get_game()->cycle);
	DrawCircle(pos.x, pos.y, 2, cluster->owner->color);
}