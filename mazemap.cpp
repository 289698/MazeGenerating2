#include "mazemap.h"

int MazeMap::at (int x, int y) {
  if (maze_map_.array == nullptr || x >= maze_map_.width || x < 0 || y >= maze_map_.height || y < 0)
    return square::kUnvalid;
  return maze_map_.array [x] [y];
}

//inline Point operator + (Point lhs, const Point &rhs) {
//  lhs.x += rhs.x;
//  lhs.y += rhs.y;
//  return lhs;
//}

//inline Point operator - (Point lhs, const Point &rhs) {
//  lhs.x -= rhs.x;
//  lhs.y -= rhs.y;
//  return lhs;
//}

void MazeMap::newArray (IntArray &pointer, int width, int height) {
  if (pointer.array != nullptr)
    deleteArray (pointer);
  pointer.width = width;
  pointer.height = height;
  pointer.array = new int *[pointer.width];
  for (int x = 0; x < pointer.width; ++x)
    pointer.array [x] = new int [pointer.height];
}

void MazeMap::resetArray (IntArray &pointer, int value) {
  if (pointer.array == nullptr)
    return;
  for (int x = 0; x < pointer.width; ++x)
    for (int y = 0; y < pointer.height; ++y)
      pointer.array [x] [y] = value;
}

void MazeMap::deleteArray (IntArray &pointer) {
  if (pointer.array == nullptr)
    return;
  for (int x = 0; x < pointer.width; ++x)
    delete [] pointer.array [x];
  delete [] pointer.array;
  pointer.array = nullptr;
}
