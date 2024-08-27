/* ######################################## */
/* #                    27.08.2024        # */
/* #  ui.h                                # */
/* #                 written by           # */
/* #                Alain Felger          # */
/* ######################################## */

#ifndef UI_H
# define UI_H

# include "raylib.h"
# include <stdlib.h>

typedef struct s_button
{
    Vector2  pos;
    void        (*action_click)();
    char        display_character;
}   t_button;

typedef struct s_button_list
{
    struct s_button_list* next;
    t_button *data;
}   t_button_list;

typedef struct s_ui
{
    t_button_list* buttons;
}   t_ui;

bool    is_inside(Vector2 posStart, float width, float height, Vector2 pointer);
int     create_ui(t_ui* ui);
int     ui_button_create(t_ui* ui, char* display, Vector2 pos, void(*action)());
void    get_ui_action(t_ui* ui, Vector2 pointer);


void draw_button(t_button* button);
void draw_ui(t_ui* ui);

#endif /* UI_H */