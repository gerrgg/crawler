#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Enemy.h"

/**
 * Player-controlled character
 */
class Player : public Character {
public:
  /**
   * Creates a player at a defined position in the world
   * 
   * @param startX Starting X position in world space.
   * @param startY Starting Y position in world space.
   */
  Player(float startX, float startY);

  /**
   * Moves the player to a target world position
   * 
   * @param target Target position in world (usually where we walk or attack)
   */
  void MoveTo(Vector2 target);

  /**
   * Attacks an enemy and applies damage
   * 
   * @param enemy Enemy to attack
   */
  void Attack(Enemy& enemy);

  /**
   * Returns readable class name for debugging
   */
  std::string GetClassName() const override {
    return "Player";
  }
};

#endif