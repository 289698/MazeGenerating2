#include "game-map.h"

GameMap::GameMap (Textures *textures, int width, int height) :
  textures_ (textures), width_ (width), height_ (height) {
  map_ = new GameField *[width_];


  for (int x = 0; x < width_; ++ x) {
    map_ [x] = new GameField [height_];
    for (int y = 0; y < height_; ++ y)
      map_ [x] [y].tile = GameMap::tile::Wall;
  }
  for (int x = 1; x < width_ - 1; ++ x) {
    for (int y = 1; y < height_ - 1; ++ y)
      map_ [x] [y].tile = GameMap::tile::Floor;
  }

  drawBackground ();
  drawWalls ();
}

GameMap::~GameMap () {
  for (int x = 0; x < width_; ++ x)
    delete [] map_ [x];
  delete [] map_;
  if (background_ != nullptr)
    delete background_;
}

void GameMap::drawAdhereTile (QPainter *painter, Textures::tile type, int x, int y,
                              int drawing_x, int drawing_y) {
  painter->drawPixmap (drawing_x, drawing_y,
                       textures_->squareTileTex (type, Textures::squareTile::Tile));

  int adjacent_tiles = 0;
  if (y > 0 && map_ [x] [y - 1].tile != map_ [x] [y].tile)
    adjacent_tiles += 0b0001;
  if (x > 0 && map_ [x - 1] [y].tile != map_ [x] [y].tile)
    adjacent_tiles += 0b0010;
  if (y < (height_ - 1) && map_ [x] [y + 1].tile != map_ [x] [y].tile)
    adjacent_tiles += 0b0100;
  if (x < (width_ -1) && map_ [x + 1] [y].tile != map_ [x] [y].tile)
    adjacent_tiles += 0b1000;

  switch (adjacent_tiles & 0b1001) {
  case 0b0000:
    if (x < (width_ - 1) && y > 0 && map_ [x + 1] [y - 1].tile != map_ [x] [y].tile)
      painter->drawPixmap (drawing_x + Textures::HalfRes, drawing_y,
                           textures_->squareTileTex (type, Textures::squareTile::Quoin1));
    break;
  case 0b0001:
    painter->drawPixmap (drawing_x + Textures::HalfRes, drawing_y,
                         textures_->squareTileTex (type, Textures::squareTile::BarH1));
    break;
  case 0b1000:
    painter->drawPixmap (drawing_x + Textures::HalfRes, drawing_y,
                         textures_->squareTileTex (type, Textures::squareTile::BarV1));
    break;
  case 0b1001:
    painter->drawPixmap (drawing_x + Textures::HalfRes, drawing_y,
                         textures_->squareTileTex (type, Textures::squareTile::Corner1));
    break;
  }
  switch (adjacent_tiles & 0b0011) {
  case 0b0000:
    if (x > 0 && y > 0 && map_ [x - 1] [y - 1].tile != map_ [x] [y].tile)
      painter->drawPixmap (drawing_x, drawing_y,
                           textures_->squareTileTex (type, Textures::squareTile::Quoin2));
    break;
  case 0b0001:
    painter->drawPixmap (drawing_x, drawing_y,
                         textures_->squareTileTex (type, Textures::squareTile::BarH2));
    break;
  case 0b0010:
    painter->drawPixmap (drawing_x, drawing_y,
                         textures_->squareTileTex (type, Textures::squareTile::BarV2));
    break;
  case 0b0011:
    painter->drawPixmap (drawing_x, drawing_y,
                         textures_->squareTileTex (type, Textures::squareTile::Corner2));
    break;
  }
  switch (adjacent_tiles & 0b0110) {
  case 0b0000:
    if (x > 0 && y < (height_ - 1) && map_ [x - 1] [y + 1].tile != map_ [x] [y].tile)
      painter->drawPixmap (drawing_x, drawing_y + Textures::HalfRes,
                           textures_->squareTileTex (type, Textures::squareTile::Quoin3));
    break;
  case 0b0100:
    painter->drawPixmap (drawing_x, drawing_y + Textures::HalfRes,
                         textures_->squareTileTex (type, Textures::squareTile::BarH3));
    break;
  case 0b0010:
    painter->drawPixmap (drawing_x, drawing_y + Textures::HalfRes,
                         textures_->squareTileTex (type, Textures::squareTile::BarV3));
    break;
  case 0b0110:
    painter->drawPixmap (drawing_x, drawing_y + Textures::HalfRes,
                         textures_->squareTileTex (type, Textures::squareTile::Corner3));
    break;
  }
  switch (adjacent_tiles & 0b1100) {
  case 0b0000:
    if (x < (width_ - 1) && y < (height_ - 1) && map_ [x + 1] [y + 1].tile != map_ [x] [y].tile)
      painter->drawPixmap (drawing_x + Textures::HalfRes, drawing_y + Textures::HalfRes,
                           textures_->squareTileTex (type, Textures::squareTile::Quoin4));
    break;
  case 0b0100:
    painter->drawPixmap (drawing_x + Textures::HalfRes, drawing_y + Textures::HalfRes,
                         textures_->squareTileTex (type, Textures::squareTile::BarH4));
    break;
  case 0b1000:
    painter->drawPixmap (drawing_x + Textures::HalfRes, drawing_y + Textures::HalfRes,
                         textures_->squareTileTex (type, Textures::squareTile::BarV4));
    break;
  case 0b1100:
    painter->drawPixmap (drawing_x + Textures::HalfRes, drawing_y + Textures::HalfRes,
                         textures_->squareTileTex (type, Textures::squareTile::Corner4));
    break;
  }
}

void GameMap::drawBackground () {
  if (background_ != nullptr)
    delete background_;
  background_ = new QPixmap (width_ * Textures::FullRes, height_ * Textures::FullRes);
  QPainter *painter = new QPainter (background_);
  for (int x = 0; x < width_; ++ x)
    for (int y = 0; y < height_; ++ y) {
      Textures::tile type;
      switch (map_ [x] [y].tile) {
      case GameMap::tile::Floor:
        type = Textures::tile::Floor;
        break;
      case GameMap::tile::Wall:
        type = Textures::tile::Celling;
        break;
      default:
        continue;
      }
      drawAdhereTile (painter, type, x, y,
                      x * Textures::FullRes, y * Textures::FullRes);
    }
  delete painter;
}

void GameMap::drawWalls () {
  if (walls_ != nullptr)
    delete walls_;
  walls_ = new QPixmap (width_ * Textures::FullRes, height_ * Textures::FullRes);
  walls_->fill (Qt::transparent);
  QPainter *painter = new QPainter (walls_);
  for (int x = 0; x < width_; ++ x)
    for (int y = 0; y < height_; ++ y)
      if (map_ [x] [y].tile == GameMap::tile::Wall) {
        drawAdhereTile (painter, Textures::tile::Celling, x, y,
                        x * Textures::FullRes, (y - 2) * Textures::FullRes);
        painter->drawPixmap (x * Textures::FullRes, (y -1) * Textures::FullRes,
                             QPixmap (":/textures/Dungeon/WallPlaceholder.png"));
      }
  delete painter;
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
