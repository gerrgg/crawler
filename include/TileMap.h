#ifndef TILEMAP_H
#define TILEMAP_H

#include "raylib.h"
#include <array>

class TileMap {
public:
  static constexpr int tileSize = 32;
  static constexpr int mapWidth = 16 * 10;
  static constexpr int mapHeight = 12;

  using Map = std::array<std::array<int, mapWidth>, mapHeight>;

  enum TileType {
    TILE_FLOOR_DIRT          = 16,
    TILE_FLOOR_DIRT_2        = 17,
    TILE_WALL_TOP_LEFT       = 0,
    TILE_WALL_TOP            = 44,
    TILE_WALL_TOP_RIGHT      = 4,
    TILE_WALL_LEFT           = 14,
    TILE_WALL_RIGHT          = 18,
    TILE_WALL_BOTTOM_LEFT    = 42,
    TILE_WALL_BOTTOM         = 43,
    TILE_WALL                = 44,
    TILE_WALL_BOTTOM_RIGHT   = 46,
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

  TileMap();

  void Load();
  
  void Draw() const;
  void DrawDebug() const;

  bool IsTilePassable(int tile) const;
  bool IsWorldPositionPassable(Vector2 worldPos) const;
  bool IsTileCoordinateInBounds(int x, int y) const;

  const Map& GetMap() const;
  Vector2 GetTileCenter(int x, int y) const;
  
  int WorldToTileX(float worldX) const;
  int WorldToTileY(float worldY) const;
  int GetTileAt(int x, int y) const;
  int GetTileSize() const;

  int GetDefaultTile(int x, int y) const;

  bool TryGetPassableTileCenter(Vector2 worldPos, Vector2& outCenter) const;
  
  bool HasNearbyDecoration(int tileX, int tileY, int radius) const;
  int GetRandomDecorTile() const;

  void GenerateGround();

  void GenerateDecor(int offset = 1, int radius = 1);

private:
  Texture2D tileset;

  static constexpr int TILE_EMPTY = -1;

  Map groundMap{};
  Map decorMap{};

  void LoadDefaultMap();
  void DrawLayer(const Map& layer) const;
};

#endif