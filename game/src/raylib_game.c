

#include "raylib.h"
#include "stellar.h"

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_NAME);

    SetTargetFPS(60);

    t_game game;
    create_game(&game, 3, 10);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int i = game.stars_filled; i + 1; --i)
        {
            draw_star(&game.stars[i]);
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
