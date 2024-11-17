#include "raylib.h"
#include "raymath.h"

#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

static constexpr int screenWidth = 800;
static constexpr int screenHeight = 600;

struct Circle {
  float x, y;
  float radius;
  Color color;
};

int main() {
  // Initialization
  InitWindow(screenWidth, screenHeight, "Hello World");

  SetTargetFPS(60);

  srand(time(nullptr));

  vector<Circle> trail;

  Circle walker = {
      static_cast<float>(screenWidth / 2),
      static_cast<float>(screenHeight / 2),
      10,
      BLACK,
  };

  float timeElapsed = 0.0f;
  constexpr float circleSpawnInterval = 0.2f;
  constexpr float stepSize = 20.0f;

  while (!WindowShouldClose()) {
    // Update
    timeElapsed += GetFrameTime();

    if (timeElapsed >= circleSpawnInterval) {
      timeElapsed = 0.0f;

      trail.push_back(walker);

      switch (int direction = rand() % 4) {
      case 0:
        walker.y -= stepSize;
        break;
      case 1:
        walker.x += stepSize;
        break;
      case 2:
        walker.y += stepSize;
        break;
      case 3:
        walker.x -= stepSize;
        break;
      }

      walker.x = Clamp(walker.x, walker.radius, screenWidth - walker.radius);
      walker.y = Clamp(walker.y, walker.radius, screenHeight - walker.radius);
    }
    // Draw
    BeginDrawing();
    for (const Circle &circle : trail) {
      DrawCircle(circle.x, circle.y, circle.radius, circle.color);
    }
    DrawCircle(walker.x, walker.y, walker.radius, walker.color);
    ClearBackground(RAYWHITE);
    DrawText("Hello World!", 350, 300, 20, LIGHTGRAY);
    EndMode2D();

    DrawFPS(10, 10);
    EndDrawing();
  }
  // De-Initialization
  CloseWindow();
  return 0;
}
