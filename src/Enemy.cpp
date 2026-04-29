#include "Enemy.h"
#include "Debug.h"

Enemy::Enemy(float startX, float startY)
  : Character(startX, startY) {
    AddAnimation("idle", "assets/orc/Orc-Idle.png", 6, 100, 100, 0.20f);
    AddAnimation("walk", "assets/orc/Orc-Walk.png",  8, 100, 100, 0.24f);
    AddAnimation("attack", "assets/orc/Orc-Attack01.png",  6, 100, 100, 0.18f, false);
    AddAnimation("dead", "assets/orc/Orc-Death.png",  4, 100, 100, 0.18f, false);
    AddAnimation("hurt", "assets/orc/Orc-Hurt.png",  4, 100, 100, 0.18f, false);
  }

void Enemy::UpdateToward(Vector2 target, const TileMap& tileMap) {
  if(dead || hurt){
    Update();
    return;
  }

  Vector2 enemyPos = GetPosition();

  int playerTileX = tileMap.WorldToTileX(target.x);
  int playerTileY = tileMap.WorldToTileY(target.y);

  int enemyTileX = tileMap.WorldToTileX(enemyPos.x);
  int enemyTileY = tileMap.WorldToTileY(enemyPos.y);

  int distanceX = playerTileX - enemyTileX;
  int distanceY = playerTileY - enemyTileY;

  // already in position
  if (std::abs(distanceX) + std::abs(distanceY) <= 1) {
    if (movingToTarget) {
      Update();
      return;
    }

    movingToTarget = false;
    attacking = true;
    Update();
    return;
  }

  attacking = false;

  // set
  int targetTileX = playerTileX;
  int targetTileY = playerTileY;

  // determine if we go 1 tile vertically or horizontally
  if (std::abs(distanceX) > std::abs(distanceY)) {
    targetTileX = playerTileX + (distanceX > 0 ? -1 : 1);
  } else {
    targetTileY = playerTileY + (distanceY > 0 ? -1 : 1);
  }

  // out of bounds
  if(! tileMap.IsTileCoordinateInBounds(targetTileX, targetTileY)){
    return;
  }

  int tile = tileMap.GetTileAt(targetTileX, targetTileY);

  // can we pass that tile?
  if( ! tileMap.IsTilePassable(tile) ){
    return;
  }

  Vector2 adjustedTarget = tileMap.GetTileCenter(targetTileX, targetTileY);
  SetTarget(adjustedTarget);


  Update();
}

void Enemy::TakeDamage(int damage) {
  if (dead) {
    return;
  }

  movingToTarget = false;
  attacking = false;

  health -= damage;

  if (health <= 0) {
    health = 0;
    dead = true;
    hurt = false;
    PlayAnimation("dead");
    return;
  }

  hurt = true;
  PlayAnimation("hurt");
}

void Enemy::Update() {
  if (dead || hurt) {
    UpdateAnimationFrames();

    Animation& animation = animations[currentAnimation];

    if (currentFrame >= animation.frames - 1) {
      if (dead) {
        currentFrame = animation.frames - 1;
        
      } else {
        hurt = false;
        PlayAnimation("idle");
      }
    }

    return;
  }

  Character::Update();
}

void Enemy::DrawHealthBar() const {
  if( health == maxHealth ) return;

  float barWidth = 30.0f;
  float barHeight = 6.0f;

  float x = position.x - barWidth / 2.0f;
  float y = position.y - 25.0f;

  float healthPercent = (float)health / (float)maxHealth;

  Rectangle background = {
    x,
    y,
    barWidth,
    barHeight
  };

  Rectangle fill = {
    x,
    y,
    barWidth * healthPercent,
    barHeight
  };

  DrawRectangleRec(background, DARKGRAY);
  DrawRectangleRec(fill, RED);
  DrawRectangleLinesEx(background, 1.0f, BLACK);
}
