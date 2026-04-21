#include "Game.h"

Game::Game()
  : currentState(GameState::Logo),
    logoAlpha(0.0f),
    logoTimer(0.0f),
    pauseSelection(0) {
  logo = LoadTexture("assets/logo.png");
  title = LoadTexture("assets/title_screen.png");
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

  logoTimer += dt;

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

  float scale = 0.75f;
  float logoWidth = logo.width * scale;
  float logoHeight = logo.height * scale;

  float x = (GetScreenWidth() - logoWidth) / 2.0f;
  float y = (GetScreenHeight() - logoHeight) / 2.0f;

  DrawTextureEx(logo, {x, y}, 0.0f, scale, Fade(WHITE, logoAlpha));
}

void Game::UpdateTitle() {
  if (IsKeyPressed(KEY_ENTER)) {
    ResetGame();
    currentState = GameState::Playing;
  }

  Rectangle playButton = {
    GetScreenWidth() / 2.0f - 100.0f,
    260.0f,
    200.0f,
    50.0f
  };

  Vector2 mouse = GetMousePosition();

  if (CheckCollisionPointRec(mouse, playButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    ResetGame();
    currentState = GameState::Playing;
  }
}

void Game::DrawTitle() {
  ClearBackground(BLACK);

  float scale = 0.75f;
  float titleWidth = title.width * scale;
  float titleHeight = title.height * scale;

  float x = (GetScreenWidth() - titleWidth) / 2.0f;
  float y = 100.0f;

  DrawTextureEx(title, {x, y}, 0.0f, scale, RAYWHITE);

  const char* titleText = "CRAWLER";
  int fontSize = 64;
  int textWidth = MeasureText(titleText, fontSize);

  DrawText(titleText, (GetScreenWidth() - textWidth) / 2, 100, fontSize, RAYWHITE);

  Rectangle playButton = {
    GetScreenWidth() / 2.0f - 100.0f,
    260.0f,
    200.0f,
    50.0f
  };

  DrawRectangleRec(playButton, DARKGRAY);
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

void Game::DrawPauseMenu() {
  DrawPlaying();

  DrawRectangle(150, 100, 500, 250, Fade(BLACK, 0.85f));
  DrawText("Paused", 320, 130, 40, RAYWHITE);

  Color resumeColor = (pauseSelection == 0) ? YELLOW : RAYWHITE;
  Color titleColor = (pauseSelection == 1) ? YELLOW : RAYWHITE;

  DrawText("Resume", 320, 210, 30, resumeColor);
  DrawText("Return to Title", 250, 260, 30, titleColor);
}

void Game::ResetGame() {
  // reset player position
  // reset score
  // clear enemies
  // reset timers
}