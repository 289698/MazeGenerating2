#include "game-map.h"

using namespace gameField;

GameMap::GameMap (int width, int height, int num_layers) :
  width_ (width), height_ (height), num_layers_ (num_layers) {
  map_ = new int *[width_];
  for (int i = 0; i < width_; ++ i)
    map_ [i] = new int [height_];
  for (int x = 0; x < width_; ++ x)
    for (int y = 0; y < height_; ++ y)
      map_ [x] [y] = (logic::blockPrintFlag | colour::Grass | block::Ground |
                      ((logic::blockPrintFlag | colour::Dirt | block::Quoin1) << layer::Offset));
  generateMaze (10, 10, true, 0, 0, 1);
}

GameMap::~GameMap () {
  if (map_ != nullptr)
    for (int i = 0; i < width_; ++ i)
      delete [] map_ [i];
  delete [] map_;
}


bool GameMap::printFlagBrick (int x, int y, int layer_index) {
  if (x < 0 || x >= width_ || y < 0 || y >= height_ || layer_index < 0 || layer_index >= num_layers_)
    return false;
  return ((map_ [x] [y] & (logic::blockPrintFlag << (layer::Offset * layer_index))) ==
          (logic::blockPrintFlag << (layer::Offset * layer_index)));
}

int GameMap::colorIndex (int x, int y, int layer_index) {
  if (x < 0 || x >= width_ || y < 0 || y >= height_ || layer_index < 0 || layer_index >= num_layers_)
    return false;
  return ((map_ [x] [y] & (colour::Bits << (layer::Offset * layer_index))) >>
          (colour::Offset + (layer::Offset * layer_index)));
}

int GameMap::blockIndex (int x, int y, int layer_index) {
  if (x < 0 || x >= width_ || y < 0 || y >= height_ || layer_index < 0 || layer_index >= num_layers_)
    return false;
  return ((map_ [x] [y] & (block::Bits << (layer::Offset * layer_index))) >>
          (block::Offset + (layer::Offset * layer_index)));
}

void GameMap::generateMaze (int maze_width, int maze_height, bool maze_border_flag,
                            int map_x, int map_y, int layer_index) { // dodać sprawdzanie, czy się zmieści i wsparcie dla layer
  HuntAndKill *maze = new HuntAndKill (maze_width, maze_height, Point {2, 2}, maze_border_flag);
  /*! resetowanie odpowiednich bitów w zadanej części mapy i warstwie
   * na 0 za pomocą bitwise NOR*/
  for (int i = 0; i < maze->width () * 5; ++ i)
    for (int j = 0; j < maze->height () * 5; ++ j)
      map_ [map_x + i] [map_y + j] &=
          ~((block::Bits | logic::blockPrintFlag) << (layer::Offset * layer_index));

  /*! (x, y) to punkt w maze, (map_x, map_y) to punkt w map_
   * przy iteracji y zwiększam y o 1 i pozycję y w map_ (map_y) o 5
   * przy iteracji x zwiększam x o 1 i zmniejszam map_y do wyjściowej wartości */
  for (int x = 0; x < maze->width (); ++ x, map_x += 5, map_y -= maze->height () * 5)
    for (int y = 0; y < maze->height (); ++ y, map_y += 5) {
      int current_maze_square = maze->at (x, y);

      /*! ustawianie odpowiednich wartości na bokach fragmentu mapy sumą binarną wartości pola mapy
       * z odpowiedną wartością klocka*/
      //! górny bok
      if ((current_maze_square & mazeSquare::Up) == mazeSquare::Up)
        for (int i = 1; i < 4; ++ i)
          map_ [map_x + i] [map_y] |=
              ((block::Wall1 | logic::blockPrintFlag) << (layer::Offset * layer_index));
      //! prawy bok
      if ((current_maze_square & mazeSquare::Right) == mazeSquare::Right)
        for (int i = 1; i < 4; ++ i)
          map_ [map_x + 4] [map_y + i] |=
              ((block::Wall2 | logic::blockPrintFlag) << (layer::Offset * layer_index));
      //! dolny bok
      if ((current_maze_square & mazeSquare::Down) == mazeSquare::Down)
        for (int i = 1; i < 4; ++ i)
          map_ [map_x + i] [map_y + 4] |=
              ((block::Wall3 | logic::blockPrintFlag) << (layer::Offset * layer_index));
      //! lewy bok
      if ((current_maze_square & mazeSquare::Left) == mazeSquare::Left)
        for (int i = 1; i < 4; ++ i)
          map_ [map_x] [map_y + i] |=
              ((block::Wall4 | logic::blockPrintFlag) << (layer::Offset * layer_index));

      /*! ustawianie odpowiednich węgłów i kątów sumą binarną jw.; gdy brak rogu - albo pusta
       * przestrzeń, albo węgieł (wtedy, gdy sąsiednie komórki labiryntu są odpowiednie)*/
      //! górny-prawy róg
      switch (current_maze_square & (mazeSquare::Up | mazeSquare::Right)) {
        case mazeSquare::Empty:
          if ((maze->at (x + 1, y) & mazeSquare::Up) == mazeSquare::Up ||
              (maze->at (x, y - 1) & mazeSquare::Right) == mazeSquare::Right)
            map_ [map_x + 4] [map_y] |=
                ((block::Quoin3 | logic::blockPrintFlag) << (layer::Offset * layer_index));
          break;
        case mazeSquare::Up:
          map_ [map_x + 4] [map_y] |=
              ((block::Wall1 | logic::blockPrintFlag) << (layer::Offset * layer_index));
          break;
        case mazeSquare::Right:
          map_ [map_x + 4] [map_y] |=
              ((block::Wall2 | logic::blockPrintFlag) << (layer::Offset * layer_index));
          break;
        case (mazeSquare::Up | mazeSquare::Right):
          map_ [map_x + 4] [map_y] |=
              ((block::Corner1 | logic::blockPrintFlag) << (layer::Offset * layer_index));
          break;
      }//! prawy-dolny róg
      switch (current_maze_square & (mazeSquare::Right | mazeSquare::Down)) {
        case mazeSquare::Empty:
          if ((maze->at (x, y + 1) & mazeSquare::Right) == mazeSquare::Right ||
              (maze->at (x + 1, y) & mazeSquare::Down) == mazeSquare::Down)
            map_ [map_x + 4] [map_y + 4] |=
                ((block::Quoin4 | logic::blockPrintFlag) << (layer::Offset * layer_index));
          break;
        case mazeSquare::Right:
          map_ [map_x + 4] [map_y + 4] |=
              ((block::Wall2 | logic::blockPrintFlag) << (layer::Offset * layer_index));
          break;
        case mazeSquare::Down:
          map_ [map_x + 4] [map_y + 4] |=
              ((block::Wall3 | logic::blockPrintFlag) << (layer::Offset * layer_index));
          break;
        case (mazeSquare::Right | mazeSquare::Down):
          map_ [map_x + 4] [map_y + 4] |=
              ((block::Corner2 | logic::blockPrintFlag) << (layer::Offset * layer_index));
          break;
      }//! dolny-lewy róg
      switch (current_maze_square & (mazeSquare::Down | mazeSquare::Left)) {
        case mazeSquare::Empty:
          if ((maze->at (x - 1, y) & mazeSquare::Down) == mazeSquare::Down ||
              (maze->at (x, y + 1) & mazeSquare::Left) == mazeSquare::Left)
            map_ [map_x] [map_y + 4] |=
                ((block::Quoin1 | logic::blockPrintFlag) << (layer::Offset * layer_index));
          break;
        case mazeSquare::Down:
          map_ [map_x] [map_y + 4] |=
              ((block::Wall3 | logic::blockPrintFlag) << (layer::Offset * layer_index));
          break;
        case mazeSquare::Left:
          map_ [map_x] [map_y + 4] |=
              ((block::Wall4 | logic::blockPrintFlag) << (layer::Offset * layer_index));
          break;
        case (mazeSquare::Down | mazeSquare::Left):
          map_ [map_x] [map_y + 4] |=
              ((block::Corner3 | logic::blockPrintFlag) << (layer::Offset * layer_index));
          break;
      }//! lewy-górny róg
      switch (current_maze_square & (mazeSquare::Left | mazeSquare::Up)) {
        case mazeSquare::Empty:
          if ((maze->at (x, y - 1) & mazeSquare::Left) == mazeSquare::Left ||
              (maze->at (x - 1, y) & mazeSquare::Up) == mazeSquare::Up)
            map_ [map_x] [map_y] |=
                ((block::Quoin2 | logic::blockPrintFlag) << (layer::Offset * layer_index));
          break;
        case mazeSquare::Left:
          map_ [map_x] [map_y] |=
              ((block::Wall4 | logic::blockPrintFlag) << (layer::Offset * layer_index));
          break;
        case mazeSquare::Up:
          map_ [map_x] [map_y] |=
              ((block::Wall1 | logic::blockPrintFlag) << (layer::Offset * layer_index));
          break;
        case (mazeSquare::Left | mazeSquare::Up):
          map_ [map_x] [map_y] |=
              ((block::Corner4 | logic::blockPrintFlag) << (layer::Offset * layer_index));
          break;
      }
    }
  delete maze;
}
