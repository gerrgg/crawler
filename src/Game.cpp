#include "Game.h"
#include <algorithm>

Game::Game(int virtualWidth, int virtualHeight)
  : screenWidth(virtualWidth),
    screenHeight(virtualHeight),
    currentState(GameState::Logo),
    logoAlpha(0.0f),
    logoTimer(0.0f),
    pauseSelection(0) {
  logo = LoadTexture("assets/logo_2.png");
  title = LoadTexture("assets/title_screen_2.png");
}

void Game::Update() {
  switch (currentState) {
    case GameState::Logo:
      UpdateLogo();
      break;

    case GameState::Title:
      UpdateTitle();
      break;

    case GameState::Playing:
      UpdatePlaying();
      break;

    case GameState::PauseMenu:
      UpdatePauseMenu();
      break;
  }
}

void Game::Draw() {
  switch (currentState) {
    case GameState::Logo:
      DrawLogo();
      break;

    case GameState::Title:
      DrawTitle();
      break;

    case GameState::Playing:
      DrawPlaying();
      break;

    case GameState::PauseMenu:
      DrawPauseMenu();
      break;
  }
}

void Game::UpdateLogo() {
  float dt = GetFrameTime();

  logoTimer += dt * 0.5f;

  if (logoAlpha < 1.0f) {
    logoAlpha += dt;
    if (logoAlpha > 1.0f) logoAlpha = 1.0f;
  }

  if (logoTimer >= 2.0f) {
    currentState = GameState::Title;
  }
}

void Game::DrawLogo() {
  ClearBackground(RAYWHITE);

  // scale logo to 50% and center it on the screen
  float scale = 0.5f;
  float logoWidth = logo.width * scale;
  float logoHeight = logo.height * scale;

  // calculate position to center the logo
  float x = (screenWidth - logoWidth) / 2.0f;
  float y = (screenHeight - logoHeight) / 2.0f;

  // draw the logo with fade effect
  DrawTextureEx(logo, {x, y}, 0.0f, scale, Fade(WHITE, logoAlpha));
}

void Game::UpdateTitle() {
  if (IsKeyPressed(KEY_ENTER)) {
    ResetGame();
    currentState = GameState::Playing;
  }

  Rectangle playButton = {
    screenWidth / 2.0f - 100.0f,
    260.0f,
    200.0f,
    50.0f
  };

  Vector2 mouse = GetVirtualMouse();

  if (CheckCollisionPointRec(mouse, playButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    ResetGame();
    currentState = GameState::Playing;
  }
}

void Game::DrawTitle() {
  ClearBackground(BLACK);

  DrawTexturePro(
    title,
    (Rectangle){0, 0, (float)title.width, (float)title.height},
    (Rectangle){0, 0, (float)screenWidth, (float)screenHeight},
    (Vector2){0, 0},
    0.0f,
    WHITE
  );

  Rectangle playButton = {
    screenWidth / 2.0f - 100.0f,
    260.0f,
    200.0f,
    50.0f
  };

  DrawRectangleRec(playButton, Fade(BLACK, 0.65f));
  DrawRectangleLinesEx(playButton, 2.0f, GRAY);
  DrawText("PLAY", playButton.x + 60, playButton.y + 12, 28, RAYWHITE);
}

void Game::UpdatePlaying() {
  if (IsKeyPressed(KEY_ESCAPE)) {
    pauseSelection = 0;
    currentState = GameState::PauseMenu;
    return;
  }

  // actual gameplay update here
}

void Game::DrawPlaying() {
  ClearBackground(DARKGREEN);

  DrawText("Gameplay running...", 20, 20, 30, WHITE);
  DrawText("Press ESC for menu", 20, 60, 20, WHITE);

  // actual gameplay draw here
}

void Game::UpdatePauseMenu() {
  if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
    pauseSelection--;
  }

  if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
    pauseSelection++;
  }

  if (pauseSelection < 0) pauseSelection = 1;
  if (pauseSelection > 1) pauseSelection = 0;

  if (IsKeyPressed(KEY_ENTER)) {
    if (pauseSelection == 0) {
      currentState = GameState::Playing;
    } else if (pauseSelection == 1) {
      currentState = GameState::Title;
    }
  }

  if (IsKeyPressed(KEY_ESCAPE)) {
    currentState = GameState::Playing;
  }
}

void DrawCenteredTextInRect(const char* text, Rectangle rect, int y, int fontSize, Color color) {
  int textWidth = MeasureText(text, fontSize);
  int x = rect.x + (rect.width - textWidth) / 2;
  DrawText(text, x, y, fontSize, color);
}

void Game::DrawPauseMenu() {
  DrawPlaying();

  Rectangle panel = {150, 100, 500, 250};
  DrawRectangleRec(panel, Fade(BLACK, 0.85f));

  Color resumeColor = (pauseSelection == 0) ? YELLOW : RAYWHITE;
  Color titleColor = (pauseSelection == 1) ? YELLOW : RAYWHITE;

  DrawCenteredTextInRect("Paused", panel, panel.y + 30, 40, RAYWHITE);
  DrawCenteredTextInRect("Resume", panel, panel.y + 110, 30, resumeColor);
  DrawCenteredTextInRect("Return to Title", panel, panel.y + 160, 30, titleColor);
}

Vector2 Game::GetVirtualMouse() const {
  float scale = std::min(
    (float)GetScreenWidth() / screenWidth,
    (float)GetScreenHeight() / screenHeight
  );

  float renderWidth = screenWidth * scale;
  float renderHeight = screenHeight * scale;

  float offsetX = (GetScreenWidth() - renderWidth) / 2.0f;
  float offsetY = (GetScreenHeight() - renderHeight) / 2.0f;

  Vector2 mouse = GetMousePosition();

  mouse.x = (mouse.x - offsetX) / scale;
  mouse.y = (mouse.y - offsetY) / scale;

  return mouse;
}

void Game::ResetGame() {
  // reset player position
  // reset score
  // clear enemies
  // reset timers
}