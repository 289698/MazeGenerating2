namespace gameField {
  namespace logic { enum {
      Offset = 0,
      Bits = 0b1111 << Offset,

      Obstacle = 0b0001 << Offset,
      Transparent = 0b0010 << Offset,
    }; }
  namespace ground {
    enum {
      Offset = 8,
      Bits  = 0b1111 << Offset,

      Dirt  = 0b0000 << Offset,
      Grass = 0b0001 << Offset,
      Sand  = 0b0010 << Offset,
      Stone = 0b0011 << Offset,
      Water = 0b0100 << Offset,
    };
  }
  namespace brick {
    enum {
      Offset = 16,
      Bits    = 0b11111111 << Offset,
      Pattern     = 0b1111 << Offset,
      Colour   = 0b1111 << (Offset + 4),

      Shape1 = 0b0000 << Offset,
      Shape2 = 0b0001 << Offset,
      Shape3 = 0b0010 << Offset,
      Shape4 = 0b0011 << Offset,
      Quoin  = 0b0000 << Offset,
      Wall   = 0b0100 << Offset,
      Corner = 0b1000 << Offset,
      Stairs = 0b1100 << Offset,

      Dirt  = 0b0000 << (Offset + 4),
      Grass = 0b0001 << (Offset + 4),
      Sand  = 0b0010 << (Offset + 4),
      Stone = 0b0011 << (Offset + 4),
      Water = 0b0100 << (Offset + 4),
    };
  }
  namespace item {
    enum {

    };
  }
}
