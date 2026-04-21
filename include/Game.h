#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "Player.h"
#include <array>
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

  Texture2D tileset;

  static constexpr int tileSize = 32;
  static constexpr int mapWidth = 20;
  static constexpr int mapHeight = 15;

  int tileMap[mapHeight][mapWidth] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0},
    {0,1,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,1,0},
    {0,1,2,3,4,4,4,4,4,4,4,4,4,4,4,4,3,2,1,0},
    {0,1,2,3,4,5,5,5,5,5,5,5,5,5,5,4,3,2,1,0},
    {0,1,2,3,4,5,6,6,6,6,6,6,6,6,5,4,3,2,1,0},
    {0,1,2,3,4,5,6,7,7,7,7,7,7,6,5,4,3,2,1,0},
    {0,1,2,3,4,5,6,6,6,6,6,6,6,6,5,4,3,2,1,0},
    {0,1,2,3,4,5,5,5,5,5,5,5,5,5,5,4,3,2,1,0},
    {0,1,2,3,4,4,4,4,4,4,4,4,4,4,4,4,3,2,1,0},
    {0,1,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,1,0},
    {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
  };

  void DrawTileMap();
  
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