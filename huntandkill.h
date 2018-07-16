#ifndef HUNTANDKILL_H
#define HUNTANDKILL_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "mazemap.h"

class HuntAndKill : public MazeMap {
public:
  HuntAndKill ();
  HuntAndKill (int maze_width, int maze_height);
  ~HuntAndKill ();
  void generate ();

private:
  bool huntPoint (Point &point);
  Point createPath (Point current_point);
  int randDirection(const Point &position);
};

#endif // HUNTANDKILL_H
