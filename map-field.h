#ifndef MAPFIELD_H
#define MAPFIELD_H

namespace mapField {
  namespace logic { enum {
      None = 0,
      BackPrintFlag   = 0b0001,
      GroundPrintFlag = 0b0010,
      BlockPrintFlag  = 0b0100,
      ExtraPrintFlag  = 0b1000,
      Obstacle = 0b0001 << 4,
      Entrance = 0b0010 << 4,
    }; }
  namespace color { enum color {
      NumVariations = 5,

      Dirt  = 0b0000,
      Grass = 0b0001,
      Sand  = 0b0010,
      Stone = 0b0011,
      Water = 0b0100,
    }; }
  namespace ground { enum ground {
      NumVariations = 1,

      Plain = 0b0000,
    }; }
  namespace block { enum block {
      NumVariations = 16,

      Quoin1  = 0b0000,
      Quoin2  = 0b0001,
      Quoin3  = 0b0010,
      Quoin4  = 0b0011,
      Wall1   = 0b0100,
      Wall2   = 0b0101,
      Wall3   = 0b0110,
      Wall4   = 0b0111,
      Corner1 = 0b1000,
      Corner2 = 0b1001,
      Corner3 = 0b1010,
      Corner4 = 0b1011,
      Stairs1 = 0b1100,
      Stairs2 = 0b1101,
      Stairs3 = 0b1110,
      Stairs4 = 0b1111,
    }; }
  namespace extra { enum extra {
      NumVariations = 6,

      Bush  = 0b0000,
      Bones = 0b0001,
      Fence = 0b0010,
      Rock1 = 0b0011,
      Rock2 = 0b0100,
      Rock3 = 0b0101,
    }; }
}

#endif // MAPFIELD_H
