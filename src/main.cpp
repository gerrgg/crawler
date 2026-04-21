#include "raylib.h"
#include "Game.h"
#include <cmath>

int main() {
  const int virtualWidth = 800;
  const int virtualHeight = 450;

  InitWindow(1280, 720, "Crawler");
  SetExitKey(KEY_NULL);
  SetTargetFPS(60);

  RenderTexture2D target = LoadRenderTexture(virtualWidth, virtualHeight);

  Game game(virtualWidth, virtualHeight);

  while (!WindowShouldClose()) {
    game.Update();

    float scale = fmin(
      (float)GetScreenWidth() / virtualWidth,
      (float)GetScreenHeight() / virtualHeight
    );

    float renderWidth = virtualWidth * scale;
    float renderHeight = virtualHeight * scale;

    float offsetX = (GetScreenWidth() - renderWidth) / 2.0f;
    float offsetY = (GetScreenHeight() - renderHeight) / 2.0f;

    BeginTextureMode(target);
      ClearBackground(RAYWHITE);
      game.Draw();
    EndTextureMode();

    BeginDrawing();
      ClearBackground(BLACK);

      DrawTexturePro(
        target.texture,
        (Rectangle){0, 0, (float)target.texture.width, (float)-target.texture.height},
        (Rectangle){offsetX, offsetY, renderWidth, renderHeight},
        (Vector2){0, 0},
        0.0f,
        WHITE
      );
    EndDrawing();
  }

  CloseWindow();
  return 0;
}