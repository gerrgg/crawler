#include "Debug.h"
#include "Character.h"
#include <cmath>

Character::Character(float startX, float startY)
  : position{ startX, startY },
    moveTarget{ startX, startY },
    speed(100.0f),
    radius(12.0f),
    movingToTarget(false),
    currentAnimation(""),
    spriteScale(2.0f),
    currentFrame(0),
    facingRight(true),
    attacking(false),
    dead(false),
    hurt(false),
    animationTimer(0.0f) {}

Character::~Character() {
  for (auto& pair : animations) {
    UnloadTexture(pair.second.texture);
  }
}

void Character::AddAnimation(
  const std::string& name,
  const std::string& path,
  int frames,
  int frameWidth,
  int frameHeight,
  float speed,
  bool loop
) {
  Animation animation;
  animation.path = path;
  animation.texture = LoadTexture(path.c_str());
  animation.frames = frames;
  animation.frameWidth = frameWidth;
  animation.frameHeight = frameHeight;
  animation.speed = speed;
  animation.loop = loop;

  animations[name] = animation;

  if (currentAnimation.empty()) {
    PlayAnimation(name);
  }
}

bool Character::IsBusy() const {
  return attacking && currentAnimation == "attack";
}

void Character::PlayAnimation(const std::string& name) {
  if (currentAnimation == name) {
    return;
  }

  if (animations.find(name) == animations.end()) {
    return;
  }

  currentAnimation = name;
  currentFrame = 0;
  animationTimer = 0.0f;
}


int Character::GetTileX(const TileMap& tileMap) const {
  return tileMap.WorldToTileX(position.x);
}

int Character::GetTileY(const TileMap& tileMap) const {
  return tileMap.WorldToTileY(position.y);
}

Vector2 Character::GetPosition() const {
  return position;
}

void Character::SetTarget(Vector2 newTarget) {
  moveTarget = newTarget;
  movingToTarget = true;
}

void Character::Draw() {
  if (currentAnimation.empty()) {
    return;
  }

  Animation& animation = animations[currentAnimation];

  Rectangle source = {
    static_cast<float>(currentFrame * animation.frameWidth),
    0.0f,
    static_cast<float>(animation.frameWidth),
    static_cast<float>(animation.frameHeight)
  };

  Rectangle dest = {
    position.x,
    position.y,
    animation.frameWidth * spriteScale,
    animation.frameHeight * spriteScale
  };

  Vector2 origin = {
    dest.width / 2.0f,
    dest.height / 2.0f
  };

  if( ! facingRight){
    source.width = -source.width;
  }

  DrawTexturePro(
    animation.texture,
    source,
    dest,
    origin,
    0.0f,
    WHITE
  );
}

void Character::FaceTarget(Vector2 target) {
  float dx = target.x - position.x;

  if (std::abs(dx) > 1.0f) {
    facingRight = dx > 0;
  }
}

void Character::Update() {
  float dt = GetFrameTime();

  if (dead || hurt) {
    Animation& animation = animations[currentAnimation];

    animationTimer += dt;

    if (animationTimer >= animation.speed) {
      animationTimer = 0.0f;
      currentFrame++;

      if (currentFrame >= animation.frames) {
        if (dead) {
          currentFrame = animation.frames - 1;
        } else {
          hurt = false;
          PlayAnimation("idle");
        }
      }
    }

    return;
  }

  if (movingToTarget) {
    FaceTarget(moveTarget);

    PlayAnimation("walk");

    Vector2 toTarget = {
      moveTarget.x - position.x,
      moveTarget.y - position.y
    };

    float distance = std::sqrt(toTarget.x * toTarget.x + toTarget.y * toTarget.y);

    if (distance < 2.0f) {
      position = moveTarget;
      movingToTarget = false;

      PlayAnimation(attacking ? "attack" : "idle");
    } else {
      Vector2 direction = {
        toTarget.x / distance,
        toTarget.y / distance
      };

      position.x += direction.x * speed * dt;
      position.y += direction.y * speed * dt;
    }
  } else {
    PlayAnimation(attacking ? "attack" : "idle");
  }

  UpdateAnimationFrames();

  if (currentAnimation == "attack" && currentFrame >= animations[currentAnimation].frames - 1) {
    attacking = false;
    PlayAnimation("idle");
  }
}

void Character::SetPosition(Vector2 newPosition) {
  position = newPosition;
  moveTarget = newPosition;
  movingToTarget = false;
}

void Character::UpdateAnimationFrames() {
  if (currentAnimation.empty()) {
    return;
  }

  Animation& animation = animations[currentAnimation];

  animationTimer += GetFrameTime();

  if (animationTimer < animation.speed) {
    return;
  }

  animationTimer = 0.0f;
  currentFrame++;

  if (currentFrame >= animation.frames) {
    currentFrame = animation.loop ? 0 : animation.frames - 1;
  }
}