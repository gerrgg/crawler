/**
 * Name: Gregory Bastianelli
 * Project: Crawler
 * Usage: ./run.sh
 */

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

  // dimensions the game logic uses
  const int virtualWidth = 800;
  const int virtualHeight = 450;

  // build window
  InitWindow(1280, 720, "Crawler");

  // prevent close when pressing esc
  SetExitKey(KEY_NULL);

  // set frame cap
  SetTargetFPS(60);

  // creates a texture in memory only, we draw the game to this texture before scaling
  RenderTexture2D target = LoadRenderTexture(virtualWidth, virtualHeight);

  // create game object
  Game game(virtualWidth, virtualHeight);

  // user pressed x or selected exit in the menu
  while (!WindowShouldClose() && !game.ShouldQuit()) {
    // updates game to current frame
    game.Update();

    // calculate scale
    // divide real width by virtual width to get scale
    // 1280 / 800 = 1.6
    // 720 / 450 = 1.6
    // 1.6 is our scale
    // fmin - use smaller scale to preserve aspect ration
    float scale = fmin(
      (float)GetScreenWidth() / virtualWidth,
      (float)GetScreenHeight() / virtualHeight
    );

    // final display size
    float renderWidth = virtualWidth * scale;
    float renderHeight = virtualHeight * scale;

    // center the game on the real window
    float offsetX = (GetScreenWidth() - renderWidth) / 2.0f;
    float offsetY = (GetScreenHeight() - renderHeight) / 2.0f;

    // draw into hidden texture
    // each frame we clear and draw new frame
    BeginTextureMode(target);
      ClearBackground(RAYWHITE);
      game.Draw();
    EndTextureMode();

    /*
    * Draw to screen
    * Take the texture on the hidden canvas and scale it up before writing to real screen
    * Rectange (offsetX, offsetY, renderWidth, renderHeight)
    */

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

  // close
  CloseWindow();
  return 0;
}