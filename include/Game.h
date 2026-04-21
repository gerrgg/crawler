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

  enum TileType {
    TILE_VOID                = 6,
    TILE_FLOOR_DIRT          = 16,
    TILE_FLOOR_DIRT_2        = 17,
    TILE_WALL_TOP_LEFT       = 0,
    TILE_WALL_TOP            = 4,
    TILE_WALL_TOP_RIGHT      = 7,
    TILE_WALL_LEFT           = 14,
    TILE_WALL_RIGHT          = 21,
    TILE_WALL_BOTTOM_LEFT    = 42,
    TILE_WALL_BOTTOM         = 43,
    TILE_WALL_BOTTOM_RIGHT   = 46,
    TILE_EDGE_LEFT           = 56,
    TILE_EDGE_RIGHT          = 60,
    TILE_EDGE_BOTTOM_LEFT    = 70,
    TILE_EDGE_BOTTOM         = 71,
    TILE_EDGE_BOTTOM_RIGHT   = 74,
    TILE_SLOPE_LEFT          = 78,
    TILE_SLOPE_MID           = 79,
    TILE_SLOPE_RIGHT         = 83,

    TILE_ROCK                = 84,
    TILE_ROCK_2              = 85,
    TILE_ROCK_3              = 86,
    TILE_PLANT               = 87,
    TILE_PLANT_2             = 88,
    TILE_MUSHROOM_RED        = 89,
    TILE_MUSHROOM_PURPLE     = 90,
    TILE_CRYSTAL_PINK        = 100,
    TILE_CRYSTAL_PURPLE      = 101,
    TILE_CRYSTAL_BLUE        = 102,
    TILE_CRYSTAL_BLUE_2      = 103
  };

  bool IsTilePassable(int tile) const;
  bool IsWorldPositionPassable(Vector2 worldPos) const;

  static constexpr int tileSize = 32;
  static constexpr int mapWidth = 32;
  static constexpr int mapHeight = 16;

int tileMap[mapHeight][mapWidth] = {
  { 0,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  7},
  {14, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 21},
  {14, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 21},
  {14, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 21},
  {14, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 21},
  {14, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 21},
  {14, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 21},
  {14, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 21},
  {14, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 21},
  {14, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 21},
  {14, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 21},
  {14, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 21},
  {42, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 46},
  {56, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 60},
  {70, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 74},
  {84, 85, 86, 87, 88, 89, 90,100,101,102,103, 84, 85, 86, 87, 88, 89, 90,100,101,102,103, 84, 85, 86, 87, 88, 89, 90,100,101,102}
};

int hole[5][5] = {
  {7,8,9,10,11},
  {21,22,23,24,25},
  {35,36,37,38,39},
  {49,50,51,52,53},
};

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