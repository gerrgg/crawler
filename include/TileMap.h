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

  /**
  * Loads .png texture file
  * @see assets/8_cave.png
  */
  void Load();
  
  /**
  * Draws the ground and decoration maps
  */
  void Draw() const;

  /**
  * Useful for visual representation of tile grid
  * @see assets/8_cave_debug.png
  */
  void DrawDebug() const;

  /**
  * Visual representation of where which tile the mouse is on
  * @param worldMouse Mouse position converted into world/map coordinates
  */
  void DrawHoveredTile(Vector2 worldMouse) const;

  /**
  * Checks whether a tile can be walked on
  * @param tile The tile ID to check
  * @return true if tile is passible, false otherwise
  */
  bool IsTilePassable(int tile) const;

  /**
  * Checks whether a world position is on a passible tile
  * 
  * @param worldPos The world/map position to check
  * @return true is position is within bounds and on a passible tile
  */
  bool IsWorldPositionPassable(Vector2 worldPos) const;
  
  
  /**
  * Checks whether the tile is within bounds of the map
  * @param x the tile x coordinate
  * @param y the tile y coordianate
  */
  bool IsTileCoordinateInBounds(int x, int y) const;

  /**
  * Returns the ground map
  */
  const Map& GetMap() const;

  /**
   * Returns the world position of the center of a tile, used for centering characters on a tile

   * @param x The tile x coordinate
   * @param y the tile y coordinate
   * @return A Vector2 representing the center position of the tile
   */
  Vector2 GetTileCenter(int x, int y) const;
  
  /**
  * Converts a world X position to a tile X coordinate.
  *
  * @param worldX The X position in world space.
  * @return The tile X coordinate.
  */
  int WorldToTileX(float worldX) const;

  /**
  * Converts a world Y position to a tile Y coordinate.
  *
  * @param worldY The Y position in world space.
  * @return The tile Y coordinate.
  */
  int WorldToTileY(float worldY) const;

  /**
  * Gets the ground tile at a tile coordinate.
  *
  * @param x The tile X coordinate.
  * @param y The tile Y coordinate.
  * @return The tile ID, or -1 if out of bounds.
  */
  int GetTileAt(int x, int y) const;

  /**
  * Gets the tile size in pixels.
  *
  * @return The width/height of one tile.
  */
  int GetTileSize() const;

  /**
  * Gets the default tile ID for a position in the map grid.
  * 
  * @param x The tile X coordinate.
  * @param y The tile Y coordinate.
  * @return The wall tile ID for map edges/corners or floor
  */
  int GetDefaultTile(int x, int y) const;

  /**
  * Gets the center position of a passable tile at a world position.
  * 
  * @param worldPos the world/map position to check
  * @param outCenter updated with the tile center if passible
  * @return true if the position is in bounds and passible
  */
  bool TryGetPassableTileCenter(Vector2 worldPos, Vector2& outCenter) const;
  
  /**
  * Checks hwther any decoration exists within a square radius of a tile
  * 
  * @param tileX The center tile X coordinate
  * @param tileY The center tile Y coordinate
  * @param The number of tiles to check outward from the center tile coordinates
  * @return true if a nearby decoration exists
  */
  bool HasNearbyDecoration(int tileX, int tileY, int radius) const;
  
  /**
  * Gets a random docoration tile ID
  *
  * @return A randomy selected tile ID
  */
  int GetRandomDecorTile() const;

  /**
  * Randomly generates decoration tiles on passable ground.
  *
  * @param offset Number of edge tiles to avoid when placing decorations.
  * @param radius Minimum spacing around existing decorations.
  */
  void GenerateDecor(int offset = 1, int radius = 1);

private:
  Texture2D tileset;

  static constexpr int TILE_EMPTY = -1;

  Map groundMap{};
  Map decorMap{};

  void LoadDefaultMap();

  /**
  * Draw a single tile layer using the assigned texture
  *
  * @param layer The tilemap layer to draw.
  */
  void DrawLayer(const Map& layer) const;
};

#endif