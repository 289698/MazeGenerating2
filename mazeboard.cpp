#include "mazeboard.h"

MazeBoard::MazeBoard (QWidget *parent) : QFrame (parent) {
  game_ = new GameMechanics (20, Size {4, 4}, 1); // ma pobierać z widgetów
  maze_square_ = new QImage [16];
  player_icon_ = new QImage;
  reloadTextures ();
  timer = new QTimer (this);
  connect (timer, SIGNAL (timeout()), this, SLOT(increaseAngle ()));
  timer->start (20);
}

MazeBoard::~MazeBoard () {
  if (game_ != nullptr)
    delete game_;
  if (maze_square_ != nullptr)
    delete [] maze_square_;
  if (player_icon_ != nullptr)
    delete player_icon_;
}

void MazeBoard::newGame (int num_levels) {
  if (game_ != nullptr)
    delete game_;
  game_ = new GameMechanics (num_levels, Size {4, 4}, 1); // ma pobierać z widgetów
}

void MazeBoard::handleKeyEvent (QKeyEvent *event) {
  switch (event->key ()) {
    case Qt::Key_W:
      game_->tryMove (direction::kUp);
      player_rotation_.reset ();
      player_rotation_.rotate (0);
      break;
    case Qt::Key_D:
      game_->tryMove (direction::kRight);
      player_rotation_.reset ();
      player_rotation_.rotate (90);
      break;
    case Qt::Key_S:
      game_->tryMove (direction::kDown);
      player_rotation_.reset ();
      player_rotation_.rotate (180);
      break;
    case Qt::Key_A:
      game_->tryMove (direction::kLeft);
      player_rotation_.reset ();
      player_rotation_.rotate (270);
      break;
    case Qt::Key_E:
      game_->tryEnter ();
      break;
    case Qt::Key_X:
      is_antialiasing_ = !is_antialiasing_;
      break;
    case Qt::Key_QuoteLeft:
      game_->toogleGodMode ();
      break;
    case Qt::Key_Escape:
      exit (0);
      //    default:
      //      qDebug() << event;
  }
  if (game_->isGod ()) {
    switch (event->key ()) {
      case Qt::Key_R:
        reloadTextures ();
        break;
      case Qt::Key_Right:
        game_->nextLevel ();
        break;
      case Qt::Key_Left:
        game_->previousLevel ();
        break;
      case Qt::Key_O:
        game_->jumpToStart ();
        break;
      case Qt::Key_P:
        game_->jumpToEnd ();
        break;
      case Qt::Key_G:
        newGame (20);
        update ();
        break;
    }
  }
  update ();
}

void MazeBoard::paintEvent(QPaintEvent *event) {
  QFrame::paintEvent (event);
  // Drawing maze
  QImage *maze = new QImage (game_->mazeWidth () * texture_resolution_,
                             game_->mazeHeight () * texture_resolution_, QImage::Format_ARGB32);
  QPainter *painter = new QPainter (maze);
  painter->drawImage (QPoint (game_->playerPositionX () * texture_resolution_ ,
                              game_->playerPositionY () * texture_resolution_ ),
                      player_icon_->transformed (player_rotation_));
  for (int x = 0; x < game_->mazeWidth (); ++ x)
    for (int y = 0; y < game_->mazeHeight (); ++ y)
      painter->drawImage (QPoint (x * texture_resolution_, y * texture_resolution_),
                          maze_square_ [game_->at (x, y)]);
  painter->end ();
  // Resizing and positioning
  painter->begin (this);
  if (is_antialiasing_)
    painter->setRenderHint (QPainter::SmoothPixmapTransform);
  if (this->width () > this->height ()) {
    maze_size_ = this->height () - 50;
    margin_x_ = (this->width () - maze_size_) / 2;
    margin_y_ = 25;
  } else {
    maze_size_ = this->width () - 50;
    margin_x_ = 25;
    margin_y_ = (this->height () - maze_size_) / 2;
  }
  painter->drawImage (QRect (margin_x_, margin_y_, maze_size_, maze_size_),
                      maze->transformed (QTransform ().rotate (angle_)));

  delete maze;
  delete painter;
}

void MazeBoard::reloadTextures () {
  player_icon_->load ("textures/player_characters/cube.png");
  QImage maze_textures ("textures/mazes/curved.png");

  for (int i = 0, q = 0; i < 15; ++ q)
    for (int p = 0; p < 5; ++ p, ++ i)
      maze_square_ [i] = maze_textures.copy (80 * p, 80 * q, 80, 80);

  maze_square_ [15].load ("textures/curved_maze/maze_square_15.png");
}
