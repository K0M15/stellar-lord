/* ######################################## */
/* #                    25.08.2024        # */
/* #  draw.c                              # */
/* #                 written by           # */
/* #                Alain Felger          # */
/* ######################################## */

#include "stellar.h"

int calc_star_size(t_star* star)
{
	return Clamp((star->population / 150), 2, 5);
}

void draw_star(t_star* star, Vector2 mouse)
{
	int size = calc_star_size(star);
	if (Vector2Distance(star->position, mouse) < 3)
		size += 3;
	if (star->owner != NULL)
	{
		DrawCircle((int)star->position.x,
			(int)star->position.y, size + 3, star->owner->color);
		if (star->owner->home == star)
		{
			DrawRectangle((int)star->position.x, (int)star->position.y - 1, 1, 3, RAYWHITE);
			DrawRectangle((int)star->position.x - 1, (int)star->position.y, 3, 1, RAYWHITE);
		}
	}
	else
		DrawCircle((int)star->position.x,
			(int)star->position.y, size, DARKGRAY);
}

void draw_ship_cluster(t_ship_cluster* cluster)
{
	t_position pos = get_cluster_pos(cluster, get_game()->cycle);
	DrawCircle(pos.x, pos.y, 2, cluster->owner->color);
}