#ifndef MAZEMAP_H
#define MAZEMAP_H

#include <QDebug>

namespace square {
  static const int
  kEmpty      = 0b0000,
  kUp         = 0b0001,
  kRight      = 0b0010,
  kDown       = 0b0100,
  kLeft       = 0b1000,
  kSurrounded = 0b1111,

  kOutside    = 0b00010000,
  kSolid      = 0b00100000,
  kWater      = 0b01000000,
  kVisited    = 0b10000000;
} namespace direction = square;

struct Point {
  int x;
  int y;
  inline Point& operator += (const Point &rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
  }
  inline Point operator + (const Point &rhs) {
    return Point {x + rhs.x, y + rhs.y};
  }
  inline Point& operator -= (const Point &rhs) {
    this->x -= rhs.x;
    this->y -= rhs.y;
    return *this;
  }
  inline Point operator - (const Point &rhs) {
    return Point {x - rhs.x, y - rhs.y};
  }
  inline Point operator = (const Point &rhs) {
    this->x = rhs.x;
    this->y = rhs.y;
    return *this;
  }
  inline Point operator / (const int &rhs) {
    return Point {this->x / rhs, this->y / rhs};
  }
  inline bool operator == (const Point &rhs) {
    if (this->x == rhs.x && this->y == rhs.y)
      return 1;
    return 0;
  }
};  typedef Point Size;

struct IntArray {
  int width;
  int height;
  int **array;
  //inline int *&operator [] (int i) { return array [i]; }
};

class MazeMap {
public:  
  virtual ~MazeMap ();
  inline int distanceFromPlayer (int x, int y) const
  { return distance_from_player_.array [x] [y]; }
  inline Size mazeSize () const { return Size {maze_map_.width, maze_map_.height}; }
  inline int mazeWidth () const { return maze_map_.width; }
  inline int mazeHeight () const { return maze_map_.height; }
  inline Point startPoint () const { return start_; }
  inline int startX () const { return start_.x; }
  inline int startY () const { return start_.y; }
  inline Point endPoint () const { return end_; }
  inline int endX () const { return end_.x; }
  inline int endY () const { return end_.y; }
  int setEnd ();

  int at (int x, int y);
  int at (Point position) { return at (position.x, position.y); }
  int backgroundAt (int x, int y);
  int backgroundAt (Point position) { return backgroundAt (position.x, position.y); }
  void resetDistance (const Point &position);

protected:
  IntArray maze_map_ {0, 0, nullptr};
  IntArray distance_from_player_ {0, 0, nullptr};
  Point start_ {0, 0};
  Point end_ {0, 0};

  void newArray (IntArray &array, int width, int height);
  void resetArray (IntArray &array, int value);
  void deleteArray (IntArray &array);

private:
  void floodFill (int value, int x, int y);

};

#endif // MAZEMAP_H
