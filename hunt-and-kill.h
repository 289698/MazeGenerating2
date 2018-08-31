#ifndef HUNTANDKILL_H
#define HUNTANDKILL_H

#include <cstdlib>
#include <ctime>
#include "maze.h"

class HuntAndKill : public Maze {

public:
  HuntAndKill (int width, int height);
  HuntAndKill (int width, int height, Point start, bool maze_border_flag = 0);
  ~HuntAndKill ();

private:
  void generate ();
  void generate (Point start);
  bool huntPoint (Point &point);
  void createPath (Point current_point);
  int randDirection (const Point &position);
};

#endif // HUNTANDKILL_H
