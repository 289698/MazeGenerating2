#ifndef GAMEMECHANICS_H
#define GAMEMECHANICS_H

#include <QObject>
#include "huntandkill.h"

class GameMechanics : public QObject {
  Q_OBJECT
public:
  explicit GameMechanics (int num_levels, Size first_level, int maze_increment, QObject *parent = 0);
  ~GameMechanics ();

  inline int at (int x, int y) const { return mazes_ [level_index_]->at (x, y); }
  inline int at (Point position) const { return mazes_ [level_index_]->at (position); }
  inline int backgroundAt (int x, int y) const { return mazes_ [level_index_]->backgroundAt (x, y); }
  inline int backgroundAt (Point position) const
  { return mazes_ [level_index_]->backgroundAt (position); }
  inline Size mazeSize () const { return mazes_ [level_index_]->mazeSize (); }
  inline int mazeWidth () const { return mazes_ [level_index_]->mazeWidth (); }
  inline int mazeHeight () const { return mazes_ [level_index_]->mazeHeight (); }
  inline Point playerPosition () const { return player_position_; }
  inline int playerPositionX () const { return player_position_.x; }
  inline int playerPositionY () const { return player_position_.y; }
  inline Point startPoint () const { return mazes_ [level_index_]->startPoint (); }
  inline int startX () const { return mazes_ [level_index_]->startX (); }
  inline int startY () const { return mazes_ [level_index_]->startY (); }
  inline Point endPoint () const { return mazes_ [level_index_]->endPoint (); }
  inline int endX () const { return mazes_ [level_index_]->endX (); }
  inline int endY () const { return mazes_ [level_index_]->endY (); }
  inline int numLevels () const { return num_levels_; }
  inline int currentLevel () const { return level_index_; }
  inline bool isGod () const { return god_mode_; }
  inline void toogleGodMode () { god_mode_ = !god_mode_; }
  inline void nextLevel () { if (level_index_ < num_levels_ - 1) ++ level_index_; }
  inline void previousLevel () { if (level_index_ > 0) -- level_index_; }
  inline void jumpToStart () { player_position_ = mazes_ [level_index_]->startPoint (); }
  inline void jumpToEnd () { player_position_ = mazes_ [level_index_]->endPoint (); }

  bool tryMove (int direction);
  bool tryEnter();
  int distanceFromPlayer (int x, int y);

private:
  MazeMap **mazes_;
  Point player_position_;
  int num_levels_;
  int level_index_ = 0;
  bool god_mode_ = true;
};

#endif // GAMEMECHANICS_H
