#include "raylib.h"

int main()
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Hello World");
    // Load textures
    Texture2D player = LoadTexture("../assets/human/idle/base_idle_strip9.png");
    Rectangle frameRec = {0.0f, 0.0f, (float)player.width / 9, (float)player.height};
    Vector2 playerPos = {350.0f, 300.0f};

    float playerSpeed = 4;
    int framesCounter = 0;
    int framesSpeed = 10;
    int currentFrame = 0;


    Camera2D camera = {0};
    camera.target = (Vector2){playerPos.x + 20.0f, playerPos.y + 20.0f};
    camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
    camera.zoom = 1.0f;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        //update
        if (IsKeyDown(KEY_RIGHT)) playerPos.x += playerSpeed;
        if (IsKeyDown(KEY_LEFT)) playerPos.x -= playerSpeed;
        if (IsKeyDown(KEY_UP)) playerPos.y -= playerSpeed;
        if (IsKeyDown(KEY_DOWN)) playerPos.y += playerSpeed;

        if (IsKeyPressed(KEY_Q)) camera.zoom += 0.5f;
        if (IsKeyPressed(KEY_E)) camera.zoom -= 0.5f;
        if (IsKeyPressed(KEY_R)) camera.zoom = 1.0f;

        camera.target = (Vector2){playerPos.x + 20.0f, playerPos.y + 20.0f};
        if (camera.zoom > 3.0f) camera.zoom = 3.0f;
        if (camera.zoom < 0.1f) camera.zoom = 0.1f;

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
        BeginMode2D(camera);
        DrawTextureRec(player, frameRec, playerPos, WHITE);
        DrawText("Hello World!", 350, 300, 20, LIGHTGRAY);
        EndMode2D();
        DrawFPS(10, 10);

        EndDrawing();
    }


    // De-Initialization
    UnloadTexture(player);

    CloseWindow();
    return 0;
}
