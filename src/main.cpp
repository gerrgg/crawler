#include "raylib.h"
#include "Game.h"
#include <cmath>

/**
 * Virtual Resolution Setup
 * 
 * Game logic and UI pretends the screen is always 800x450
 * by drawing the game onto an offsceen texture and scaling based on window size
 * 
 * TL;DR - Makes the game look the same on all screens.
 */
int main() {
  const int virtualWidth = 800;
  const int virtualHeight = 450;

  InitWindow(1280, 720, "Crawler");
  SetExitKey(KEY_NULL);
  SetTargetFPS(60);
  SetWindowFocused();

  // offscreen
  RenderTexture2D target = LoadRenderTexture(virtualWidth, virtualHeight);

  // init game
  Game game(virtualWidth, virtualHeight);

  // user pressed x or selected exit in the menu
  while (!WindowShouldClose() && !game.ShouldQuit()) {
    game.Update();

    // calculate scale, preserve aspect ratio
    float scale = fmin(
      (float)GetScreenWidth() / virtualWidth,
      (float)GetScreenHeight() / virtualHeight
    );

    // final display size
    float renderWidth = virtualWidth * scale;
    float renderHeight = virtualHeight * scale;

    // center
    float offsetX = (GetScreenWidth() - renderWidth) / 2.0f;
    float offsetY = (GetScreenHeight() - renderHeight) / 2.0f;

    // draw into hidden texture
    BeginTextureMode(target);
      ClearBackground(RAYWHITE);
      game.Draw();
    EndTextureMode();

    // draw the real screen
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