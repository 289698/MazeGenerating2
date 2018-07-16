#include "huntandkill.h"

HuntAndKill::HuntAndKill () {
  newArray (maze_map_, 20, 10);
  resetArray (maze_map_, square::kUnvalid);
  generate ();
}

HuntAndKill::HuntAndKill (int maze_width, int maze_height) {
  newArray (maze_map_, maze_width, maze_height);
  resetArray (maze_map_, square::kUnvalid);
  generate ();
}

HuntAndKill::~HuntAndKill () {
  deleteArray (maze_map_);
}

void HuntAndKill::generate () {
  Point start {2, 2};
  do {
    createPath (start);
  } while (huntPoint (start));
}

Point HuntAndKill::createPath (Point current_point) {
  while (true) {
    switch (randDirection (current_point)) {
      case direction::kUp:
        maze_map_.array [current_point.x] [current_point.y] -= square::kUp;
        maze_map_.array [current_point.x] [current_point.y - 1] -= square::kDown;
        current_point += Point {0, -1};
        break;
      case direction::kRight:
        maze_map_.array [current_point.x] [current_point.y] -= square::kRight;
        maze_map_.array [current_point.x + 1] [current_point.y] -= square::kLeft;
        current_point += Point {1, 0};
        break;
      case direction::kDown:
        maze_map_.array [current_point.x] [current_point.y] -= square::kDown;
        maze_map_.array [current_point.x] [current_point.y + 1] -= square::kUp;
        current_point += Point {0, 1};
        break;
      case direction::kLeft:
        maze_map_.array [current_point.x] [current_point.y] -= square::kLeft;
        maze_map_.array [current_point.x - 1] [current_point.y] -= square::kRight;
        current_point += Point {-1, 0};
        break;
      default:
        return current_point;
    }
  }
}

int HuntAndKill::randDirection (Point const &position) {
  int number_of_directions = 0,
      legal_directions [4];

  if (position.y > 0 &&
      maze_map_.array [position.x] [position.y - 1] == square::kUnvalid) // UP
    legal_directions [number_of_directions ++] = direction::kUp;

  if (position.x < maze_map_.width - 1 &&
      maze_map_.array [position.x + 1] [position.y] == square::kUnvalid) // RIGHT
    legal_directions [number_of_directions ++] = direction::kRight;

  if (position.y < maze_map_.height - 1 &&
      maze_map_.array [position.x] [position.y + 1] == square::kUnvalid) // DOWN
    legal_directions [number_of_directions ++] = direction::kDown;

  if (position.x > 0 &&
      maze_map_.array [position.x - 1] [position.y] == square::kUnvalid) // LEFT
    legal_directions [number_of_directions ++] = direction::kLeft;

  if (number_of_directions == 0)
    return direction::kUnvalid;
  return legal_directions [rand() % number_of_directions];
}

bool HuntAndKill::huntPoint (Point &point) {
  for (int y = 0; y < maze_map_.height; ++ y)
    for (int x = 0; x < maze_map_.width; ++ x)
      if (maze_map_.array [x] [y] == square::kUnvalid) {
        if (y > 0 && maze_map_.array [x] [y - 1] != square::kUnvalid) { // check UP
          maze_map_.array [x] [y] -= square::kUp;
          maze_map_.array [x] [y - 1] -= square::kDown;
          point = Point {x, y};
          return 1;
        }
        if (x < maze_map_.width - 1 && maze_map_.array [x + 1] [y] != square::kUnvalid) { // check RIGHT
          maze_map_.array [x] [y] -= square::kRight;
          maze_map_.array [x + 1] [y] -= square::kLeft;
          point = Point {x, y};
          return 1;
        }
        if (y < maze_map_.height - 1 && maze_map_.array [x] [y + 1] != square::kUnvalid) { // check DOWN
          maze_map_.array [x] [y] -= square::kDown;
          maze_map_.array [x] [y + 1] -= square::kUp;
          point = Point {x, y};
          return 1;
        }
        if (x > 0 && maze_map_.array [x - 1] [y] != square::kUnvalid) { // check LEFT
          maze_map_.array [x] [y] -= square::kLeft;
          maze_map_.array [x - 1] [y] -= square::kRight;
          point = Point {x, y};
          return 1;
        }
      }
  return 0;
}
