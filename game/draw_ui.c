/* ######################################## */
/* #                    27.08.2024        # */
/* #  ui.h                                # */
/* #                 written by           # */
/* #                Alain Felger          # */
/* ######################################## */

#include "ui.h"

void draw_ui(t_ui* ui)
{
	t_button_list *list = ui->buttons;
	while (list != NULL)
	{
		draw_button(list->data);
		list = list->next;
	}
}

void draw_button(t_button* button)
{
	char* str[2];
	str[0] = button->display_character;
	str[1] = 0;
	DrawRectangle(button->pos.x, button->pos.y, 100, 100, LIGHTGRAY);
	DrawText(str, button->pos.x + 20, button->pos.y + 10, 90, RAYWHITE);
}