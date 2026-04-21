#ifndef GAME_H
#define GAME_H

#include "raylib.h"

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

private:
  int screenWidth;
  int screenHeight;

  GameState currentState;

  Texture2D logo;
  Texture2D title;

  float logoAlpha;
  float logoTimer;

  int pauseSelection;

  Vector2 GetVirtualMouse() const;

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