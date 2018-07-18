#include "gamemechanics.h"

GameMechanics::GameMechanics (int num_levels, Size first_level, int maze_increment,
                              QObject *parent) : QObject (parent) {
  num_levels_ = num_levels;
  mazes_ = new MazeMap *[num_levels_];

  mazes_ [0] = new HuntAndKill (first_level);
  mazes_ [0]->setStart (Point {6, 6});
  mazes_ [0]->setEnd ();
  for (int i = 1; i < num_levels_; ++ i){
    mazes_ [i] = new HuntAndKill (first_level += Size {maze_increment * 2, maze_increment * 2});
    mazes_ [i]->setStart (mazes_ [i - 1]->endPoint () + Point {maze_increment, maze_increment});
    mazes_ [i]->setEnd ();
  }

  player_position_ = mazes_ [0]->startPoint ();
}

GameMechanics::~GameMechanics () {
  delete [] mazes_;
}

int GameMechanics::distanceFromPlayer (int x, int y) {
  mazes_ [level_index_]->resetDistance (player_position_);
  return mazes_ [level_index_]->distanceFromPlayer (x, y);
}

void GameMechanics::tryMove (int direction) {
  if (mazes_ [level_index_]->at (player_position_.x, player_position_.y) & direction)
    return;
  switch (direction) {
    case direction::kUp:
      -- player_position_.y;
      break;
    case direction::kRight:
      ++ player_position_.x;
      break;
    case direction::kDown:
      ++ player_position_.y;
      break;
    case direction::kLeft:
      -- player_position_.x;
      break;
  }
}

void GameMechanics::tryEnter () {
  if (player_position_ == mazes_ [level_index_]->endPoint () && level_index_ < num_levels_ - 1) {
    ++ level_index_;
    player_position_ = mazes_ [level_index_]->startPoint ();
    return;
  }
  if (player_position_ == mazes_ [level_index_]->startPoint () && level_index_ > 0) {
    -- level_index_;
    player_position_ = mazes_ [level_index_]->endPoint ();
    return;
  }
  if (player_position_ == mazes_ [num_levels_ - 1]->endPoint ()) {
    // finish method
    exit (0);
  }
}
