#include "raylib.h"

int main() {

    InitWindow(800, 600, "Hello World");
    SetTargetFPS(60);


    while (!WindowShouldClose()) {

        //update


        //draw

        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("Hello World!", 350, 300, 20, LIGHTGRAY);
        EndDrawing();


    }

    CloseWindow();
    return 0;
}
