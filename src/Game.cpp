#include "Game.h"

Game::Game()
  : player(400.0f, 225.0f) {
}

void Game::Update() {
  player.Update();
}

void Game::Draw() {
  player.Draw();
}