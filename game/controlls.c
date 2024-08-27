/* ######################################## */
/* #                    25.08.2024        # */
/* #  controlls.                          # */
/* #                 written by           # */
/* #                Alain Felger          # */
/* ######################################## */

#include "stellar.h"

void handle_click(t_game *game)
{
	bool mouse_pressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
	if (!mouse_pressed)
		return ;
	Vector2 vec = GetMousePosition();
	t_star* s = get_star_by_pos(game, vec);
	if (vec.y > SCREEN_HEIGHT)
	{
		get_ui_action(game->ui, vec);
	}
	if (mouse_pressed && game->selected_star == NULL)
	{
		if (s != NULL)
		{
			game->selected_star= s;
			log_star(s);
		}
	}
	else if (mouse_pressed && s != NULL && game->selected_star != NULL)
	{
		t_ship_cluster* ships = send_ships(game->selected_star->ships, game->selected_star, s, game);
		s = NULL;
		game->selected_star = NULL;
	}
	else
	{
		game->selected_star = NULL;
	}
}

t_star* get_star_by_pos(t_game* game, Vector2 click)
{
	//if to slow: optimize using quad trees
	for (int i = 0; i < game->stars_filled; i++)
	{
		if(game->stars[i].owner != NULL)
			if (Vector2Distance(game->stars[i].position, click)
				<= calc_star_size(&game->stars[i])+3)
				return &game->stars[i];
		if (Vector2Distance(game->stars[i].position, click)
			<= calc_star_size(&game->stars[i]))
			return &game->stars[i];
	}
	return NULL;
}