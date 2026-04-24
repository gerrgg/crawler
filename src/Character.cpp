#include "Character.h"
#include <cmath>

Character::Character(float startX, float startY, const std::string& spritePath)
  : position{startX, startY},
    moveTarget{startX, startY},
    speed(220.0f),
    radius(20.0f),
    movingToTarget(false),
    spriteScale(1.0f),
    currentFrame(1),
    currentRow(0),
    animationTimer(0.0f),
    animationSpeed(0.12f),
    walkFrameDir(1) {
  sprite = LoadTexture(spritePath.c_str());
}

Character::~Character() {
  if (sprite.id != 0) {
    UnloadTexture(sprite);
  }
}

Vector2 Character::GetPosition() const {
  return position;
}

void Character::SetTarget(Vector2 newTarget) {
  moveTarget = newTarget;
  movingToTarget = true;
}

void Character::Draw() {
  if (sprite.id == 0) {
    DrawCircleV(position, radius, MAROON);
    return;
  }

  float drawWidth = frameWidth * spriteScale;
  float drawHeight = frameHeight * spriteScale;

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

void Character::Update() {
  if (!movingToTarget) {
    currentFrame = 1;
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
    currentFrame = 1;
    return;
  }

  Vector2 direction = {
    toTarget.x / distance,
    toTarget.y / distance
  };

  if (std::abs(direction.x) > std::abs(direction.y)) {
    currentRow = direction.x > 0 ? 3 : 2;
  } else {
    currentRow = direction.y > 0 ? 0 : 1;
  }

  position.x += direction.x * speed * dt;
  position.y += direction.y * speed * dt;

  animationTimer += dt;

  if (animationTimer >= animationSpeed) {
    animationTimer = 0.0f;

    currentFrame += walkFrameDir;

    if (currentFrame >= 3) {
      currentFrame = 3;
      walkFrameDir = -1;
    }
    else if (currentFrame <= 1) {
      currentFrame = 1;
      walkFrameDir = 1;
    }
  }
}

void Character::DrawDebug() const {
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