#ifndef GAMEMECHANICS_H
#define GAMEMECHANICS_H

#include "game-map.h"

class GameMechanics {

public:
  GameMechanics (Textures *textures, int width, int height);
  ~GameMechanics ();
  QPixmap *background () { return game_map_->background (); }
  QPixmap *walls () { return game_map_->walls (); }
  void onGrid (int x, int y) { game_map_->onGrid (x, y); }
  void offGrid (int x, int y) { game_map_->offGrid (x, y); }
  inline int mapWidth () { return game_map_->width (); } // sprawdzanie null, czy uznać, że zawsze będzie?
  inline int mapHeight () { return game_map_->height (); }

private:
  Textures *const textures_;
  GameMap *game_map_ = nullptr;
//  int num_levels_;

};

#endif // GAMEMECHANICS_H
