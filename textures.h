#ifndef TEXTURES_H
#define TEXTURES_H

#include <QPixmap>

class Textures {

public:
  enum { FullRes = 64, HalfRes = FullRes / 2 };
  enum class theme { Dungeon };
  enum class tile { Floor, Celling };
  enum class squareTile { Quoin1, Quoin2, Quoin3, Quoin4, BarH1, BarH2, BarH3, BarH4,
                          BarV1, BarV2, BarV3, BarV4, Corner1, Corner2, Corner3, Corner4, Tile };
  Textures ();
  ~Textures ();
  QPixmap squareTileTex (tile type, squareTile index);

private:
  QPixmap *loadSquareTiles (const QString &path);
  QPixmap **square_tiles_;

};

#endif // TEXTURES_H
