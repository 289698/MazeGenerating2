#ifndef GAMEMECHANICS_H
#define GAMEMECHANICS_H

#include "game-map.h"

class GameMechanics {

public:
  GameMechanics (int height, int width, const QString &name);
  ~GameMechanics ();
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

private:
  GameMap *game_map_ = nullptr;
//  int num_levels_;

};

#endif // GAMEMECHANICS_H
