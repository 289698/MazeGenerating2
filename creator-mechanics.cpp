#include "creator-mechanics.h"

CreatorMechanics::CreatorMechanics (int height, int width, const QString &name) {
  game_map_ = new GameMap (height, width, name);
}

CreatorMechanics::~CreatorMechanics () {
  if (game_map_ != nullptr)
    delete game_map_;
}


