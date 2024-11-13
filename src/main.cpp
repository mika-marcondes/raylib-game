#include "raylib.h"

#include <random>

static constexpr int screenWidth = 800;
static constexpr int screenHeight = 600;

class Walker {
public:
  int x;
  int y;

  void Setup() {
    this->x = screenWidth / 2;
    this->y = screenHeight / 2;
  }

  void Step() {
    int min = 0;
    int max = 3;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution distrib(min, max);

    int choice = distrib(gen);

    if (choice == 0) {
      this->x++;
    } else if (choice == 1) {
      this->x--;
    } else if (choice == 2) {
      this->y++;
    } else {
      this->y--;
    }
  }

  void Draw() const { DrawCircle(this->x, this->y, 20, BLACK); }
};

int main() {
  // Initialization
  Walker walker;
  InitWindow(screenWidth, screenHeight, "Hello World");
  walker.Setup();
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    // Update
    walker.Step();
    // Draw
    BeginDrawing();
    ClearBackground(RAYWHITE);
    walker.Draw();
    DrawText("Hello World!", 350, 300, 20, LIGHTGRAY);
    EndMode2D();

    DrawFPS(10, 10);
    EndDrawing();
  }
  // De-Initialization
  CloseWindow();
  return 0;
}
