#include "Game.h"
#include <iostream>
#include <algorithm>

Game::Game(int virtualWidth, int virtualHeight)
  : screenWidth(virtualWidth),
    screenHeight(virtualHeight),
    currentState(GameState::Playing),
    logoAlpha(0.0f),
    logoTimer(0.0f),
    pauseSelection(0),
    enemy(virtualWidth / 2.0f + 64.0f, virtualHeight / 2.0f),
    player(virtualWidth / 2.0f, virtualHeight / 2.0f) {
  logo = LoadTexture("assets/logo.png");
  title = LoadTexture("assets/title_screen.png");
  shouldQuit = false;

  camera.target = player.GetPosition();
  camera.offset = {(float)screenWidth / 2.0f, (float)screenHeight / 2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;
 
}

/*==================================
    Menu Helpers (should seperate)
===================================*/

// center text within rectangle
void DrawCenteredTextInRect(const char* text, Rectangle rect, int y, int fontSize, Color color) {
  int textWidth = MeasureText(text, fontSize);
  int x = rect.x + (rect.width - textWidth) / 2;
  DrawText(text, x, y, fontSize, color);
}

// menu helper
Rectangle Game::MakeCenteredButtonRect(float y, float width, float height) {
  return Rectangle{
    (screenWidth - width) / 2.0f,
    y,
    width,
    height
  };
}

// should we break out of loop and quit?
bool Game::ShouldQuit() const {
  return shouldQuit;
}

// update based on gamestate
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

// Draw based on gamestate
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

// Get the world space position for a 2d camera screen space position
// Determine where we clicked on the world
Vector2 Game::GetVirtualMouseWorld() const {
  Vector2 mouse = GetVirtualMouse();
  return GetScreenToWorld2D(mouse, camera);
}

// animate the logo fade in by incrementing alpha until full
void Game::UpdateLogo() {
  float dt = GetFrameTime();

  // controls how long the logo stays up
  logoTimer += dt;

  // keep fading in
  if (logoAlpha < 1.0f) {

    // controls speed of fade in
    logoAlpha += dt;

    // stop once full
    if (logoAlpha > 1.0f) logoAlpha = 1.0f;
  }

  // move to title after 2.0f
  if (logoTimer >= 2.0f) {
    currentState = GameState::Title;
  }
}

// draw the logo screen
void Game::DrawLogo() {
  //clear
  ClearBackground(RAYWHITE);

  // scale logo to 50% and center it on the screen
  float scale = 0.5f;
  float logoWidth = logo.width * scale;
  float logoHeight = logo.height * scale;

  // calculate position to center the logo
  float x = (screenWidth - logoWidth) / 2.0f;
  float y = (screenHeight - logoHeight) / 2.0f;

  // draw the logo asset and fade in
  DrawTextureEx(logo, {x, y}, 0.0f, scale, Fade(WHITE, logoAlpha));
}

// Draw title screen
void Game::DrawTitle() {
  //clear
  ClearBackground(BLACK);

  // draw asset as background, fill screen
  DrawTexturePro(
    title,
    (Rectangle){0, 0, (float)title.width, (float)title.height},
    (Rectangle){0, 0, (float)screenWidth, (float)screenHeight},
    (Vector2){0, 0},
    0.0f,
    WHITE
  );

  // draw play button
  Rectangle playButton = {screenWidth / 2.0f - 100.0f, 260.0f, 200.0f, 50.0f};
  MakeButton("PLAY", playButton, false);

  // draw exit button
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

// button helper
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

// running game
void Game::UpdatePlaying() {
  // open pause
  if (IsKeyPressed(KEY_ESCAPE)) {
    pauseSelection = 0;
    currentState = GameState::PauseMenu;
    return;
  }

  HandlePlayerInput();
  player.Update();

  Vector2 playerPos = player.GetPosition();
  enemy.UpdateToward(playerPos, tileMap);

  float dt = GetFrameTime();
  float followSpeed = 5.0f;

  camera.target.x += (playerPos.x - camera.target.x) * followSpeed * dt;
  camera.target.y += (playerPos.y - camera.target.y) * followSpeed * dt;
}

// init Game::Playing
void Game::DrawPlaying() {
  // clear
  ClearBackground(BLACK);

  // set camera (things between begin and end are affected by the camera)
  BeginMode2D(camera);
  // draw map
  tileMap.Draw();
  // draw player init position
  enemy.Draw();
  player.Draw();
    // restore normal screen
  EndMode2D();

  }

// Handle pause menu hover/actions
void Game::UpdatePauseMenu() {
  Rectangle resumeButton = {screenWidth / 2.0f - 100.0f, 190.0f, 200.0f, 50.0f};
  Rectangle titleButton = {screenWidth / 2.0f - 100.0f, 250.0f, 200.0f, 50.0f};
  Rectangle exitButton = {screenWidth / 2.0f - 100.0f, 310.0f, 200.0f, 50.0f};

  // get mouse position
  Vector2 mouse = GetVirtualMouse();

  // track hovers
  bool resumeHovered = CheckCollisionPointRec(mouse, resumeButton);
  bool titleHovered = CheckCollisionPointRec(mouse, titleButton);
  bool exitHovered = CheckCollisionPointRec(mouse, exitButton);

  // track which button is being hovered
  if (resumeHovered) pauseSelection = 0;
  if (titleHovered) pauseSelection = 1;
  if (exitHovered) pauseSelection = 2;

  // track what was clicked
  bool confirm =
    IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

  // take action based on what was clicked
  if (confirm) {
    if (pauseSelection == 0) {
      currentState = GameState::Playing;
    } else if (pauseSelection == 1) {
      currentState = GameState::Title;
    } else if (pauseSelection == 2) {
      shouldQuit = true;
    }
  }

  // resume game
  if (IsKeyPressed(KEY_ESCAPE)) {
    currentState = GameState::Playing;
  }
}



// Show Pause Menu
// https://www.raylib.com/cheatsheet/cheatsheet.html
void Game::DrawPauseMenu() {
  DrawPlaying();

  // overlay over game
  DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.35f));

  // panel
  Rectangle panel = {
    100.0f, // x
    70.0f, // y
    600.0f, // w
    320.0f // h
  };

  // Create pause menu box
  DrawRectangleRec(panel, Fade(BLACK, 0.7f));
  DrawRectangleLinesEx(panel, 2.0f, GRAY);

  // add text
  DrawCenteredTextInRect("Paused", panel, panel.y + 25, 40, RAYWHITE);

  // button defaults
  float buttonWidth = 300.0f;
  float buttonHeight = 60.0f;
  float buttonX = panel.x + (panel.width - buttonWidth) / 2.0f;

  // space out buttons
  Rectangle resumeButton = {buttonX, panel.y + 90.0f, buttonWidth, buttonHeight};
  Rectangle titleButton = {buttonX, panel.y + 160.0f, buttonWidth, buttonHeight};
  Rectangle exitButton = {buttonX, panel.y + 230.0f, buttonWidth, buttonHeight};

  // MakeButton(text, dims, callback)
  MakeButton("Resume", resumeButton, pauseSelection == 0);
  MakeButton("Return to Title", titleButton, pauseSelection == 1);
  MakeButton("Save and Exit", exitButton, pauseSelection == 2);
}

// Tracks mouse position on virtual texture and scales up to match window size
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

void Game::HandlePlayerInput() {
  if (!IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    return;
  }

  Vector2 clickWorld = GetVirtualMouseWorld();

  Enemy* clickedEnemy = GetEnemyAtWorldPosition(clickWorld);

  if (clickedEnemy) {
    player.Attack(*clickedEnemy);
    return;
  }

  Vector2 tileCenter;

  if (!tileMap.TryGetPassableTileCenter(clickWorld, tileCenter)) {
    return;
  }

  if (IsEnemyAtTile(tileCenter)) {
    return;
  }

  player.MoveTo(tileCenter);
}

Enemy* Game::GetEnemyAtWorldPosition(Vector2 worldPos) {
  int clickedTileX = tileMap.WorldToTileX(worldPos.x);
  int clickedTileY = tileMap.WorldToTileY(worldPos.y);

  int enemyTileX = enemy.GetTileX(tileMap);
  int enemyTileY = enemy.GetTileY(tileMap);

  if (clickedTileX == enemyTileX && clickedTileY == enemyTileY) {
    return &enemy;
  }

  return nullptr;
}

bool Game::IsEnemyAtTile(Vector2 tileCenter) {
  int tileX = tileMap.WorldToTileX(tileCenter.x);
  int tileY = tileMap.WorldToTileY(tileCenter.y);

  return tileX == enemy.GetTileX(tileMap)
    && tileY == enemy.GetTileY(tileMap);
}

// TODO
void Game::ResetGame() {
  // reset player position
  // reset score
  // clear enemies
  // reset timers
}

