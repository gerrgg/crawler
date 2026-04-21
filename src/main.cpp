#include "raylib.h"
#include "Game.h"

int main() {
  InitWindow(800, 450, "Crawler");
  SetTargetFPS(60);

  Game game;

  while (!WindowShouldClose()) {
    game.Update();

    BeginDrawing();
      ClearBackground(RAYWHITE);
      game.Draw();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}