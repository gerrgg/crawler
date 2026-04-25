#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "TileMap.h"

class Enemy : public Character {
public:
  Enemy(float startX, float startY);

  void UpdateToward(Vector2 target, const TileMap& tileMap);
  void Update() override;
  void TakeDamage(int damage);
  void DrawHealthBar() const;

  bool IsDead() const { return dead; }

  std::string GetClassName() const override {
    return "Enemy";
  }
private:
  int health = 100;
  int maxHealth = 100;

  bool dead = false;
  bool hurt = false;
};

#endif