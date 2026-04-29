#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "TileMap.h"

#include <string>
#include <unordered_map>

/**
 * Data structure for playing sprite-based animation
 */
struct Animation {
  std::string path;
  Texture2D texture;
  int frames;
  int frameWidth;
  int frameHeight;
  float speed;
  bool loop;
};


/**
 * Base class for world characters
 * Player and Enemy inherit from this class and override update methods
 */
class Character {
public:
  /**
   * Creates a character at a defined position in the world
   * 
   * @param startX Starting X position in world
   * @param startY Starting Y position in world
   */
  Character(float startX, float startY);

  /**
   * Unloads animation textures related to character instance
   */
  virtual ~Character();

  /**
   * Draws the current animation frame
   */
  virtual void Draw();

  /**
   * Updates movement and animation states
   */
  virtual void Update();

  /**
   * Gets the character position in world
   * 
   * @return character world position
   */
  Vector2 GetPosition() const;

  /**
   * Sets a movement target
   * 
   * @param target coordinates to target position
   */
  void SetTarget(Vector2 newTarget);

  /**
   * Places the character at a world position, no animation
   * 
   * Also resets movement target to same position
   * 
   * @param newPosition New position in world space
   */
  void SetPosition(Vector2 newPosition);

  /**
   * Adds an animation to the character
   * 
   * @param name Animation key, such as "idle", "walk", or "attack"
   * @param path File path
   * @param frames number of frames
   * @param frameWidth width of the frame
   * @param frameHeight height of the frame
   * @param speed speed of the animation
   * @param loop whether or not the animation should loop
   */
  void AddAnimation(
    const std::string& name,
    const std::string& path,
    int frames,
    int frameWidth,
    int frameHeight,
    float speed,
    bool loop = true
  );

  /**
   * Returns readable class name for debugging
   */
  virtual std::string GetClassName() const {
    return "Character";
  }

  /**
   * Switches to an animation by name
   * 
   * @param name Animation key to play
   */
  void PlayAnimation(const std::string& name);

  /**
   * Turns the charactger to face the target position
   * 
   * @param target Target position in world (target.x - position.x)
   */
  void FaceTarget(Vector2 target);

  /**
   * Checks whether the character is locked in another animation (attack)
   * 
   * @return true if character is currently attacking
   */
  bool IsBusy() const;

  /**
   * Gets the tile X coordinate for character position
   * 
   * @param tileMap Tile map used for converting tile coordinates to world coordinates
   * @return Tile X coordinate
   */
  int GetTileX(const TileMap& tileMap) const;

  /**
   * Gets the tile Y coordinate for character position
   * 
   * @param tileMap Tile map used for converting tile coordinates to world coordinates
   * @return Tile Y coordinate
   */
  int GetTileY(const TileMap& tileMap) const;

protected:
  /**
   * Updates the animation based on frame timing
   */
  void UpdateAnimationFrames();

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

  bool dead;
  bool hurt;
};

#endif