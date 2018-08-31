#ifndef TEXTURES_H
#define TEXTURES_H

#include <QPixmap>
#include "map-field.h"

class Textures {

public:
  enum { Resolution = 16 };
  Textures ();
  ~Textures ();
  QPixmap backTexture (mapField::color::color color);
  QPixmap groundTexture (mapField::ground::ground ground, mapField::color::color color);
  QPixmap blockTexture (mapField::block::block block, mapField::color::color color);
  QPixmap extraTexture (mapField::extra::extra extra);

private:
  QPixmap **ground_textures_ = nullptr;
  QPixmap **block_textures_ = nullptr;
  QPixmap *extra_textures_ = nullptr;

};

#endif // TEXTURES_H
