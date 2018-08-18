#include "maze.h"

Maze::~Maze () {

}

int Maze::at (int x, int y) {
  if (maze_.array == nullptr
      || x >= maze_.width || x < 0
      || y >= maze_.height || y < 0)
    return mazeSquare::Empty;
  return (maze_.array [x] [y] & mazeSquare::Surrounded);
}

void Maze::resetDistance (const Point &position) {
  newArray (distance_from_player_, maze_.width, maze_.height);
  resetArray (distance_from_player_, -1);
  floodFill (0, position.x, position.y);
}

int Maze::setEnd () {
  int distance = 0;
  resetDistance (start_);
  for (int x = 0; x < maze_.width; ++ x)
    for (int y = 0; y < maze_.height; ++ y)
      if (distance_from_player_.array [x] [y] > distance) {
        end_ = Point {x, y};
        distance = distance_from_player_.array [x] [y];
      }
  deleteArray (distance_from_player_);
  return distance;
}

void Maze::floodFill (int value, int x, int y) {
  distance_from_player_.array [x] [y] = value;
  if ( !(maze_.array [x] [y] & direction::Up)
       && distance_from_player_.array [x] [y - 1] == -1)
    floodFill (value + 1, x, y - 1);
  if ( !(maze_.array [x] [y] & direction::Right)
       && distance_from_player_.array [x + 1] [y] == -1)
    floodFill (value + 1, x + 1, y);
  if ( !(maze_.array [x] [y] & direction::Down)
       && distance_from_player_.array [x] [y + 1] == -1)
    floodFill (value + 1, x, y + 1);
  if ( !(maze_.array [x] [y] & direction::Left)
       && distance_from_player_.array [x - 1] [y] == -1)
    floodFill (value + 1, x - 1, y);
  return;
}

void Maze::newArray (IntArray &array, int width, int height) {
  if (array.array != nullptr)
    deleteArray (array);
  array.width = width;
  array.height = height;
  array.array = new int *[array.width];
  for (int x = 0; x < array.width; ++ x)
    array.array [x] = new int [array.height];
}

void Maze::resetArray (IntArray &array, int value) {
  if (array.array == nullptr)
    return;
  for (int x = 0; x < array.width; ++ x)
    for (int y = 0; y < array.height; ++ y)
      array.array [x] [y] = value;
}

void Maze::deleteArray (IntArray &array) {
  if (array.array == nullptr)
    return;
  for (int x = 0; x < array.width; ++ x)
    delete [] array.array [x];
  delete [] array.array;
  array.array = nullptr;
}
