#ifndef HUNTANDKILL_H
#define HUNTANDKILL_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "mazemap.h"

class HuntAndKill : public MazeMap {
public:
  HuntAndKill (Size maze_size);
  HuntAndKill (Size maze_size, Point start);
  ~HuntAndKill ();

private:
  void generate ();
  bool huntPoint (Point &point);
  void createPath (Point current_point);
  int randDirection (const Point &position);
};

#endif // HUNTANDKILL_H
