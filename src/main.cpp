#include "raylib.h"
#include "rlgl.h"

int main()
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Hello World");
    // Load textures
    Texture2D player = LoadTexture("../assets/human/idle/base_idle_strip9.png");
    SetTextureFilter(player, RL_TEXTURE_FILTER_NEAREST);
    int playerFrameWidth = player.width / 9;
    int playerFrameHeight = player.height;
    Vector2 playerPosition = {350.0f, 300.0f};
    Rectangle frameRec = {0.0f, 0.0f, (float)playerFrameWidth, (float)playerFrameHeight};

    float playerSpeed = 4;
    int framesCounter = 0;
    int framesSpeed = 10;
    int currentFrame = 0;

    Camera2D camera = {0};
    camera.target = (Vector2){playerPosition.x + 20.0f, playerPosition.y + 20.0f};
    camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
    camera.zoom = 2.0f;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Update
        if (IsKeyDown(KEY_D))
        {
            playerPosition.x += playerSpeed;
            if (frameRec.width < 0)
            {
                frameRec.width = -frameRec.width;
            }
        }
        if (IsKeyDown(KEY_A))
        {
            playerPosition.x -= playerSpeed;
            if (frameRec.width > 0)
            {
                frameRec.width = -frameRec.width;
            }
        }

        if (IsKeyDown(KEY_W)) playerPosition.y -= playerSpeed;
        if (IsKeyDown(KEY_S)) playerPosition.y += playerSpeed;

        if (IsKeyPressed(KEY_Q)) camera.zoom += 1.0f;
        if (IsKeyPressed(KEY_E)) camera.zoom -= 1.0f;
        if (IsKeyPressed(KEY_R)) camera.zoom = 1.0f;


        camera.target = (Vector2){playerPosition.x + 20.0f, playerPosition.y + 20.0f};
        if (camera.zoom > 3.0f) camera.zoom = 3.0f;
        if (camera.zoom < 1.0f) camera.zoom = 1.0f;

        framesCounter++;
        if (framesCounter >= 60 / framesSpeed)
        {
            framesCounter = 0;
            currentFrame++;
            if (currentFrame > 8) currentFrame = 0;
            frameRec.x = (float)currentFrame * (float)playerFrameWidth;
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);
        DrawTextureRec(player, frameRec, playerPosition, WHITE);
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
