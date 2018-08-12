#include "mazemap.h"

MazeMap::~MazeMap () {

}

int MazeMap::at (int x, int y) {
  if (maze_map_.array == nullptr
      || x >= maze_map_.width || x < 0
      || y >= maze_map_.height || y < 0)
    return square::kEmpty;
  return maze_map_.array [x] [y] & square::kSurrounded;
}

int MazeMap::backgroundAt (int x, int y) {
  if (maze_map_.array == nullptr
      || x >= maze_map_.width || x < 0
      || y >= maze_map_.height || y < 0)
    return 1;
  switch (maze_map_.array [x] [y] & (square::kOutside | square::kWater)) {
    case square::kEmpty:
      return 0;
    case square::kOutside:
      return 1;
    case square::kWater:
      return 2;
    case (square::kOutside | square::kWater):
      return 3;
    default:
      return 0;
  }
}

//int MazeMap::backgroundAt (int x, int y) {
//  if (maza_map.array ==  nullptr
//      || x >= maze_map_.width || x < 0
//      || y >= maze_map_.height || y < 0)
//}

void MazeMap::resetDistance (const Point &position) {
  newArray (distance_from_player_, maze_map_.width, maze_map_.height);
  resetArray (distance_from_player_, -1);
  floodFill (0, position.x, position.y);
}

int MazeMap::setEnd () {
  int distance = 0;
  resetDistance (start_);
  for (int x = 0; x < maze_map_.width; ++ x)
    for (int y = 0; y < maze_map_.height; ++ y)
      if (distance_from_player_.array [x] [y] > distance) {
        end_ = Point {x, y};
        distance = distance_from_player_.array [x] [y];
      }
  deleteArray (distance_from_player_);
  return distance;
}

void MazeMap::floodFill (int value, int x, int y) {
  distance_from_player_.array [x] [y] = value;
  if ( !(maze_map_.array [x] [y] & direction::kUp)
       && distance_from_player_.array [x] [y - 1] == -1)
    floodFill (value + 1, x, y - 1);
  if ( !(maze_map_.array [x] [y] & direction::kRight)
       && distance_from_player_.array [x + 1] [y] == -1)
    floodFill (value + 1, x + 1, y);
  if ( !(maze_map_.array [x] [y] & direction::kDown)
       && distance_from_player_.array [x] [y + 1] == -1)
    floodFill (value + 1, x, y + 1);
  if ( !(maze_map_.array [x] [y] & direction::kLeft)
       && distance_from_player_.array [x - 1] [y] == -1)
    floodFill (value + 1, x - 1, y);
  return;
}

void MazeMap::newArray (IntArray &array, int width, int height) {
  if (array.array != nullptr)
    deleteArray (array);
  array.width = width;
  array.height = height;
  array.array = new int *[array.width];
  for (int x = 0; x < array.width; ++x)
    array.array [x] = new int [array.height];
}

void MazeMap::resetArray (IntArray &array, int value) {
  if (array.array == nullptr)
    return;
  for (int x = 0; x < array.width; ++x)
    for (int y = 0; y < array.height; ++y)
      array.array [x] [y] = value;
}

void MazeMap::deleteArray (IntArray &array) {
  if (array.array == nullptr)
    return;
  for (int x = 0; x < array.width; ++x)
    delete [] array.array [x];
  delete [] array.array;
  array.array = nullptr;
}
