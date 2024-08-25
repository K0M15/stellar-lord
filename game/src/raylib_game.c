

#include "raylib.h"
#include "stellar.h"

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_NAME);

    SetTargetFPS(60);

    t_game game;
    if (!create_game(&game, 3, 100))
    {
        fprintf(stderr, "Error initalizing the game");
    }

    while (!WindowShouldClose())
    {
        handle_click( &game );
        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int i = game.stars_filled; i; --i)
        {
            draw_star(&game.stars[i-1]);
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
