#ifndef GAMEMECHANICS_H
#define GAMEMECHANICS_H

#include <QObject>
#include "huntandkill.h"

class GameMechanics : public QObject {
  Q_OBJECT
public:
  explicit GameMechanics (QObject *parent = 0);
  ~GameMechanics ();

  inline int at (int x, int y) {
    return levels_ [level_index_]->at(x, y);
  }
  inline int mazeWidth () {
    return levels_ [level_index_]->mazeWidth ();
  }
  inline int mazeHeight () {
    return levels_ [level_index_]->mazeHeight ();
  }
  inline int playerPositionX () {
    return player_position_.x;
  }
  inline int playerPositionY () {
    return player_position_.y;
  }
  inline int endX () {
    return levels_ [level_index_]->endX ();
  }
  inline int endY () {
    return levels_ [level_index_]->endY ();
  }
  inline void nextLevel () {
    if (level_index_ < num_levels_ - 1) ++ level_index_;
  }
  inline void previousLevel () {
    if (level_index_ > 0) -- level_index_;
  }

  void tryMove (int direction);
  void tryEnter ();

private:
  MazeMap **levels_;
  Point player_position_ {2, 5};
  int num_levels_ = 5;
  int level_index_ = 0;
};

#endif // GAMEMECHANICS_H
