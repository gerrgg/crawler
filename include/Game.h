#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "Player.h"
#include <string>

enum class GameState {
  Logo,
  Title,
  Playing,
  PauseMenu
};

class Game {
public:
  Game(int virtualWidth, int virtualHeight);

  void Update();
  void Draw();

  bool shouldQuit;
  bool ShouldQuit() const;

private:
  int screenWidth;
  int screenHeight;

  GameState currentState;

  Texture2D logo;
  Texture2D title;

  Player player;
  Camera2D camera;

  float logoAlpha;
  float logoTimer;
  
  int pauseSelection;
  
  Vector2 GetVirtualMouseWorld() const;
  Vector2 GetVirtualMouse() const;

  bool MakeButton(const std::string& text, Rectangle rect, bool selected);
  Rectangle MakeCenteredButtonRect(float y, float width, float height);

  void UpdateLogo();
  void UpdateTitle();
  void UpdatePlaying();
  void UpdatePauseMenu();

  void DrawLogo();
  void DrawTitle();
  void DrawPlaying();
  void DrawPauseMenu();

  void ResetGame();
};

#endif