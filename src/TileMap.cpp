#include "TileMap.h"

// setup and draw
TileMap::TileMap() {
  Load();
  LoadDefaultMap();
}

// get the texture asset
void TileMap::Load() {
  tileset = LoadTexture("assets/8_cave.png");
}

// procedurally generate ground and decor map
void TileMap::LoadDefaultMap() {
  GenerateGround();
  GenerateDecor(2, 5);
}

// procedurally generate ground
void TileMap::GenerateGround() {
  for (int y = 0; y < mapHeight; y++) {
    for (int x = 0; x < mapWidth; x++) {
      groundMap[y][x] = GetDefaultTile(x, y);
    }
  }
}

// generate corners, walls and fill the rest with ground
int TileMap::GetDefaultTile(int x, int y) const {
  if (x == 0 && y == 0) return TILE_WALL_TOP_LEFT;
  if (x == mapWidth - 1 && y == 0) return TILE_WALL_TOP_RIGHT;
  if (x == 0 && y == mapHeight - 1) return TILE_WALL_BOTTOM_LEFT;
  if (x == mapWidth - 1 && y == mapHeight - 1) return TILE_WALL_BOTTOM_RIGHT;

  if (y == 0) return TILE_WALL_TOP;
  if (y == mapHeight - 1) return TILE_WALL_BOTTOM;
  if (x == 0) return TILE_WALL_LEFT;
  if (x == mapWidth - 1) return TILE_WALL_RIGHT;

  return TILE_FLOOR_DIRT;
}

// multiple maps allows us to place objects on the ground like rocks and mushrooms
void TileMap::Draw() const {
  DrawLayer(groundMap);
  DrawLayer(decorMap);
}

/*
* Procedurally generate decorations
* tileX, tileY keep decorations away from walls
* radius is how many spaces away a decoration should be from others
*/
bool TileMap::HasNearbyDecoration(int tileX, int tileY, int radius) const {
  for (int y = tileY - radius; y <= tileY + radius; y++) {
    for (int x = tileX - radius; x <= tileX + radius; x++) {
      if (x < 0 || x >= mapWidth || y < 0 || y >= mapHeight) {
        continue;
      }

      if (decorMap[y][x] != TILE_EMPTY) {
        return true;
      }
    }
  }

  return false;
}

// randomly pick a piece of decor
int TileMap::GetRandomDecorTile() const {
  int roll = GetRandomValue(0, 5);

  switch (roll) {
    case 0: return TILE_PLANT;
    case 1: return TILE_PLANT_2;
    case 2: return TILE_ROCK;
    case 3: return TILE_ROCK_2;
    case 4: return TILE_MUSHROOM_RED;
    case 5: return TILE_CRYSTAL_BLUE;
    default: return TILE_PLANT;
  }
}

// clears the decor map and places decor tiles where passable
void TileMap::GenerateDecor(int offset, int radius) {
  for (int y = 0; y < mapHeight; y++) {
    for (int x = 0; x < mapWidth; x++) {
      decorMap[y][x] = TILE_EMPTY;
    }
  }

  for (int y = offset; y < mapHeight - offset; y++) {
    for (int x = offset; x < mapWidth - offset; x++) {
      // only place decor on passable ground
      if (!IsTilePassable(groundMap[y][x])) {
        continue;
      }

      // random chance
      if (GetRandomValue(0, 100) > 12) {
        continue;
      }

      // avoid placing too close to another decoration
      if (HasNearbyDecoration(x, y, radius)) {
        continue;
      }

      decorMap[y][x] = GetRandomDecorTile();
    }
  }
}

// loops the length of the map and places tiles set in array
void TileMap::DrawLayer(const Map& layer) const {
  int tilesPerRow = tileset.width / tileSize;

  for (int y = 0; y < mapHeight; y++) {
    for (int x = 0; x < mapWidth; x++) {
      int tileIndex = layer[y][x];

      if (tileIndex == TILE_EMPTY) {
        continue;
      }

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

      DrawTexturePro(tileset, source, dest, {0.0f, 0.0f}, 0.0f, WHITE);
    }
  }
}

// for gridding off tileset asset
void TileMap::DrawDebug() const {
  DrawTexture(tileset, 0, 0, WHITE);

  int tilesPerRow = tileset.width / tileSize;
  int tilesPerCol = tileset.height / tileSize;

  for (int y = 0; y < tilesPerCol; y++) {
    for (int x = 0; x < tilesPerRow; x++) {
      int drawX = x * tileSize;
      int drawY = y * tileSize;
      int index = y * tilesPerRow + x;

      DrawRectangleLines(drawX, drawY, tileSize, tileSize, RED);
      DrawText(TextFormat("%d", index), drawX + 4, drawY + 4, 10, YELLOW);
    }
  }
}

// mark tiles as passable or not
bool TileMap::IsTilePassable(int tile) const {
  switch (tile) {
    case TILE_FLOOR_DIRT:
    case TILE_FLOOR_DIRT_2:
      return true;

    case TILE_PLANT:
    case TILE_PLANT_2:
    case TILE_MUSHROOM_RED:
    case TILE_MUSHROOM_PURPLE:
      return true;

    default:
      return false;
  }
}

// determines if the clicked tile can be walked on
bool TileMap::IsWorldPositionPassable(Vector2 worldPos) const {
  int tileX = (int)(worldPos.x / tileSize);
  int tileY = (int)(worldPos.y / tileSize);

  if (tileX < 0 || tileX >= mapWidth || tileY < 0 || tileY >= mapHeight) {
    return false;
  }

  int tile = groundMap[tileY][tileX];
  return IsTilePassable(tile);
}

// checks if the clicked area is within bounds of the map
bool TileMap::IsTileCoordinateInBounds(int x, int y) const {
  return x >= 0 && x < mapWidth && y >= 0 && y < mapHeight;
}

// returns the center of the tile
Vector2 TileMap::GetTileCenter(int x, int y) const {
  return {
    x * tileSize + tileSize / 2.0f,
    y * tileSize + tileSize / 2.0f
  };
}

// converts world size to tile X coordinate
int TileMap::WorldToTileX(float worldX) const {
  return (int)(worldX / tileSize);
}

// converts world to tile Y coordinate
int TileMap::WorldToTileY(float worldY) const {
  return (int)(worldY / tileSize);
}

int TileMap::GetTileSize() const {
  return tileSize;
}

// returns the ENUM value of a tile given a coordinate
int TileMap::GetTileAt(int x, int y) const {
  if (x < 0 || x >= mapWidth || y < 0 || y >= mapHeight) {
    return -1;
  }

  return groundMap[y][x];
}

// determines if clicked tile can be walked on
bool TileMap::TryGetPassableTileCenter(Vector2 worldPos, Vector2& outCenter) const {
  int tileX = WorldToTileX(worldPos.x);
  int tileY = WorldToTileY(worldPos.y);

  if (!IsTileCoordinateInBounds(tileX, tileY)) {
    return false;
  }

  int tile = GetTileAt(tileX, tileY);
  if (!IsTilePassable(tile)) {
    return false;
  }

  outCenter = GetTileCenter(tileX, tileY);
  return true;
}

const TileMap::Map& TileMap::GetMap() const {
  return groundMap;
}