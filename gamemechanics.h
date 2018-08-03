#ifndef GAMEMECHANICS_H
#define GAMEMECHANICS_H

#include <QObject>
#include "huntandkill.h"

class GameMechanics : public QObject {
  Q_OBJECT
public:
  explicit GameMechanics (int num_levels, Size first_level, int maze_increment, QObject *parent = 0);
  ~GameMechanics ();

  inline int at (int x, int y) const { return mazes_ [level_index_]->at(x, y); }
  inline int mazeWidth () const { return mazes_ [level_index_]->mazeWidth (); }
  inline int mazeHeight () const { return mazes_ [level_index_]->mazeHeight (); }
  inline int playerPositionX () const { return player_position_.x; }
  inline int playerPositionY () const { return player_position_.y; }
  inline int numLevels () const { return num_levels_; }
  inline int currentLevel () const { return level_index_; }
  inline int startX () const { return mazes_ [level_index_]->startX (); }
  inline int startY () const { return mazes_ [level_index_]->startY (); }
  inline int endX () const { return mazes_ [level_index_]->endX (); }
  inline int endY () const { return mazes_ [level_index_]->endY (); }
  inline bool isGod () const { return god_mode_; }
  inline void toogleGodMode () { god_mode_ = !god_mode_; }
  inline void nextLevel () { if (level_index_ < num_levels_ - 1) ++ level_index_; }
  inline void previousLevel () { if (level_index_ > 0) -- level_index_; }
  inline void jumpToStart () { player_position_ = mazes_ [level_index_]->startPoint (); }
  inline void jumpToEnd () { player_position_ = mazes_ [level_index_]->endPoint (); }

  void tryMove (int direction);
  void tryEnter ();
  int distanceFromPlayer (int x, int y);

private:
  MazeMap **mazes_;
  Point player_position_;
  int num_levels_;
  int level_index_ = 0;
  bool god_mode_ = true;
};

#endif // GAMEMECHANICS_H
