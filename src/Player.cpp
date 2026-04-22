#include "Player.h"
#include <cmath>

// set player initial position
Player::Player(float startX, float startY)
  : position{startX, startY},
    moveTarget{startX, startY},
    speed(220.0f),
    radius(20.0f),
    movingToTarget(false) {
}

// return player position ([x, y])
Vector2 Player::GetPosition() const {
  return position;
}

// set new player position (controlled by click)
void Player::SetTarget(Vector2 newTarget) {
  moveTarget = newTarget;
  movingToTarget = true;
}

// animate moving position
void Player::Update() {
  if (!movingToTarget) {
    return;
  }

  float dt = GetFrameTime();

  Vector2 toTarget = {
    moveTarget.x - position.x,
    moveTarget.y - position.y
  };

  float distance = std::sqrt(toTarget.x * toTarget.x + toTarget.y * toTarget.y);

  if (distance < 2.0f) {
    position = moveTarget;
    movingToTarget = false;
    return;
  }

  Vector2 direction = {
    toTarget.x / distance,
    toTarget.y / distance
  };

  position.x += direction.x * speed * dt;
  position.y += direction.y * speed * dt;
}

void Player::Draw() {
  DrawCircleV(position, radius, MAROON);
}