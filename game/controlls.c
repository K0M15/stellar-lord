/* ######################################## */
/* #                    25.08.2024        # */
/* #  controlls.                          # */
/* #                 written by           # */
/* #                Alain Felger          # */
/* ######################################## */

#include "stellar.h"

void handle_click(t_game *game)
{
	static t_star *is_selected;

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && is_selected == NULL)
	{
		Vector2 vec = GetMousePosition();
		t_star* s = get_star_by_pos(game, vec);
		if (s != NULL)
		{
			is_selected = s;
			log_star(s);
		}
	}
	else
	{
		is_selected = NULL;
	}
}

t_star* get_star_by_pos(t_game* game, Vector2 click)
{
	//if to slow: optimize using quad trees
	for (int i = game->stars_filled; i; --i)
	{
		if (Vector2Distance(game->stars[i - 1].position, click)
			<= calc_star_size(&game->stars[i - 1]))
			return &game->stars[i - 1];
	}
	return NULL;
}