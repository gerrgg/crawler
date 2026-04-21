#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class Player {
public:
  Player(float startX, float startY);

  void Update();
  void Draw();

private:
  Vector2 position;
  float speed;
  float radius;
};

#endif