#ifndef CREATORMECHANICS_H
#define CREATORMECHANICS_H

#include "game-map.h"

class CreatorMechanics {

public:
  CreatorMechanics (int height, int width, const QString &name);
  ~CreatorMechanics ();
  inline int mapWidth () { return game_map_->width (); } // sprawdzanie null, czy uznać, że zawsze będzie?
  inline int mapHeight () { return game_map_->height (); }
  bool groundPrintFlag (int x, int y) { return game_map_->groundPrintFlag (x, y); }
  bool blockPrintFlag (int x, int y) { return game_map_->blockPrintFlag (x, y); }
  bool extraPrintFlag (int x, int y) { return game_map_->extraPrintFlag (x, y); }
  mapField::color::color backColor (int x, int y) { return game_map_->backColor (x, y); }
  mapField::color::color groundColor (int x, int y) { return game_map_->groundColor (x, y); }
  mapField::color::color blockColor (int x, int y) { return game_map_->blockColor (x, y); }
  mapField::ground::ground ground (int x, int y) { return game_map_->ground (x, y); }
  mapField::block::block block (int x, int y) { return game_map_->block (x, y); }
  mapField::extra::extra extra (int x, int y) { return game_map_->extra (x, y); }
  bool setGroundPrintFlag (bool value, int x, int y)
  { return game_map_->setGroundPrintFlag (value, x, y); }
  bool setBlockPrintFlag (bool value, int x, int y)
  { return game_map_->setBlockPrintFlag (value, x, y); }
  bool setExtraPrintFlag (bool value, int x, int y)
  { return game_map_->setExtraPrintFlag (value, x, y); }
  bool setBackColor (mapField::color::color color, int x, int y)
  { return game_map_->setBackColor (color, x, y); }
  bool setGroundColor (mapField::color::color color, int x, int y)
  { return game_map_->setGroundColor (color, x, y); }
  bool setBlockColor (mapField::color::color color, int x, int y)
  { return game_map_->setBlockColor (color, x, y); }
  bool setGround (mapField::ground::ground ground, int x, int y)
  { return game_map_->setGround (ground, x, y); }
  bool setBlock (mapField::block::block block, int x, int y)
  { return game_map_->setBlock (block, x, y); }
  bool setExtra (mapField::extra::extra extra, int x, int y)
  { return game_map_->setExtra (extra, x, y); }

private:
  GameMap *game_map_ = nullptr;

};

#endif // CREATORMECHANICS_H
