#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "hunt-and-kill.h"

namespace gameField {
  enum {
    Empty = 0b0,
  };
  namespace layer { enum {
      Offset = 16,
      Bits = 0b1111111111111111,
    }; }
  namespace logic { enum {
      Offset = 0,
      Bits = 0b1111 << Offset,

      Obstacle = 0b0001 << Offset,
      blockPrintFlag = 0b0100 << Offset,
      extraPrintFlag = 0b1000 << Offset,
    }; }
  namespace colour { enum {
      NumVariations = 5,
      Offset = 4,
      Bits = 0b1111 << Offset,

      Dirt  = 0b0000 << Offset,
      Grass = 0b0001 << Offset,
      Sand  = 0b0010 << Offset,
      Stone = 0b0011 << Offset,
      Water = 0b0100 << Offset,
    }; }
  namespace block { enum {
      NumVariations = 17,
      Offset = 8,
      Bits = 0b11111111 << Offset,

      Quoin1  = 0b00000 << Offset,
      Quoin2  = 0b00001 << Offset,
      Quoin3  = 0b00010 << Offset,
      Quoin4  = 0b00011 << Offset,
      Wall1   = 0b00100 << Offset,
      Wall2   = 0b00101 << Offset,
      Wall3   = 0b00110 << Offset,
      Wall4   = 0b00111 << Offset,
      Corner1 = 0b01000 << Offset,
      Corner2 = 0b01001 << Offset,
      Corner3 = 0b01010 << Offset,
      Corner4 = 0b01011 << Offset,
      Stairs1 = 0b01100 << Offset,
      Stairs2 = 0b01101 << Offset,
      Stairs3 = 0b01110 << Offset,
      Stairs4 = 0b01111 << Offset,
      Ground  = 0b10000 << Offset,
    }; }
  namespace extra { enum {
      NumVariations = 0,
      Offset = 16,
      Bits = 0b1111 << Offset,

      Bush  = 0b0000 << Offset,
      Bones = 0b0001 << Offset,
      Fence = 0b0010 << Offset,
      Rock1 = 0b0011 << Offset,
      Rock2 = 0b0100 << Offset,
      Rock3 = 0b0101 << Offset,
    }; }
}

class GameMap {

public:
  GameMap (int width, int height, int num_layers);
  ~GameMap ();
  inline int width () { return width_; }
  inline int height () { return height_; }
  inline int numLayers () { return num_layers_; }
  bool printFlagBrick (int x, int y, int layer);
  int colorIndex (int x, int y, int layer);
  int blockIndex (int x, int y, int layer);
  void generateMaze (int maze_width, int maze_height, bool maze_border_flag,
                     int map_x, int map_y, int layer); // private? friends?

private:
  int **map_ = nullptr;
  int width_;
  int height_;
  int num_layers_;
};

#endif // GAMEMAP_H
