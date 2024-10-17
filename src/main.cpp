#include "raylib.h"

typedef struct Player
{
    Vector2 position;
    Vector2 speed;
    Texture2D idle;
} Player;

static const int screenWidth = 800;
static const int screenHeight = 600;

static int framesCounter = 0;

static Player player = {0};
static Camera2D camera = {0};

int main()
{
    // Initialization
    InitWindow(screenWidth, screenHeight, "Hello World");
    // Load textures
    player.idle = LoadTexture("../resources/human/idle/base_idle_strip9.png");
    player.position = {350.0f, 300.0f};

    int playerFrameWidth = player.idle.width / 9;
    int playerFrameHeight = player.idle.height;

    Rectangle frameRec = {0.0f, 0.0f, (float)playerFrameWidth, (float)playerFrameHeight};

    float playerSpeed = 4;
    int framesSpeed = 10;
    int currentFrame = 0;

    camera.target = (Vector2){player.position.x + 20.0f, player.position.y + 20.0f};
    camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
    camera.zoom = 2.0f;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Update
        if (IsKeyDown(KEY_RIGHT))
        {
            player.position.x += playerSpeed;
            if (frameRec.width < 0)
            {
                frameRec.width = -frameRec.width;
            }
        }
        if (IsKeyDown(KEY_LEFT))
        {
            player.position.x -= playerSpeed;
            if (frameRec.width > 0)
            {
                frameRec.width = -frameRec.width;
            }
        }
        if (IsKeyDown(KEY_UP)) player.position.y -= playerSpeed;
        if (IsKeyDown(KEY_DOWN)) player.position.y += playerSpeed;

        if (IsKeyPressed(KEY_Q)) camera.zoom += 1.0f;
        if (IsKeyPressed(KEY_E)) camera.zoom -= 1.0f;
        if (IsKeyPressed(KEY_R)) camera.zoom = 1.0f;

        camera.target = (Vector2){player.position.x + 20.0f, player.position.y + 20.0f};
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
        DrawTextureRec(player.idle, frameRec, player.position, WHITE);
        DrawText("Hello World!", 350, 300, 20, LIGHTGRAY);
        EndMode2D();

        DrawFPS(10, 10);
        EndDrawing();
    }
    // De-Initialization
    UnloadTexture(player.idle);

    CloseWindow();
    return 0;
}
