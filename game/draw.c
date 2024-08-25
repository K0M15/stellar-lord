/* ######################################## */
/* #                    25.08.2024        # */
/* #  draw.c                              # */
/* #                 written by           # */
/* #                Alain Felger          # */
/* ######################################## */

#include "stellar.h"

void draw_star(t_star* star)
{
	if(star->owner != NULL)
		DrawCircle((int)star->position.x, (int)star->position.y, 4, star->owner->color);
	else
		DrawCircle((int)star->position.x, (int)star->position.y, 4, DARKGRAY);
}

void draw_ship_cluster(t_ship_cluster* cluster)
{
	
}