#include "raylib.h"

typedef struct Player
{
    Vector2 position;
    Vector2 speed;
    Texture2D texture;
    Color color;

    int currentFrame;
    Rectangle frameRec;
} Player;

static constexpr int screenWidth = 800;
static constexpr int screenHeight = 600;

static int framesCounter = 0;

static Player player = {0};
static Camera2D camera = {0};

int main()
{
    // Initialization
    InitWindow(screenWidth, screenHeight, "Hello World");
    // Load textures
    player.texture = LoadTexture("../resources/human/idle/base_idle_strip9.png");
    player.position = {350.0f, 300.0f};
    player.currentFrame = player.texture.width / 9;
    player.frameRec = {0.0f, 0.0f, (float)player.currentFrame, (float)player.texture.height};
    player.color = WHITE;

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
            if (player.frameRec.width < 0)
            {
                player.frameRec.width = -player.frameRec.width;
            }
        }
        if (IsKeyDown(KEY_LEFT))
        {
            player.position.x -= playerSpeed;
            if (player.frameRec.width > 0)
            {
                player.frameRec.width = -player.frameRec.width;
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
            player.frameRec.x = (float)currentFrame * (float)player.currentFrame;
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);
        DrawTextureRec(player.texture, player.frameRec, player.position, player.color);
        DrawText("Hello World!", 350, 300, 20, LIGHTGRAY);
        EndMode2D();

        DrawFPS(10, 10);
        EndDrawing();
    }
    // De-Initialization
    UnloadTexture(player.texture);

    CloseWindow();
    return 0;
}
