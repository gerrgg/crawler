#include "raylib.h"
#include "Game.h"

int main() {
  InitWindow(800, 450, "Crawler");
  SetExitKey(KEY_NULL);
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