#include "Enemy.h"
#include <cmath>
#include <iostream>

// set Enemy initial position
Enemy::Enemy(float startX, float startY)
  : position{startX, startY},
    moveTarget{startX, startY},
    speed(120.0f),
    radius(20.0f),
    movingToTarget(false),
    spriteScale(1.0f),
    currentFrame(2),
    currentRow(0),
    animationTimer(0.0f),
    animationSpeed(0.12f),
    walkFrameDir(1){
  sprite = LoadTexture("assets/player.png");
}

Enemy::~Enemy(){
  if(sprite.id != 0){
    UnloadTexture(sprite);
  }
}

// return Enemy position ([x, y])
Vector2 Enemy::GetPosition() const {
  return position;
}

// set new Enemy position (controlled by click)
void Enemy::SetTarget(Vector2 newTarget) {
  moveTarget = newTarget;
  movingToTarget = true;
}

void Enemy::DrawDebug() const {
  DrawTexture(sprite, 0, 0, WHITE);

  int tilesPerRow = sprite.width / frameWidth;
  int tilesPerCol = sprite.height / frameHeight;

  for (int y = 0; y < tilesPerCol; y++) {
    for (int x = 0; x < tilesPerRow; x++) {
      int drawX = x * frameWidth;
      int drawY = y * frameHeight;
      int index = y * tilesPerRow + x;

      DrawRectangleLines(drawX, drawY, frameWidth, frameHeight, RED);
      DrawText(TextFormat("%d", index), drawX + 4, drawY + 4, 10, YELLOW);
    }
  }
}

void Enemy::Draw() {
  if(sprite.id == 0){
    DrawCircleV(position, radius, MAROON);
    return;
  }

  float drawWidth = frameWidth * spriteScale;
  float drawHeight = frameHeight * spriteScale;

  // clip the asset
  Rectangle source = {
    (float)(currentFrame * frameWidth),
    (float)(currentRow * frameHeight),
    (float)frameWidth,
    (float)frameHeight
  };

  Rectangle dest = {
    position.x - drawWidth / 2.0f,
    position.y - drawHeight / 2.0f,
    drawWidth,
    drawHeight
  };

  DrawTexturePro(
    sprite,
    source,
    dest,
    {0.0f, 0.0f},
    0.0f,
    WHITE
  );
}

// animate moving position
void Enemy::Update() {
  if (!movingToTarget) {
    currentFrame = 1; // idle
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

  if (std::abs(direction.x) > std::abs(direction.y)) {
    if (direction.x > 0) {
      currentRow = 3; // right
    } else {
      currentRow = 2; // left
    }
  } else {
    if (direction.y > 0) {
      currentRow = 0; // down
    } else {
      currentRow = 1; // up
    }
  }

  position.x += direction.x * speed * dt;
  position.y += direction.y * speed * dt;

  // animate walk frames
  animationTimer += dt;

  
std::cout << "animationTimer: " << animationTimer
          << " | currentFrame: " << currentFrame
          << " | walkFrameDir: " << walkFrameDir
          << std::endl;

  if (animationTimer >= animationSpeed) {
    animationTimer = 0.0f;

    currentFrame += walkFrameDir;

    // bounce between 1 and 3
    if (currentFrame >= 3) {
      currentFrame = 2;
      walkFrameDir = -1;
    }
    else if (currentFrame <= 1) {
      currentFrame = 1;
      walkFrameDir = 1;
    }
  }
}