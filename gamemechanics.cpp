#include "gamemechanics.h"

GameMechanics::GameMechanics (QObject *parent) : QObject (parent) {
  levels_ = new MazeMap *[num_levels_];
  for (int i = 0; i < num_levels_; ++ i)
    levels_ [i] = new HuntAndKill (20, 10);
}

GameMechanics::~GameMechanics () {
  delete [] levels_;
}

void GameMechanics::tryMove (int direction) {
  if (levels_ [level_index_]->at (player_position_.x, player_position_.y) & direction)
    return;
  switch (direction) {
    case direction::kUp:
      -- player_position_.y;
      break;
    case direction::kRight:
      ++ player_position_.x;
      break;
    case direction ::kDown:
      ++ player_position_.y;
      break;
    case direction::kLeft:
      -- player_position_.x;
      break;
  }
}

void GameMechanics::tryEnter () {
  if (player_position_ == levels_ [level_index_]->endPoint())
    qDebug() << "wow";
}
