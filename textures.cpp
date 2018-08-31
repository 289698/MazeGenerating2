#include "textures.h"

Textures::Textures () {
  //! rezerwowanie miejsca na tekstury
  ground_textures_ = new QPixmap *[mapField::ground::NumVariations];
  for (int i = 0; i < mapField::ground::NumVariations; ++ i)
    ground_textures_ [i] = new QPixmap [mapField::color::NumVariations];
  block_textures_ = new QPixmap *[mapField::block::NumVariations];
  for (int i = 0; i < mapField::block::NumVariations; ++ i)
    block_textures_ [i] = new QPixmap [mapField::color::NumVariations];
  extra_textures_ = new QPixmap [mapField::extra::NumVariations];

  //! tymczasowe obiekty QPixmap do wczytania z plików
  QPixmap *ground_full = new QPixmap (":/textures/grounds.png");
  for (int y = 0; y < mapField::color::NumVariations; ++ y)
    for (int x = 0; x < mapField::ground::NumVariations; ++ x)
      ground_textures_ [x] [y] = ground_full->copy (x * Resolution, y * Resolution,
                                                    Resolution, Resolution);
  delete ground_full;
  QPixmap *block_full = new QPixmap (":/textures/blocks.png");
  for (int y = 0; y < mapField::color::NumVariations; ++ y)
    for (int x = 0; x < mapField::block::NumVariations; ++ x)
      block_textures_ [x] [y] = block_full->copy (x * Resolution, y * Resolution,
                                                  Resolution, Resolution);
  delete block_full;
  QPixmap *extra_full = new QPixmap (":/textures/extras.png");
  for (int i = 0; i < mapField::extra::NumVariations; ++ i)
    extra_textures_ [i] = extra_full->copy (i * Resolution, 0,
                                            Resolution, Resolution);
  delete extra_full;
}

Textures::~Textures () {
  if (ground_textures_ != nullptr) {
    for (int i = 0; i < mapField::ground::NumVariations; ++ i)
      delete [] ground_textures_ [i];
    delete [] ground_textures_;
  }
  if (block_textures_ != nullptr) {
    for (int i = 0; i < mapField::block::NumVariations; ++ i)
      delete [] block_textures_ [i];
    delete [] block_textures_;
  }
  if (extra_textures_ != nullptr)
    delete [] extra_textures_;
}

QPixmap Textures::backTexture (mapField::color::color color) {
  return ground_textures_ [0] [color];
}

QPixmap Textures::groundTexture (mapField::ground::ground ground, mapField::color::color color) {
  return ground_textures_ [ground] [color];
}

QPixmap Textures::blockTexture (mapField::block::block block, mapField::color::color color) {
  return block_textures_ [block] [color];
}

QPixmap Textures::extraTexture (mapField::extra::extra extra) {
  return extra_textures_ [extra];
}
