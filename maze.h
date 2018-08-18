#ifndef MAZEMAP_H
#define MAZEMAP_H

#include <iostream>
#include <QDebug>

namespace mazeSquare {
  enum {
    Empty      = 0,
    Up         = 0b0001,
    Right      = 0b0010,
    Down       = 0b0100,
    Left       = 0b1000,
    Surrounded = 0b1111,
    Outside    = 0b1 << 5
  };
}
namespace direction {
  enum {
    Empty = 0,
    Up    = 0b0001,
    Right = 0b0010,
    Down  = 0b0100,
    Left  = 0b1000
  };
}

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
};

struct IntArray {
  int width;
  int height;
  int **array;
  //inline int *&operator [] (int i) { return array [i]; }
};

class Maze {
public:

  virtual ~Maze ();
  inline int distanceFromPlayer (int x, int y) const
  { return distance_from_player_.array [x] [y]; }
  inline int width () const { return maze_.width; }
  inline int height () const { return maze_.height; }
  inline Point startPoint () const { return start_; }
  inline int startX () const { return start_.x; }
  inline int startY () const { return start_.y; }
  inline Point endPoint () const { return end_; }
  inline int endX () const { return end_.x; }
  inline int endY () const { return end_.y; }

  int setEnd ();
  int at (int x, int y);
  int at (Point position) { return at (position.x, position.y); }

protected:
  IntArray maze_ {0, 0, nullptr};
  IntArray distance_from_player_ {0, 0, nullptr};
  Point start_ {0, 0};
  Point end_ {0, 0};

  void newArray (IntArray &array, int width, int height);
  void resetArray (IntArray &array, int value);
  void deleteArray (IntArray &array);

private:
  void floodFill (int value, int x, int y);
  void resetDistance (const Point &position);

};

#endif // MAZEMAP_H
