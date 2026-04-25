#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

class Player : public Character {
public:
  Player(float startX, float startY);

  std::string GetClassName() const override {
    return "Player";
  }
};

#endif