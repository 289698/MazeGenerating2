#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QDebug>
#include <QPainter>

#include "textures.h"
#include "hunt-and-kill.h"

class GameMap {

public:
  GameMap (Textures *textures, int width, int height);
  ~GameMap ();
  QPixmap *background () { return background_; }
  QPixmap *walls () { return walls_; }
  inline int width () { return width_; }
  inline int height () { return height_; }
  //  void generateMaze (int maze_width, int maze_height, bool maze_border_flag,
  //                     int layer, int map_x, int map_y); // private? friends?
  void onGrid (int x, int y) { map_ [x] [y].tile = GameMap::tile::Floor; drawBackground (); drawWalls (); }
  void offGrid (int x, int y) { map_ [x] [y].tile = GameMap::tile::Wall; drawBackground (); drawWalls (); }

private:
  enum class tile { Null = -1, Floor, Wall };
  struct GameField {
    int logic;
    GameMap::tile tile;
  };
  void drawBackground ();
  void drawWalls ();
  void drawAdhereTile (QPainter *painter, Textures::tile type, int x, int y,
                       int drawing_x = 0, int drawing_y = 0);

  Textures *const textures_;
  QPixmap *background_ = nullptr, *walls_ = nullptr;
  GameField **map_ = nullptr;
  int width_;
  int height_;
};

#endif // GAMEMAP_H
