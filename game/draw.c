/* ######################################## */
/* #                    25.08.2024        # */
/* #  draw.c                              # */
/* #                 written by           # */
/* #                Alain Felger          # */
/* ######################################## */

#include "stellar.h"

int calc_star_size(t_star* star)
{
	return (int)max((int)(star->population / 150), 4);
}

void draw_star(t_star* star)
{
	if(star->owner != NULL)
		DrawCircle((int)star->position.x,
			(int)star->position.y, calc_star_size(star), star->owner->color);
	else
		DrawCircle((int)star->position.x,
			(int)star->position.y, calc_star_size(star), DARKGRAY);
}

void draw_ship_cluster(t_ship_cluster* cluster)
{
	
}