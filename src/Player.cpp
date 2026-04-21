#include "Player.h"

Player::Player(float startX, float startY)
  : position{startX, startY},
    speed(200.0f),
    radius(20.0f) {
}

void Player::Update() {
  float dt = GetFrameTime();

  if (IsKeyDown(KEY_W)) position.y -= speed * dt;
  if (IsKeyDown(KEY_S)) position.y += speed * dt;
  if (IsKeyDown(KEY_A)) position.x -= speed * dt;
  if (IsKeyDown(KEY_D)) position.x += speed * dt;
}

void Player::Draw() {
  DrawCircleV(position, radius, DARKGRAY);
}