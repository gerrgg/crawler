#include "Player.h"
#include "Debug.h"

Player::Player(float startX, float startY)
  : Character(startX, startY) {
    speed = 150.0f;
    AddAnimation("idle", "assets/soldier/Soldier-Idle.png", 6, 100, 100, 0.20f);
    AddAnimation("walk", "assets/soldier/Soldier-Walk.png",  8, 100, 100, 0.12f);
    AddAnimation("attack", "assets/soldier/Soldier-Attack01.png",  6, 100, 100, 0.08f, false);
  }

  void Player::MoveTo(Vector2 target) {
    attacking = false;
    SetTarget(target);
  }

 
  void Player::Attack(Enemy& enemy) {
    if (IsBusy()) {
      return;
    }

    FaceTarget(enemy.GetPosition());

    movingToTarget = false;
    attacking = true;
    PlayAnimation("attack");

    enemy.TakeDamage(20);

    DEBUG_LOG("Attack Enemy");
  }