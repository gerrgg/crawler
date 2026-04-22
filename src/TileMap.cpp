#include "TileMap.h"

TileMap::TileMap() {
  Load();
  LoadDefaultMap();
}

void TileMap::Load() {
  tileset = LoadTexture("assets/8_cave.png");
}

void TileMap::LoadDefaultMap() {

  // fill decor array with empty
  for (int y = 0; y < mapHeight; y++) {
    for (int x = 0; x < mapWidth; x++) {
      decorMap[y][x] = TILE_EMPTY;
    }
  }

  // fill ground map with simple procedural generation
  for (int y = 0; y < mapHeight; y++) {
    for (int x = 0; x < mapWidth; x++) {
      groundMap[y][x] = GetDefaultTile(x, y);
    }
  }

  // manually place decor
  decorMap[3][5] = TILE_PLANT_2;
  decorMap[4][18] = TILE_ROCK_2;
  decorMap[7][12] = TILE_PLANT;
  decorMap[8][29] = TILE_CRYSTAL_PINK;
  decorMap[10][18] = TILE_PLANT;
  decorMap[11][9] = TILE_ROCK;
  decorMap[14][4] = TILE_CRYSTAL_BLUE;
  decorMap[15][20] = TILE_ROCK_3;
}

void TileMap::Draw() const {
  DrawLayer(groundMap);
  DrawLayer(decorMap);
}

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

bool TileMap::IsWorldPositionPassable(Vector2 worldPos) const {
  int tileX = (int)(worldPos.x / tileSize);
  int tileY = (int)(worldPos.y / tileSize);

  if (tileX < 0 || tileX >= mapWidth || tileY < 0 || tileY >= mapHeight) {
    return false;
  }

  int tile = groundMap[tileY][tileX];
  return IsTilePassable(tile);
}

bool TileMap::IsTileCoordinateInBounds(int x, int y) const {
  return x >= 0 && x < mapWidth && y >= 0 && y < mapHeight;
}

Vector2 TileMap::GetTileCenter(int x, int y) const {
  return {
    x * tileSize + tileSize / 2.0f,
    y * tileSize + tileSize / 2.0f
  };
}

int TileMap::WorldToTileX(float worldX) const {
  return (int)(worldX / tileSize);
}

int TileMap::WorldToTileY(float worldY) const {
  return (int)(worldY / tileSize);
}

int TileMap::GetTileSize() const {
  return tileSize;
}

int TileMap::GetTileAt(int x, int y) const {
  if (x < 0 || x >= mapWidth || y < 0 || y >= mapHeight) {
    return -1;
  }

  return groundMap[y][x];
}

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