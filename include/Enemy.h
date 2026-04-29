#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "TileMap.h"


/**
 * Enemy character that chases and attacks player, takes damage and dies.
 */
class Enemy : public Character {
public:
  /**
   * Creates an enemy at world position
   * 
   * @param startX Starting X position in world
   * @param startY Starting Y position in world
   */
  Enemy(float startX, float startY);

  /**
   * Updates enemy movement towards target postiion
   * 
   * @param target Target position in world space (usually where the player is)
   * @param tileMap Tile map used for loose pathing and tile checks
   */
  void UpdateToward(Vector2 target, const TileMap& tileMap);

  /**
   * Updates enemy animation and hurt/death state.
   */
  void Update() override;

  /**
   * Applies damage to the enemy.
   * 
   * @param damage Amount of health to remove.
   */
  void TakeDamage(int damage);

  /**
   * Draws the enemy health bar.
   */
  void DrawHealthBar() const;

  /**
   * Checks whether the enemy is dead.
   * 
   * @return true if dead, false otherwise.
   */
  bool IsDead() const { return dead; }

  /**
   * Returns class for debugging.
   */
  std::string GetClassName() const override {
    return "Enemy";
  }

private:
  int health = 100;
  int maxHealth = 100;

  bool dead = false;
  bool hurt = false;
};

#endif