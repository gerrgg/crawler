#include "Game.h"
#include <algorithm>

Game::Game(int virtualWidth, int virtualHeight)
  : screenWidth(virtualWidth),
    screenHeight(virtualHeight),
    currentState(GameState::PauseMenu),
    logoAlpha(0.0f),
    logoTimer(0.0f),
    pauseSelection(0),
    player(virtualWidth / 2.0f, virtualHeight / 2.0f) {
  logo = LoadTexture("assets/logo.png");
  title = LoadTexture("assets/title_screen.png");
  shouldQuit = false;

  camera.target = player.GetPosition();
  camera.offset = {(float)screenWidth / 2.0f, (float)screenHeight / 2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  tileset = LoadTexture("assets/8_cave.png");
  
}

bool Game::ShouldQuit() const {
  return shouldQuit;
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

Vector2 Game::GetVirtualMouseWorld() const {
  Vector2 mouse = GetVirtualMouse();
  return GetScreenToWorld2D(mouse, camera);
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

  Rectangle playButton = {screenWidth / 2.0f - 100.0f, 260.0f, 200.0f, 50.0f};
  MakeButton("PLAY", playButton, false);

  Rectangle exitButton = {screenWidth / 2.0f - 100.0f, 320.0f, 200.0f, 50.0f};
  MakeButton("EXIT", exitButton, false);
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

  Rectangle exitButton = {screenWidth / 2.0f - 100.0f, 320.0f, 200.0f, 50.0f};

  Vector2 mouse = GetVirtualMouse();

  if (CheckCollisionPointRec(mouse, playButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    ResetGame();
    currentState = GameState::Playing;
  } else if( CheckCollisionPointRec(mouse, exitButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) ){
    shouldQuit = true;
  }
}

// UpdateTitle and DrawTitle are pretty long, so I moved the button drawing code to a separate function
bool Game::MakeButton(const std::string& text, Rectangle rect, bool selected) {
  Vector2 mouse = GetVirtualMouse();
  bool hovered = CheckCollisionPointRec(mouse, rect);
  bool clicked = hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

  Color fillColor = hovered ? Fade(BLACK, 0.82f) : Fade(BLACK, 0.65f);
  Color borderColor = hovered ? YELLOW : (selected ? YELLOW : GRAY);
  Color textColor = hovered ? YELLOW : (selected ? YELLOW : RAYWHITE);

  DrawRectangleRec(rect, fillColor);
  DrawRectangleLinesEx(rect, 2.0f, borderColor);

  int fontSize = 28;
  int textWidth = MeasureText(text.c_str(), fontSize);

  float textX = rect.x + (rect.width - textWidth) / 2.0f;
  float textY = rect.y + (rect.height - fontSize) / 2.0f;

  DrawText(text.c_str(), (int)textX, (int)textY, fontSize, textColor);

  return clicked;
}

void Game::UpdatePlaying() {
  if (IsKeyPressed(KEY_ESCAPE)) {
    pauseSelection = 0;
    currentState = GameState::PauseMenu;
    return;
  }

  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    player.SetTarget(GetVirtualMouseWorld());
  }

  player.Update();

  Vector2 playerPos = player.GetPosition();
  float dt = GetFrameTime();
  float followSpeed = 5.0f;

  camera.target.x += (playerPos.x - camera.target.x) * followSpeed * dt;
  camera.target.y += (playerPos.y - camera.target.y) * followSpeed * dt;
}

void Game::DrawTileMap() {
  int tilesPerRow = tileset.width / tileSize;

  for (int y = 0; y < mapHeight; y++) {
    for (int x = 0; x < mapWidth; x++) {
      int tileIndex = tileMap[y][x];

      Rectangle source = {
        (float)((tileIndex % tilesPerRow) * tileSize),
        (float)((tileIndex / tilesPerRow) * tileSize),
        (float)tileSize,
        (float)tileSize
      };

      Rectangle dest = {
        (float)(x * tileSize),
        (float)(y * tileSize),
        (float)tileSize,
        (float)tileSize
      };

      DrawTexturePro(
        tileset,
        source,
        dest,
        {0.0f, 0.0f},
        0.0f,
        WHITE
      );
    }
  }
}

void Game::DrawPlaying() {
  ClearBackground(BLACK);

  BeginMode2D(camera);

    DrawTileMap();

    DrawCircle(0, 0, 10, RED);
    DrawLine(-40, 0, 40, 0, RED);
    DrawLine(0, -40, 0, 40, RED);

    player.Draw();

  EndMode2D();

}

void Game::UpdatePauseMenu() {
  Rectangle resumeButton = {screenWidth / 2.0f - 100.0f, 190.0f, 200.0f, 50.0f};
  Rectangle titleButton = {screenWidth / 2.0f - 100.0f, 250.0f, 200.0f, 50.0f};
  Rectangle exitButton = {screenWidth / 2.0f - 100.0f, 310.0f, 200.0f, 50.0f};

  Vector2 mouse = GetVirtualMouse();

  bool resumeHovered = CheckCollisionPointRec(mouse, resumeButton);
  bool titleHovered = CheckCollisionPointRec(mouse, titleButton);
  bool exitHovered = CheckCollisionPointRec(mouse, exitButton);

  if (resumeHovered) pauseSelection = 0;
  if (titleHovered) pauseSelection = 1;
  if (exitHovered) pauseSelection = 2;

  if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
    pauseSelection--;
  }

  if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
    pauseSelection++;
  }

  if (pauseSelection < 0) pauseSelection = 2;
  if (pauseSelection > 2) pauseSelection = 0;

  bool confirm =
    IsKeyPressed(KEY_ENTER) ||
    IsKeyPressed(KEY_SPACE) ||
    IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

  if (confirm) {
    if (pauseSelection == 0) {
      currentState = GameState::Playing;
    } else if (pauseSelection == 1) {
      currentState = GameState::Title;
    } else if (pauseSelection == 2) {
      shouldQuit = true;
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

Rectangle Game::MakeCenteredButtonRect(float y, float width, float height) {
  return Rectangle{
    (screenWidth - width) / 2.0f,
    y,
    width,
    height
  };
}

void Game::DrawPauseMenu() {
  DrawPlaying();

  DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.35f));

  Rectangle panel = {
    100.0f, // x
    70.0f, // y
    600.0f, // w
    320.0f // h
  };

  DrawRectangleRec(panel, Fade(BLACK, 0.7f));
  DrawRectangleLinesEx(panel, 2.0f, GRAY);

  DrawCenteredTextInRect("Paused", panel, panel.y + 25, 40, RAYWHITE);

  float buttonWidth = 300.0f;
  float buttonHeight = 60.0f;
  float buttonX = panel.x + (panel.width - buttonWidth) / 2.0f;

  Rectangle resumeButton = {buttonX, panel.y + 90.0f, buttonWidth, buttonHeight};
  Rectangle titleButton = {buttonX, panel.y + 160.0f, buttonWidth, buttonHeight};
  Rectangle exitButton = {buttonX, panel.y + 230.0f, buttonWidth, buttonHeight};

  MakeButton("Resume", resumeButton, pauseSelection == 0);
  MakeButton("Return to Title", titleButton, pauseSelection == 1);
  MakeButton("Save and Exit", exitButton, pauseSelection == 2);
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