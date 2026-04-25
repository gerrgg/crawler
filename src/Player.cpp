#include "Player.h"

Player::Player(float startX, float startY)
  : Character(startX, startY) {
    speed = 150.0f;
    AddAnimation("idle", "assets/soldier/Soldier-Idle.png", 6, 100, 100, 0.20f);
    AddAnimation("walk", "assets/soldier/Soldier-Walk.png",  8, 100, 100, 0.12f);
  }