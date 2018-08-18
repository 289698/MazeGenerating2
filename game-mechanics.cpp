#include "game-mechanics.h"

GameMechanics::GameMechanics (/*QObject *parent) : QObject (parent*/) {
  game_map_ = new GameMap (50, 50, 2);
}

GameMechanics::~GameMechanics () {
  if (game_map_ != nullptr)
    delete game_map_;
}

bool GameMechanics::printFlagBrick(int x, int y, int layer) {
  return game_map_->printFlagBrick (x, y, layer);
}

int GameMechanics::blockIndex (int x, int y, int layer) {
  return game_map_->blockIndex (x, y, layer);
}

int GameMechanics::colorIndex (int x, int y, int layer) {
  return game_map_->colorIndex (x, y, layer);
}
