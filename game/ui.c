/* ######################################## */
/* #                    27.08.2024        # */
/* #  ui.c                                # */
/* #                 written by           # */
/* #                Alain Felger          # */
/* ######################################## */

// UI should be drawn from one element
#include "ui.h"

bool is_inside(Vector2 posStart, float width, float height, Vector2 pointer)
{
	if (pointer.x >= posStart.x
		&& pointer.y >= posStart.y
		&& pointer.x <= posStart.x + width
		&& pointer.y <= posStart.y + height)
		return 1;
	return 0;
}

int create_ui(t_ui* ui)
{
	ui->buttons = NULL;
	return 1;
}

int ui_button_create(t_ui* ui, char* display, Vector2 pos, void(*action)())
{
	t_button_list* butt = malloc(sizeof(t_button_list));
	if (butt == NULL)
		return 0;
	t_button *data = malloc(sizeof(t_button));
	butt->data = data;
	butt->data->pos.x = pos.x;
	butt->data->pos.y = pos.y;
	butt->data->action_click = action;
	butt->data->display_character = display;
	butt->next = NULL;
	t_button_list* list = ui->buttons;
	if(ui->buttons == NULL)
	{
		ui->buttons = butt;
		return 1;
	}
	while (list->next != NULL)
		list = list->next;
	list->next = butt;
	return 1;
}

void get_ui_action(t_ui* ui, Vector2 pointer)
{
	t_button_list* list = ui->buttons;
	while (list != NULL)
	{
		if (is_inside(list->data->pos, 100, 100, pointer))
		{
			list->data->action_click();
			return ;
		}
		list = list->next;
	}
}