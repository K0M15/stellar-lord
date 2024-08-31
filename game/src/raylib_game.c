

#include "raylib.h"
#include "stellar.h"

static t_game game;

void action_cycle()
{
    cycle_game(&game);
}

void action_cylce_mult()
{
    int i = 10;
    while (--i)
    {
        cycle_game(&game);
    }
}

t_game *get_game()
{
    return &game;
}


// Create Logos for the buttons
// Implement ZOOM
// Implement AI
// make an overlay of how many ships to send
int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT+100, GAME_NAME);

    SetTargetFPS(60);

    if (!create_game(&game, 3, 1000))
    {
        fprintf(stderr, "Error initalizing the game");
    }
    t_player* player = game_request_player(&game, "Alain");
    t_player* player2 = game_request_player(&game, "Steffen");
    t_position uipos;
    uipos.x = 0;
    uipos.y = SCREEN_HEIGHT;
    ui_button_create(&game.ui, 'N', uipos, action_cycle);
    uipos.x += 100;
    ui_button_create(&game.ui, 'M', uipos, action_cylce_mult);
    // CREATE FIGHTS and OVERTAKES
    while (!WindowShouldClose())
    {
        handle_click( &game );
        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (game.selected_star)
            DrawCircle(
                game.selected_star->position.x,
                game.selected_star->position.y,
                100,
                game.selected_star->owner ? ColorBrightness(game.selected_star->owner->color, -.13) : RAYWHITE);
        for (int i = game.stars_filled; i; --i)
        {
            Vector2 vec = GetMousePosition();
            draw_star(&game.stars[i-1], vec);
        }
        t_cluster_list *list = game.clusters;
        while (list != NULL)
        {
            draw_ship_cluster(&list->data);
            list = list->next;
        }
        draw_ui(game.ui);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
