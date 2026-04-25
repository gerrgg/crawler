#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "TileMap.h"

#include <string>
#include <unordered_map>

struct Animation {
  std::string path;
  Texture2D texture;
  int frames;
  int frameWidth;
  int frameHeight;
  float speed;
  bool loop;
};

class Character {
public:
  Character(float startX, float startY);
  virtual ~Character();

  Vector2 GetPosition() const;
  void SetTarget(Vector2 newTarget);

  virtual void Update();
  virtual void Draw();
  void SetPosition(Vector2 newPosition);

  void AddAnimation(
    const std::string& name,
    const std::string& path,
    int frames,
    int frameWidth,
    int frameHeight,
    float speed,
    bool loop = true
  );

  virtual std::string GetClassName() const {
    return "Character";
  }

  void FaceTarget(Vector2 target);

  void PlayAnimation(const std::string& name);
  bool IsBusy() const;

  int GetTileX(const TileMap& tileMap) const;
  int GetTileY(const TileMap& tileMap) const;

protected:
  Vector2 position;
  Vector2 moveTarget;

  float speed;
  float radius;
  bool movingToTarget;

  std::unordered_map<std::string, Animation> animations;
  std::string currentAnimation;

  float spriteScale;

  int currentFrame;
  float animationTimer;

  bool facingRight;
  bool attacking;
};

#endif