#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QDebug>
#include "map-field.h"
#include "hunt-and-kill.h"

class GameMap {

public:
  GameMap (int width, int height, const QString &name);
  ~GameMap ();
  inline int width () { return width_; }
  inline int height () { return height_; }
  bool groundPrintFlag (int x, int y);
  bool blockPrintFlag (int x, int y);
  bool extraPrintFlag (int x, int y);
  mapField::color::color backColor (int x, int y);
  mapField::color::color groundColor (int x, int y);
  mapField::color::color blockColor (int x, int y);
  mapField::ground::ground ground (int x, int y);
  mapField::block::block block (int x, int y);
  mapField::extra::extra extra (int x, int y);
  bool setGroundPrintFlag (bool value, int x, int y);
  bool setBlockPrintFlag (bool value, int x, int y);
  bool setExtraPrintFlag (bool value, int x, int y);
  bool setBackColor (mapField::color::color color, int x, int y);
  bool setGroundColor (mapField::color::color color, int x, int y);
  bool setBlockColor (mapField::color::color color, int x, int y);
  bool setGround (mapField::ground::ground ground, int x, int y);
  bool setBlock (mapField::block::block block, int x, int y);
  bool setExtra (mapField::extra::extra extra, int x, int y);
  //  void generateMaze (int maze_width, int maze_height, bool maze_border_flag,
  //                     int layer, int map_x, int map_y); // private? friends?

private:
  struct GameField {
    int logic;
    mapField::color::color back_color;
    mapField::color::color ground_color;
    mapField::color::color block_color;
    mapField::ground::ground ground;
    mapField::block::block block;
    mapField::extra::extra extra;
  };

  GameField **map_ = nullptr;
  int width_;
  int height_;
  QString name_;
};

#endif // GAMEMAP_H
