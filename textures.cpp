#include "textures.h"

Textures::Textures () {
  square_tiles_ = new QPixmap *[2];
  square_tiles_ [0] = loadSquareTiles (":/textures/Dungeon/Floor.png");
  square_tiles_ [1] = loadSquareTiles (":/textures/Dungeon/Celling.png");
}

Textures::~Textures () {
  for (int i = 0; i < 2; ++ i)
    delete [] square_tiles_ [i];
  delete [] square_tiles_;
}

QPixmap Textures::squareTileTex (Textures::tile type, Textures::squareTile index) {
  return square_tiles_ [static_cast <int> (type)] [static_cast <int> (index)];
}

QPixmap *Textures::loadSquareTiles(const QString &path) {
  QPixmap *tiles = new QPixmap [17];
  QPixmap *texturesAtlas = new QPixmap (path);

  tiles [0] = texturesAtlas->copy (HalfRes * 5, HalfRes * 0, HalfRes, HalfRes);
  tiles [1] = texturesAtlas->copy (HalfRes * 6, HalfRes * 0, HalfRes, HalfRes);
  tiles [2] = texturesAtlas->copy (HalfRes * 2, HalfRes * 1, HalfRes, HalfRes);
  tiles [3] = texturesAtlas->copy (HalfRes * 1, HalfRes * 1, HalfRes, HalfRes);

  tiles [4] = texturesAtlas->copy (HalfRes * 1, HalfRes * 0, HalfRes, HalfRes);
  tiles [5] = texturesAtlas->copy (HalfRes * 2, HalfRes * 0, HalfRes, HalfRes);
  tiles [6] = texturesAtlas->copy (HalfRes * 6, HalfRes * 1, HalfRes, HalfRes);
  tiles [7] = texturesAtlas->copy (HalfRes * 5, HalfRes * 1, HalfRes, HalfRes);

  tiles [8] = texturesAtlas->copy (HalfRes * 7, HalfRes * 0, HalfRes, HalfRes);
  tiles [9] = texturesAtlas->copy (HalfRes * 4, HalfRes * 0, HalfRes, HalfRes);
  tiles [10] = texturesAtlas->copy (HalfRes * 0, HalfRes * 1, HalfRes, HalfRes);
  tiles [11] = texturesAtlas->copy (HalfRes * 3, HalfRes * 1, HalfRes, HalfRes);

  tiles [12] = texturesAtlas->copy (HalfRes * 3, HalfRes * 0, HalfRes, HalfRes);
  tiles [13] = texturesAtlas->copy (HalfRes * 0, HalfRes * 0, HalfRes, HalfRes);
  tiles [14] = texturesAtlas->copy (HalfRes * 4, HalfRes * 1, HalfRes, HalfRes);
  tiles [15] = texturesAtlas->copy (HalfRes * 7, HalfRes * 1, HalfRes, HalfRes);

  tiles [16] = texturesAtlas->copy (FullRes * 4, 0, FullRes, FullRes);

  delete texturesAtlas;

  return tiles;
}
