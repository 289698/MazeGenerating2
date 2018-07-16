#ifndef MAZEMAP_H
#define MAZEMAP_H

#include <QDebug>

namespace square {
  static const int
  kEmpty         = 0,  // 0000
  kUp            = 1,  // 0001
  kRight         = 2,  // 0010
//  kUpRight       = 3,  // 0011
  kDown          = 4,  // 0100
//  kUpDown        = 5,  // 0101
//  kRightDown     = 6,  // 0110
//  kUpRightDown   = 7,  // 0111
  kLeft          = 8,  // 1000
//  kUpLeft        = 9,  // 1001
//  kRightLeft     = 10, // 1010
//  kUpRightLeft   = 11, // 1011
//  kDownLeft      = 12, // 1100
//  kUpDownLeft    = 13, // 1101
//  kRightDownLeft = 14, // 1110
  kUnvalid       = 15; // 1111
} namespace direction = square;

struct Point {
  int x;
  int y;
  inline Point& operator += (const Point &rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
  }
  inline Point& operator -= (const Point &rhs) {
    this->x -= rhs.x;
    this->y -= rhs.y;
    return *this;
  }
  inline bool operator == (const Point &rhs) {
    if (this->x == rhs.x && this->y == rhs.y)
      return 1;
    return 0;
  }
}; // typedef Point Size;

struct IntArray {
  int width;
  int height;
  int **array;
  //inline int *&operator [] (int i) { return array [i]; }
};

class MazeMap {
public:
  int at (int x, int y);

  inline int mazeWidth () {
    return maze_map_.width;
  }
  inline int mazeHeight () {
    return maze_map_.height;
  }
  inline int startX () {
    return start_.x;
  }
  inline int startY () {
    return start_.y;
  }
  inline Point startPoint () {
    return start_;
  }
  inline int endX () {
    return end_.x;
  }
  inline int endY () {
    return end_.y;
  }
  inline Point endPoint () {
    return end_;
  }

  void newArray (IntArray &pointer, int width, int height);
  void resetArray (IntArray &pointer, int value);
  void deleteArray (IntArray &pointer);

protected:
  IntArray maze_map_ {0, 0, nullptr};
  Point start_ {4, 2};
  Point end_ {5, 5};

};

#endif // MAZEMAP_H
