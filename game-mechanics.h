#ifndef GAMEMECHANICS_H
#define GAMEMECHANICS_H

//#include <QObject>
#include "game-map.h"

class GameMechanics/* : public QObject*/ {
//  Q_OBJECT

public:
  /*explicit */GameMechanics (/*QObject *parent = 0*/);
  ~GameMechanics ();
  inline int mapWidth () { return game_map_->width (); } // sprawdzanie null, czy uznać, że zawsze będzie?
  inline int mapHeight () { return game_map_->height (); }
  inline int mapNumLayers () { return game_map_->numLayers (); }
  bool printFlagBrick (int x, int y, int layer);
  int blockIndex (int x, int y, int layer);
  int colorIndex (int x, int y, int layer);

private:
  GameMap *game_map_ = nullptr;
  /*! przerysowuje zadany labirynt na zadaną mapę gry, zanczynając od offset_x, offset_y
   * zmienia tylko gameField::brick::Pattern, ::Colour zostawia niezmieniony */
};

#endif // GAMEMECHANICS_H
