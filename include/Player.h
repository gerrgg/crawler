#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Enemy.h"

class Player : public Character {
public:
  Player(float startX, float startY);

  std::string GetClassName() const override {
    return "Player";
  }

  void Click();
  void MoveTo(Vector2 target);
  void Attack(Enemy& enemy);
};

#endif