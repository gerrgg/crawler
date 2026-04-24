#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "TileMap.h"
#include <string>

class Character {
public:
  Character(float startX, float startY, const std::string& spritePath);
  virtual ~Character();

  Vector2 GetPosition() const;
  void SetTarget(Vector2 newTarget);

  virtual void Update();
  virtual void Draw();
  virtual void DrawDebug() const;

  static constexpr int frameWidth = 32;
  static constexpr int frameHeight = 64;

  int GetTileX(const TileMap& tileMap) const;
  int GetTileY(const TileMap& tileMap) const;

protected:
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