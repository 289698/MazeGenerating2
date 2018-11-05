#include "game-mechanics.h"

GameMechanics::GameMechanics (Textures *textures, int width, int height) : textures_ (textures) {
  game_map_ = new GameMap (textures_, width, height);
}

GameMechanics::~GameMechanics () {
  if (game_map_ != nullptr)
    delete game_map_;
}
