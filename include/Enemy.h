#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "TileMap.h"

class Enemy : public Character {
public:
  Enemy(float startX, float startY);

  void UpdateToward(Vector2 target, const TileMap& tileMap);
};

#endif