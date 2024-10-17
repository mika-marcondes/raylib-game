#include "raylib.h"

int main()
{
    InitWindow(800, 600, "Hello World");
    // Load textures
    Texture2D player = LoadTexture("../assets/human/idle/base_idle_strip9.png");
    Rectangle frameRec = {0.0f, 0.0f, (float)player.width / 9, (float)player.height};
    Vector2 position = {350.0f, 300.0f};

    int framesCounter = 0;
    int framesSpeed = 10;
    int currentFrame = 0;

    SetTargetFPS(60);


    while (!WindowShouldClose())
    {
        //update
        framesCounter++;
        if (framesCounter >= 60 / framesSpeed)
        {
            framesCounter = 0;
            currentFrame++;
            if (currentFrame > 8) currentFrame = 0;
            frameRec.x = (float)currentFrame * (float)player.width / 9;
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureRec(player, frameRec, position, WHITE);
        DrawText("Hello World!", 350, 300, 20, LIGHTGRAY);
        DrawFPS(10, 10);

        EndDrawing();
    }

    // De-Initialization
    UnloadTexture(player);

    CloseWindow();
    return 0;
}
