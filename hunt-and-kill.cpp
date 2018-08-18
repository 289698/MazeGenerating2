#include "hunt-and-kill.h"

HuntAndKill::HuntAndKill (int width, int height) {
  newArray (maze_, width, height);
  resetArray (maze_, mazeSquare::Surrounded);
  generate ();
}

HuntAndKill::HuntAndKill (int width, int height, Point start, bool maze_border_flag) {
  newArray (maze_, width, height);
  start_ = start;
  do {
    resetArray (maze_, mazeSquare::Surrounded);
    if (maze_border_flag) {
      for (int x = 1; x < maze_.width - 1; ++ x) {
        maze_.array [x] [maze_.height - 1] = mazeSquare::Up + mazeSquare::Outside;
        maze_.array [x] [0] = mazeSquare::Down + mazeSquare::Outside;
      }
      for (int y = 1; y < maze_.height - 1; ++ y) {
        maze_.array [0] [y] = mazeSquare::Right + mazeSquare::Outside;
        maze_.array [maze_.width - 1] [y] = mazeSquare::Left + mazeSquare::Outside;
      }
      maze_.array [0] [0] = mazeSquare::Empty + mazeSquare::Outside;
      maze_.array [maze_.width - 1] [0] = mazeSquare::Empty + mazeSquare::Outside;
      maze_.array [0] [maze_.height - 1] = mazeSquare::Empty + mazeSquare::Outside;
      maze_.array [maze_.width - 1] [maze_.height - 1] = mazeSquare::Empty + mazeSquare::Outside;
    }
    generate (start);
  } while (false);//setEnd () < (maze_.width + maze_.height) * 3 - 30);
}

HuntAndKill::~HuntAndKill () {
  deleteArray (maze_);
  deleteArray (distance_from_player_);
}

void HuntAndKill::generate () {
  Point start;
  do
    start = Point {rand () % maze_.width, rand () % maze_.height};
  while ((maze_.array [start.x] [start.y] & mazeSquare::Outside) == mazeSquare::Outside);
  do
    createPath (start);
  while (huntPoint (start));
}

void HuntAndKill::generate (Point start) {
  do
    createPath (start);
  while (huntPoint (start));
}

void HuntAndKill::createPath(Point current_point) {
  while (true) {
    switch (randDirection (current_point)) {
      case direction::Up:
        maze_.array [current_point.x] [current_point.y] -= mazeSquare::Up;
        maze_.array [current_point.x] [current_point.y - 1] -= mazeSquare::Down;
        current_point += Point {0, -1};
        break;
      case direction::Right:
        maze_.array [current_point.x] [current_point.y] -= mazeSquare::Right;
        maze_.array [current_point.x + 1] [current_point.y] -= mazeSquare::Left;
        current_point += Point {1, 0};
        break;
      case direction::Down:
        maze_.array [current_point.x] [current_point.y] -= mazeSquare::Down;
        maze_.array [current_point.x] [current_point.y + 1] -= mazeSquare::Up;
        current_point += Point {0, 1};
        break;
      case direction::Left:
        maze_.array [current_point.x] [current_point.y] -= mazeSquare::Left;
        maze_.array [current_point.x - 1] [current_point.y] -= mazeSquare::Right;
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
      && maze_.array [position.x] [position.y - 1] == mazeSquare::Surrounded
      && (maze_.array [position.x] [position.y - 1] & mazeSquare::Outside) != mazeSquare::Outside)
    legal_directions [number_of_directions ++] = direction::Up;

  if (position.x < maze_.width - 1 // CHECK RIGHT
      && maze_.array [position.x + 1] [position.y] == mazeSquare::Surrounded
      && (maze_.array [position.x + 1] [position.y] & mazeSquare::Outside) != mazeSquare::Outside)
    legal_directions [number_of_directions ++] = direction::Right;

  if (position.y < maze_.height - 1 // CHECK DOWN
      && maze_.array [position.x] [position.y + 1] == mazeSquare::Surrounded
      && (maze_.array [position.x] [position.y + 1] & mazeSquare::Outside) != mazeSquare::Outside)
    legal_directions [number_of_directions ++] = direction::Down;

  if (position.x > 0 // CHECK LEFT
      && maze_.array [position.x - 1] [position.y] == mazeSquare::Surrounded
      && (maze_.array [position.x - 1] [position.y] & mazeSquare::Outside) != mazeSquare::Outside)
    legal_directions [number_of_directions ++] = direction::Left;

  if (number_of_directions == 0)
    return direction::Empty;
  return legal_directions [rand() % number_of_directions];
}

bool HuntAndKill::huntPoint (Point &point) {
  for (int y = 0; y < maze_.height; ++ y)
    for (int x = 0; x < maze_.width; ++ x){
      if (maze_.array [x] [y] == mazeSquare::Surrounded
          && (maze_.array [x] [y] & mazeSquare::Outside) != mazeSquare::Outside) {
        if (y > 0 // check UP
            && (maze_.array [x] [y - 1] & mazeSquare::Surrounded) != mazeSquare::Surrounded
            && (maze_.array [x] [y - 1] & mazeSquare::Outside) != mazeSquare::Outside) {
          maze_.array [x] [y] -= mazeSquare::Up;
          maze_.array [x] [y - 1] -= mazeSquare::Down;
          point = Point {x, y};
          return 1;
        }
        if (x < maze_.width - 1 // check RIGHT
            && (maze_.array [x + 1] [y] & mazeSquare::Surrounded) != mazeSquare::Surrounded
            && (maze_.array [x + 1] [y] & mazeSquare::Outside) != mazeSquare::Outside) {
          maze_.array [x] [y] -= mazeSquare::Right;
          maze_.array [x + 1] [y] -= mazeSquare::Left;
          point = Point {x, y};
          return 1;
        }
        if (y < maze_.height - 1 // check DOWN
            && (maze_.array [x] [y + 1] & mazeSquare::Surrounded) != mazeSquare::Surrounded
            && (maze_.array [x] [y + 1] & mazeSquare::Outside) != mazeSquare::Outside) {
          maze_.array [x] [y] -= mazeSquare::Down;
          maze_.array [x] [y + 1] -= mazeSquare::Up;
          point = Point {x, y};
          return 1;
        }
        if (x > 0 // check LEFT
            && (maze_.array [x - 1] [y] & mazeSquare::Surrounded) != mazeSquare::Surrounded
            && (maze_.array [x - 1] [y] & mazeSquare::Outside) != mazeSquare::Outside) {
          maze_.array [x] [y] -= mazeSquare::Left;
          maze_.array [x - 1] [y] -= mazeSquare::Right;
          point = Point {x, y};
          return 1;
        }
      }
    }
  return 0;
}
