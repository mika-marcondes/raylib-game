#include "raylib.h"

typedef struct Player
{
    Vector2 position;
    Vector2 speed;
    Color color;
    Texture2D texture;

    int frameSize;
    int frameCurrent;
    Rectangle frameRec;
} Player;


static constexpr int screenWidth = 800;
static constexpr int screenHeight = 600;

static int frameCounter = 0;
static int currentFrame = 0;
static int frameSpeed = 15;
static float playerSpeed = 4.0f;

static Player player = {0};
static Camera2D camera = {0};

void InitCamera()
{
    camera.target = (Vector2){player.position.x + 20.0f, player.position.y + 20.0f};
    camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
    camera.zoom = 2.0f;
}

void InitPlayer(Texture2D texture, const int frameSize)
{
    player.texture = texture;
    player.position = Vector2(350.0f, 300.0f);
    player.frameSize = frameSize;
    player.frameCurrent = player.texture.width / player.frameSize;
    player.frameRec = {0.0f, 0.0f, (float)player.frameCurrent, (float)player.texture.height};
    player.color = WHITE;
}

void UpdateTexture(Texture2D texture, const int frameSize)
{
    player.texture = texture;
    player.frameSize = frameSize;
}

int main()
{
    // Initialization
    InitWindow(screenWidth, screenHeight, "Hello World");
    Texture2D animRun = LoadTexture("../resources/human/base_run_strip8.png");
    Texture2D animIdle = LoadTexture("../resources/human/base_idle_strip9.png");
    InitPlayer(animIdle, 9);
    InitCamera();

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Update
        if (IsKeyDown(KEY_RIGHT))
        {
            player.position.x += playerSpeed;
            UpdateTexture(animRun, 8);
            if (player.frameRec.width < 0)
            {
                player.frameRec.width = -player.frameRec.width;
            }
        }
        if (IsKeyReleased(KEY_RIGHT))
        {
            UpdateTexture(animIdle, 9);
        }
        if (IsKeyDown(KEY_LEFT))
        {
            player.position.x -= playerSpeed;
            UpdateTexture(animRun, 8);
            if (player.frameRec.width > 0)
            {
                player.frameRec.width = -player.frameRec.width;
            }
        }
        if (IsKeyReleased(KEY_LEFT))
        {
            UpdateTexture(animIdle, 9);
        }
        if (IsKeyDown(KEY_UP))
        {
            player.position.y -= playerSpeed;
            UpdateTexture(animRun, 8);
        }
        if (IsKeyReleased(KEY_UP))
        {
            UpdateTexture(animIdle, 9);
        }
        if (IsKeyDown(KEY_DOWN))
        {
            player.position.y += playerSpeed;
            UpdateTexture(animRun, 8);
        }
        if (IsKeyReleased(KEY_DOWN))
        {
            UpdateTexture(animIdle, 9);
        }

        if (IsKeyPressed(KEY_Q)) camera.zoom += 1.0f;
        if (IsKeyPressed(KEY_E)) camera.zoom -= 1.0f;
        if (IsKeyPressed(KEY_R)) camera.zoom = 1.0f;

        camera.target = (Vector2){player.position.x + 20.0f, player.position.y + 20.0f};
        if (camera.zoom > 3.0f) camera.zoom = 3.0f;
        if (camera.zoom < 1.0f) camera.zoom = 1.0f;

        frameCounter++;
        if (frameCounter >= 60 / frameSpeed)
        {
            frameCounter = 0;
            currentFrame++;
            if (currentFrame > player.frameSize - 1) currentFrame = 0;
            player.frameRec.x = (float)currentFrame * (float)player.frameCurrent;
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
    UnloadTexture(animIdle);
    UnloadTexture(animRun);

    CloseWindow();
    return 0;
}
