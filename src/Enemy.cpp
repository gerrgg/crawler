#include "Enemy.h"
#include <iostream>

Enemy::Enemy(float startX, float startY)
  : Character(startX, startY, "assets/player.png") {
  speed = 120.0f;
}

void Enemy::UpdateToward(Vector2 target, const TileMap& tileMap) {
  Vector2 enemyPos = GetPosition();

  int playerTileX = tileMap.WorldToTileX(target.x);
  int playerTileY = tileMap.WorldToTileY(target.y);

  int enemyTileX = tileMap.WorldToTileX(enemyPos.x);
  int enemyTileY = tileMap.WorldToTileY(enemyPos.y);

  int distanceX = playerTileX - enemyTileX;
  int distanceY = playerTileY - enemyTileY;

  // already in position
  if( std::abs(distanceX) + std::abs(distanceY) <= 1 ){
    movingToTarget = false;
    return;
  }

  // set
  int targetTileX = playerTileX;
  int targetTileY = playerTileY;

  // determine if we go 1 tile vertically or horizontally
  if (std::abs(distanceX) > std::abs(distanceY)) {
    targetTileX = playerTileX + (distanceX > 0 ? -1 : 1);
  } else {
    targetTileY = playerTileY + (distanceY > 0 ? -1 : 1);
  }

  // out of bounds
  if(! tileMap.IsTileCoordinateInBounds(targetTileX, targetTileY)){
    return;
  }

  int tile = tileMap.GetTileAt(targetTileX, targetTileY);

  // can we pass that tile?
  if( ! tileMap.IsTilePassable(tile) ){
    return;
  }

  Vector2 adjustedTarget = tileMap.GetTileCenter(targetTileX, targetTileY);

  std::cout << "X:" << target.x << std::endl << "Y:" << target.y << std::endl;
  SetTarget(adjustedTarget);
  Update();
}