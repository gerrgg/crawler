#ifndef GAME_H
#define GAME_H

#include "Player.h"

class Game {
public:
  Game();
  void Update();
  void Draw();

private:
  Player player;
};

#endif