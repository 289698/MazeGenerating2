#include "game-map.h"

using namespace mapField;

GameMap::GameMap (int width, int height, const QString &name) :
  width_ (width), height_ (height), name_ (name) {
  map_ = new GameField *[width_];
  for (int x = 0; x < width_; ++ x) {
    map_ [x] = new GameField [height_];
    for (int y = 0; y < height_; ++ y)
      map_ [x] [y] = GameField {logic::None, color::Stone, color::Dirt, color::Grass,
                     ground::Plain, block::Quoin1, extra::Bush};
  }
//  for (int x = 0; x < 30; ++ x)
//    for (int y = 0; y < 30; ++ y)
//      this->setGroundPrintFlag (true, x, y);
//  for (int x = 20; x < 50; ++ x)
//    for (int y = 0; y < 30; ++ y)
//      this->setBlockPrintFlag (true, x, y);
//  for (int x = 10; x < 40; ++ x)
//    for (int y = 10; y < 40; ++ y)
//      this->setExtraPrintFlag (true, x, y);
//  generateMaze (10, 10, true, 0, 0, 1);
}

GameMap::~GameMap () {
  for (int x = 0; x < width_; ++ x)
    delete [] map_ [x];
  delete [] map_;
}

bool GameMap::groundPrintFlag (int x, int y) {
  if (x < 0 || x >= width_ || y < 0 || y >= height_) {
    qDebug () << "error GameMap 1";
    return false;
  }
  return ((map_ [x] [y].logic & logic::GroundPrintFlag) == logic::GroundPrintFlag);
}

bool GameMap::blockPrintFlag (int x, int y) {
  if (x < 0 || x >= width_ || y < 0 || y >= height_) {
    qDebug () << "error GameMap 2";
    return false;
  }
  return ((map_ [x] [y].logic & logic::BlockPrintFlag) == logic::BlockPrintFlag);
}

bool GameMap::extraPrintFlag (int x, int y) {
  if (x < 0 || x >= width_ || y < 0 || y >= height_) {
    qDebug () << "error GameMap 3";
    return false;
  }
  return ((map_ [x] [y].logic & logic::ExtraPrintFlag) == logic::ExtraPrintFlag);
}

color::color GameMap::backColor(int x, int y) {
  if (x < 0 || x >= width_ || y < 0 || y >= height_) {
    qDebug () << "error GameMap 4";
    return color::color::Dirt; // poprawić na shadow
  }
  return map_ [x] [y].back_color;
}

color::color GameMap::groundColor(int x, int y) {
  if (x < 0 || x >= width_ || y < 0 || y >= height_) {
    qDebug () << "error GameMap 5";
    return color::color::Dirt; // poprawić na shadow
  }
  return map_ [x] [y].ground_color;
}

color::color GameMap::blockColor(int x, int y) {
  if (x < 0 || x >= width_ || y < 0 || y >= height_) {
    qDebug () << "error GameMap 6";
    return color::color::Dirt; // poprawić na shadow
  }
  return map_ [x] [y].block_color;
}

ground::ground GameMap::ground(int x, int y) {
  if (x < 0 || x >= width_ || y < 0 || y >= height_) {
    qDebug () << "error GameMap 7";
    return ground::ground::Plain; // no co zrobisz
  }
  return map_ [x] [y].ground;
}

block::block GameMap::block(int x, int y) {
  if (x < 0 || x >= width_ || y < 0 || y >= height_) {
    qDebug () << "error GameMap 8";
    return block::block::Quoin1;
  }
  return map_ [x] [y].block;
}

extra::extra GameMap::extra(int x, int y) {
  if (x < 0 || x >= width_ || y < 0 || y >= height_) {
    qDebug () << "error GameMap 9";
    return extra::extra::Rock1;
  }
  return map_ [x] [y].extra;
}

bool GameMap::setGroundPrintFlag (bool value, int x, int y) {
  if (x < 0 || x >= width_ || y < 0 || y >= height_) {
    qDebug () << "error GameMap 10";
    return false;
  }
  map_ [x] [y].logic &= (~logic::GroundPrintFlag);
  map_ [x] [y].logic |= (logic::GroundPrintFlag * value);
  return true;
}

bool GameMap::setBlockPrintFlag (bool value, int x, int y) {
  if (x < 0 || x >= width_ || y < 0 || y >= height_) {
    qDebug () << "error GameMap 11";
    return false;
  }
  map_ [x] [y].logic &= (~logic::BlockPrintFlag);
  map_ [x] [y].logic |= (logic::BlockPrintFlag * value);
  return true;
}

bool GameMap::setExtraPrintFlag (bool value, int x, int y) {
  if (x < 0 || x >= width_ || y < 0 || y >= height_) {
    qDebug () << "error GameMap 12";
    return false;
  }
  map_ [x] [y].logic &= (~logic::ExtraPrintFlag);
  map_ [x] [y].logic |= (logic::ExtraPrintFlag * value);
  return true;
}

bool GameMap::setBackColor (color::color color, int x, int y) {
  if (x < 0 || x >= width_ || y < 0 || y >= height_) {
    qDebug () << "error GameMap 13";
    return false;
  }
  map_ [x] [y].back_color = color;
  return true;
}

bool GameMap::setGroundColor (color::color color, int x, int y) {
  if (x < 0 || x >= width_ || y < 0 || y >= height_) {
    qDebug () << "error GameMap 14";
    return false;
  }
  map_ [x] [y].ground_color = color;
  return true;
}

bool GameMap::setBlockColor (color::color color, int x, int y) {
  if (x < 0 || x >= width_ || y < 0 || y >= height_) {
    qDebug () << "error GameMap 15";
    return false;
  }
  map_ [x] [y].block_color = color;
  return true;
}

bool GameMap::setGround (ground::ground ground, int x, int y) {
  if (x < 0 || x >= width_ || y < 0 || y >= height_) {
    qDebug () << "error GameMap 16";
    return false;
  }
  map_ [x] [y].ground = ground;
  return true;
}

bool GameMap::setBlock (block::block block, int x, int y) {
  if (x < 0 || x >= width_ || y < 0 || y >= height_) {
    qDebug () << "error GameMap 17";
    return false;
  }
  map_ [x] [y].block = block;
  return true;
}

bool GameMap::setExtra (extra::extra extra, int x, int y) {
  if (x < 0 || x >= width_ || y < 0 || y >= height_) {
    qDebug () << "error GameMap 18";
    return false;
  }
  map_ [x] [y].extra = extra;
  return true;
}

//void GameMap::generateMaze (int maze_width, int maze_height, bool maze_border_flag,
//                            int layer, int map_x, int map_y) {
//  if (maze_width < 0 || maze_height < 0 || map_x < 0 || map_x >= width_ ||
//      map_y < 0 || map_y >= height_ || layer_index < 0 || layer_index >= num_layers_ ||
//      maze_width * 5 > (width_ - map_x) || maze_height * 5 > (height_ - map_y))
//    return;
//  HuntAndKill *maze = new HuntAndKill (maze_width, maze_height, Point {2, 2}, maze_border_flag);
//  /*! resetowanie odpowiednich bitów w zadanej części mapy i warstwie
//   * na 0 za pomocą bitwise NOR*/
//  for (int i = 0; i < maze->width () * 5; ++ i)
//    for (int j = 0; j < maze->height () * 5; ++ j)
//      map_ [map_x + i] [map_y + j] &=
//          ~((block::Bits | logic::blockPrintFlag) << (layer::Offset * layer_index));

//  /*! (x, y) to punkt w maze, (map_x, map_y) to punkt w map_
//   * przy iteracji y zwiększam y o 1 i pozycję y w map_ (map_y) o 5
//   * przy iteracji x zwiększam x o 1 i zmniejszam map_y do wyjściowej wartości */
//  for (int x = 0; x < maze->width (); ++ x, map_x += 5, map_y -= maze->height () * 5)
//    for (int y = 0; y < maze->height (); ++ y, map_y += 5) {
//      int current_maze_square = maze->at (x, y);

//      /*! ustawianie odpowiednich wartości na bokach fragmentu mapy sumą binarną wartości pola mapy
//       * z odpowiedną wartością klocka*/
//      //! górny bok
//      if ((current_maze_square & mazeSquare::Up) == mazeSquare::Up)
//        for (int i = 1; i < 4; ++ i)
//          map_ [map_x + i] [map_y] |=
//              ((block::Wall1 | logic::blockPrintFlag) << (layer::Offset * layer_index));
//      //! prawy bok
//      if ((current_maze_square & mazeSquare::Right) == mazeSquare::Right)
//        for (int i = 1; i < 4; ++ i)
//          map_ [map_x + 4] [map_y + i] |=
//              ((block::Wall2 | logic::blockPrintFlag) << (layer::Offset * layer_index));
//      //! dolny bok
//      if ((current_maze_square & mazeSquare::Down) == mazeSquare::Down)
//        for (int i = 1; i < 4; ++ i)
//          map_ [map_x + i] [map_y + 4] |=
//              ((block::Wall3 | logic::blockPrintFlag) << (layer::Offset * layer_index));
//      //! lewy bok
//      if ((current_maze_square & mazeSquare::Left) == mazeSquare::Left)
//        for (int i = 1; i < 4; ++ i)
//          map_ [map_x] [map_y + i] |=
//              ((block::Wall4 | logic::blockPrintFlag) << (layer::Offset * layer_index));

//      /*! ustawianie odpowiednich węgłów i kątów sumą binarną jw.; gdy brak rogu - albo pusta
//       * przestrzeń, albo węgieł (wtedy, gdy sąsiednie komórki labiryntu są odpowiednie)*/
//      //! górny-prawy róg
//      switch (current_maze_square & (mazeSquare::Up | mazeSquare::Right)) {
//        case mazeSquare::Empty:
//          if ((maze->at (x + 1, y) & mazeSquare::Up) == mazeSquare::Up ||
//              (maze->at (x, y - 1) & mazeSquare::Right) == mazeSquare::Right)
//            map_ [map_x + 4] [map_y] |=
//                ((block::Quoin3 | logic::blockPrintFlag) << (layer::Offset * layer_index));
//          break;
//        case mazeSquare::Up:
//          map_ [map_x + 4] [map_y] |=
//              ((block::Wall1 | logic::blockPrintFlag) << (layer::Offset * layer_index));
//          break;
//        case mazeSquare::Right:
//          map_ [map_x + 4] [map_y] |=
//              ((block::Wall2 | logic::blockPrintFlag) << (layer::Offset * layer_index));
//          break;
//        case (mazeSquare::Up | mazeSquare::Right):
//          map_ [map_x + 4] [map_y] |=
//              ((block::Corner1 | logic::blockPrintFlag) << (layer::Offset * layer_index));
//          break;
//      }//! prawy-dolny róg
//      switch (current_maze_square & (mazeSquare::Right | mazeSquare::Down)) {
//        case mazeSquare::Empty:
//          if ((maze->at (x, y + 1) & mazeSquare::Right) == mazeSquare::Right ||
//              (maze->at (x + 1, y) & mazeSquare::Down) == mazeSquare::Down)
//            map_ [map_x + 4] [map_y + 4] |=
//                ((block::Quoin4 | logic::blockPrintFlag) << (layer::Offset * layer_index));
//          break;
//        case mazeSquare::Right:
//          map_ [map_x + 4] [map_y + 4] |=
//              ((block::Wall2 | logic::blockPrintFlag) << (layer::Offset * layer_index));
//          break;
//        case mazeSquare::Down:
//          map_ [map_x + 4] [map_y + 4] |=
//              ((block::Wall3 | logic::blockPrintFlag) << (layer::Offset * layer_index));
//          break;
//        case (mazeSquare::Right | mazeSquare::Down):
//          map_ [map_x + 4] [map_y + 4] |=
//              ((block::Corner2 | logic::blockPrintFlag) << (layer::Offset * layer_index));
//          break;
//      }//! dolny-lewy róg
//      switch (current_maze_square & (mazeSquare::Down | mazeSquare::Left)) {
//        case mazeSquare::Empty:
//          if ((maze->at (x - 1, y) & mazeSquare::Down) == mazeSquare::Down ||
//              (maze->at (x, y + 1) & mazeSquare::Left) == mazeSquare::Left)
//            map_ [map_x] [map_y + 4] |=
//                ((block::Quoin1 | logic::blockPrintFlag) << (layer::Offset * layer_index));
//          break;
//        case mazeSquare::Down:
//          map_ [map_x] [map_y + 4] |=
//              ((block::Wall3 | logic::blockPrintFlag) << (layer::Offset * layer_index));
//          break;
//        case mazeSquare::Left:
//          map_ [map_x] [map_y + 4] |=
//              ((block::Wall4 | logic::blockPrintFlag) << (layer::Offset * layer_index));
//          break;
//        case (mazeSquare::Down | mazeSquare::Left):
//          map_ [map_x] [map_y + 4] |=
//              ((block::Corner3 | logic::blockPrintFlag) << (layer::Offset * layer_index));
//          break;
//      }//! lewy-górny róg
//      switch (current_maze_square & (mazeSquare::Left | mazeSquare::Up)) {
//        case mazeSquare::Empty:
//          if ((maze->at (x, y - 1) & mazeSquare::Left) == mazeSquare::Left ||
//              (maze->at (x - 1, y) & mazeSquare::Up) == mazeSquare::Up)
//            map_ [map_x] [map_y] |=
//                ((block::Quoin2 | logic::blockPrintFlag) << (layer::Offset * layer_index));
//          break;
//        case mazeSquare::Left:
//          map_ [map_x] [map_y] |=
//              ((block::Wall4 | logic::blockPrintFlag) << (layer::Offset * layer_index));
//          break;
//        case mazeSquare::Up:
//          map_ [map_x] [map_y] |=
//              ((block::Wall1 | logic::blockPrintFlag) << (layer::Offset * layer_index));
//          break;
//        case (mazeSquare::Left | mazeSquare::Up):
//          map_ [map_x] [map_y] |=
//              ((block::Corner4 | logic::blockPrintFlag) << (layer::Offset * layer_index));
//          break;
//      }
//    }
//  delete maze;
//}
