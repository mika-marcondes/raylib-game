#include "raylib.h"

int main()
{
    InitWindow(800, 600, "Hello World");
    // Load textures
    Texture2D player = LoadTexture("../assets/human/idle/base_idle_strip9.png");
    Rectangle frameRec = {0.0f, 0.0f, (float)player.width / 9, (float)player.height};
    Vector2 position = {350.0f, 300.0f};

    SetTargetFPS(60);


    while (!WindowShouldClose())
    {
        //update


        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(player, position.x, position.y, WHITE);
        DrawText("Hello World!", 350, 300, 20, LIGHTGRAY);
        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
