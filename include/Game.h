#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "Player.h"
#include "TileMap.h"
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

  void Update(); // update current game state
  void Draw(); // draw current game state

  bool ShouldQuit() const; // for when user wants to close

private:
  // map object
  TileMap tileMap;

  // window size
  int screenWidth;
  int screenHeight;

  // end game?
  bool shouldQuit;

  // logo fade in
  float logoAlpha;
  float logoTimer;
  
  // what did the user pick in the pause menu
  int pauseSelection;

  // controls which state to run
  GameState currentState;

  // textures for logo/title screens
  Texture2D logo;
  Texture2D title;

  // player and camera objects
  Player player;
  Camera2D camera;

  // tracking mouse in game (playing)
  Vector2 GetVirtualMouseWorld() const;

  // tracking mouse in UI (logo/title/pause)
  Vector2 GetVirtualMouse() const;

  // UI helpers
  bool MakeButton(const std::string& text, Rectangle rect, bool selected);
  Rectangle MakeCenteredButtonRect(float y, float width, float height);

  // logo
  void DrawLogo();
  void UpdateLogo();

  // title
  void DrawTitle();
  void UpdateTitle();

  // game
  void DrawPlaying();
  void UpdatePlaying();

  // pause
  void UpdatePauseMenu();
  void DrawPauseMenu();

  void ResetGame();
};

#endif