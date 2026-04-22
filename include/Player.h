#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class Player {
public:
  Player(float startX, float startY);
  ~Player();

  Vector2 GetPosition() const; // return coordinates
  void SetTarget(Vector2 newTarget); // where the player is moving to

  void Update(); // update player position
  void Draw(); // draw player initial position
  void DrawDebug() const;

  static constexpr int frameWidth = 32;
  static constexpr int frameHeight = 64;

private:
  Vector2 position;
  Vector2 moveTarget;
  float speed;
  float radius;
  bool movingToTarget;

  Texture2D sprite;
  float spriteScale;

  int currentFrame;
  int currentRow;
  float animationTimer;
  float animationSpeed;

  int walkFrameDir;

};

#endif