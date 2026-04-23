#ifndef Enemy_H
#define Enemy_H

#include "raylib.h"

class Enemy {
public:
  Enemy(float startX, float startY);
  ~Enemy();

  Vector2 GetPosition() const; // return coordinates
  void SetTarget(Vector2 newTarget); // where the Enemy is moving to

  void Update(); // update Enemy position
  void Draw(); // draw Enemy initial position
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