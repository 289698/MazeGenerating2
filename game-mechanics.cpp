#include "game-mechanics.h"

GameMechanics::GameMechanics (int height, int width, const QString &name) {
  game_map_ = new GameMap (height, width, name);
}

GameMechanics::~GameMechanics () {
  if (game_map_ != nullptr)
    delete game_map_;
}
