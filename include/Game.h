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
  TileMap tileMap;

  int screenWidth;
  int screenHeight;

  bool shouldQuit;

  GameState currentState;

  Texture2D logo;
  Texture2D title;

  Player player;
  Camera2D camera;

  float logoAlpha;
  float logoTimer;
  
  int pauseSelection;

  Texture2D tileset;


  void DrawTileMap();
  void DrawTilesetDebug();
  
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