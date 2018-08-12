#include "huntandkill.h"

HuntAndKill::HuntAndKill (Size maze_size) {
  newArray (maze_map_, maze_size.x + 2, maze_size.y + 2);
  resetArray (maze_map_, square::kSurrounded);
  generate ();
}

HuntAndKill::HuntAndKill (Size maze_size, Point start) {
  newArray (maze_map_, maze_size.x, maze_size.y);
  start_ = start;
  do {
    resetArray (maze_map_, square::kSurrounded);
    for (int x = 1; x < maze_map_.width - 1; ++ x) {
      maze_map_.array [x] [maze_map_.height - 1] = square::kUp + square::kOutside;
      maze_map_.array [x] [0] = square::kDown + square::kOutside;
    }
    for (int y = 1; y < maze_map_.height - 1; ++ y) {
      maze_map_.array [0] [y] = square::kRight + square::kOutside;
      maze_map_.array [maze_map_.width - 1] [y] = square::kLeft + square::kOutside;
    }
    maze_map_.array [0] [0] = square::kEmpty + square::kOutside;
    maze_map_.array [maze_map_.width - 1] [0] = square::kEmpty + square::kOutside;
    maze_map_.array [0] [maze_map_.height - 1] = square::kEmpty + square::kOutside;
    maze_map_.array [maze_map_.width - 1] [maze_map_.height - 1] = square::kEmpty + square::kOutside;
    generate ();
  } while (setEnd () < (maze_map_.width + maze_map_.height) * 3 - 30);
}

HuntAndKill::~HuntAndKill () {
  deleteArray (maze_map_);
  deleteArray (distance_from_player_);
}

void HuntAndKill::generate () {
  Point start;
  do
    start = Point {rand () % maze_map_.width, rand () % maze_map_.height};
  while ((maze_map_.array [start.x] [start.y] & square::kOutside) == square::kOutside);
  do
    createPath (start);
  while (huntPoint (start));
}

void HuntAndKill::createPath(Point current_point) {
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
        return;
    }
  }
}

int HuntAndKill::randDirection (Point const &position) {
  int number_of_directions = 0,
      legal_directions [4];

  if (position.y > 0 // CHECK UP
      && maze_map_.array [position.x] [position.y - 1] == square::kSurrounded
      && (maze_map_.array [position.x] [position.y - 1] & square::kOutside) != square::kOutside)
    legal_directions [number_of_directions ++] = direction::kUp;

  if (position.x < maze_map_.width - 1 // CHECK RIGHT
      && maze_map_.array [position.x + 1] [position.y] == square::kSurrounded
      && (maze_map_.array [position.x + 1] [position.y] & square::kOutside) != square::kOutside)
    legal_directions [number_of_directions ++] = direction::kRight;

  if (position.y < maze_map_.height - 1 // CHECK DOWN
      && maze_map_.array [position.x] [position.y + 1] == square::kSurrounded
      && (maze_map_.array [position.x] [position.y + 1] & square::kOutside) != square::kOutside)
    legal_directions [number_of_directions ++] = direction::kDown;

  if (position.x > 0 // CHECK LEFT
      && maze_map_.array [position.x - 1] [position.y] == square::kSurrounded
      && (maze_map_.array [position.x - 1] [position.y] & square::kOutside) != square::kOutside)
    legal_directions [number_of_directions ++] = direction::kLeft;

  if (number_of_directions == 0)
    return direction::kEmpty;
  return legal_directions [rand() % number_of_directions];
}

bool HuntAndKill::huntPoint (Point &point) {
  for (int y = 0; y < maze_map_.height; ++ y)
    for (int x = 0; x < maze_map_.width; ++ x){
      if (maze_map_.array [x] [y] == square::kSurrounded
          && (maze_map_.array [x] [y] & square::kOutside) != square::kOutside) {
        if (y > 0 // check UP
            && (maze_map_.array [x] [y - 1] & square::kSurrounded) != square::kSurrounded
            && (maze_map_.array [x] [y - 1] & square::kOutside) != square::kOutside) {
          maze_map_.array [x] [y] -= square::kUp;
          maze_map_.array [x] [y - 1] -= square::kDown;
          point = Point {x, y};
          return 1;
        }
        if (x < maze_map_.width - 1 // check RIGHT
            && (maze_map_.array [x + 1] [y] & square::kSurrounded) != square::kSurrounded
            && (maze_map_.array [x + 1] [y] & square::kOutside) != square::kOutside) {
          maze_map_.array [x] [y] -= square::kRight;
          maze_map_.array [x + 1] [y] -= square::kLeft;
          point = Point {x, y};
          return 1;
        }
        if (y < maze_map_.height - 1 // check DOWN
            && (maze_map_.array [x] [y + 1] & square::kSurrounded) != square::kSurrounded
            && (maze_map_.array [x] [y + 1] & square::kOutside) != square::kOutside) {
          maze_map_.array [x] [y] -= square::kDown;
          maze_map_.array [x] [y + 1] -= square::kUp;
          point = Point {x, y};
          return 1;
        }
        if (x > 0 // check LEFT
            && (maze_map_.array [x - 1] [y] & square::kSurrounded) != square::kSurrounded
            && (maze_map_.array [x - 1] [y] & square::kOutside) != square::kOutside) {
          maze_map_.array [x] [y] -= square::kLeft;
          maze_map_.array [x - 1] [y] -= square::kRight;
          point = Point {x, y};
          return 1;
        }
      }
    }
  return 0;
}
