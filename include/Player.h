#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class Player {
public:
  Player(float startX, float startY);

  void Update();
  void Draw();
  void SetTarget(Vector2 newTarget);
  Vector2 GetPosition() const;

private:
  Vector2 position;
  Vector2 moveTarget;
  float speed;
  float radius;
  bool movingToTarget;
};

#endif