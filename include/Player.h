#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class Player {
public:
  Player(float startX, float startY);

  void Update(); // update player position
  void Draw(); // draw player initial position

  void SetTarget(Vector2 newTarget); // where the player is moving to
  Vector2 GetPosition() const; // return coordinates

private:
  Vector2 position;
  Vector2 moveTarget;
  float speed;
  float radius;
  bool movingToTarget;
};

#endif