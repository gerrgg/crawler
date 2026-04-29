#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "Player.h"
#include "Enemy.h"
#include "TileMap.h"
#include <string>

/**
 * High level game state for managing screens
 */
enum class GameState {
  Logo, 
  Title, 
  Playing, 
  PauseMenu 
};

/**
 * Main game controller
 * 
 * Owns the map, player, enemies, camera and input handling.
 */
class Game {
public:
  /**
   * Creates the game using a virtual render size
   * 
   * @param virtualWidth Width of the internal game resolution
   * @param virtualHeight Height of the internal game resolution
   */
  Game(int virtualWidth, int virtualHeight);


  /**
   * Updates current game state
   */
  void Update(); 
  
  /**
   * Draws initial game state
   */
  void Draw(); 

  /**
   * Whether the game should close or not
   * 
   * @return true if the game should quit (user selected)
   */
  bool ShouldQuit() const; 

private:
  // map object
  TileMap tileMap;

  int screenWidth;
  int screenHeight;

  bool shouldQuit;

  float logoAlpha;
  float logoTimer;
  
  int pauseSelection;

  GameState currentState;

  Texture2D logo;
  Texture2D title;

  Player player;

  Camera2D camera;

  Enemy enemy;

  /**
   * Converts mouse position to world/map coordinates
   * 
   * @return Mouse position in world
   */
  Vector2 GetVirtualMouseWorld() const;

  /**
   * Converts real mouse position to the virtual screen coordinates
   * 
   * @return mouse position in virtual screen space
   */
  Vector2 GetVirtualMouse() const;

  /**
   * Reusable UI button
   * 
   * @param text Button label.
   * @param rect Button position and size.
   * @param selected Whether the button is currently selected.
   * @return true if the button was clicked.
   */
  bool MakeButton(const std::string& text, Rectangle rect, bool selected);

  /**
   * Creates a horizontally centered button rectangle.
   *
   * @param y Button Y position.
   * @param width Button width.
   * @param height Button height.
   * @return Centered button rectangle.
   */
  Rectangle MakeCenteredButtonRect(float y, float width, float height);

  /**
   * Handles player input while playing.
   */
  void HandlePlayerInput();

  /**
   * Finds an enemy at a world position.
   *
   * @param worldPos Position to check in world space.
   * @return Pointer to enemy if found, otherwise nullptr.
   */
  Enemy* GetEnemyAtWorldPosition(Vector2 worldPos);


  bool IsEnemyAtTile(Vector2 tileCenter);

  void DrawLogo();
  void UpdateLogo();

  void DrawTitle();
  void UpdateTitle();

  void DrawPlaying();
  void UpdatePlaying();

  void UpdatePauseMenu();
  void DrawPauseMenu();

  /**
   * Resets gameplay state
   */
  void ResetGame();
};

#endif