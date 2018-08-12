#include "mazeboard.h"

MazeBoard::MazeBoard (QWidget *parent) : QFrame (parent) {
  game_ = new GameMechanics (20, Size {7, 7}, 1); // ma pobierać z widgetów
  maze_square_ = new QPixmap [16];
  start_icon_ = new QPixmap;
  end_icon_ = new QPixmap;
  background_ = new QPixmap [4];
  player_icon_ = new QPixmap;
  reloadTextures ();
  redrawMaze ();
  //  timer = new QTimer (this);
  //  connect (timer, SIGNAL (timeout()), this, SLOT(tick ()));
  //  timer->start (100);
}

void MazeBoard::tick () {

}

MazeBoard::~MazeBoard () {
  if (game_ != nullptr)
    delete game_;
  if (whole_maze_ != nullptr)
    delete whole_maze_;
  if (maze_square_ != nullptr)
    delete [] maze_square_;
  if (start_icon_ != nullptr)
    delete start_icon_;
  if (end_icon_ != nullptr)
    delete end_icon_;
  if (background_ != nullptr)
    delete [] background_;
  if (player_icon_ != nullptr)
    delete player_icon_;
  if (timer != nullptr)
    delete timer;
}

void MazeBoard::newGame (int num_levels) {
  if (game_ != nullptr)
    delete game_;
  game_ = new GameMechanics (num_levels, Size {100, 100}, 1); // ma pobierać z widgetów
  redrawMaze ();
}

void MazeBoard::handleKeyEvent (QKeyEvent *event) {
  switch (event->key ()) {
    case Qt::Key_W:
      if (game_->tryMove (direction::kUp))
        ++ playerSteps_;
      player_rotation_.reset ();
      player_rotation_.rotate (0);
      break;
    case Qt::Key_D:
      if (game_->tryMove (direction::kRight))
        ++ playerSteps_;
      player_rotation_.reset ();
      player_rotation_.rotate (90);
      break;
    case Qt::Key_S:
      if (game_->tryMove (direction::kDown))
        ++ playerSteps_;
      player_rotation_.reset ();
      player_rotation_.rotate (180);
      break;
    case Qt::Key_A:
      if (game_->tryMove (direction::kLeft))
        ++ playerSteps_;
      player_rotation_.reset ();
      player_rotation_.rotate (270);
      break;
    case Qt::Key_E:
      if (game_->tryEnter ())
        redrawMaze ();
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
        redrawMaze ();
        break;
      case Qt::Key_Left:
        game_->previousLevel ();
        redrawMaze ();
        break;
      case Qt::Key_O:
        game_->jumpToStart ();
        break;
      case Qt::Key_P:
        game_->jumpToEnd ();
        break;
      case Qt::Key_Period:
        ++ fov_size_;
        break;
      case Qt::Key_Comma:
        -- fov_size_;
        break;
      case Qt::Key_G:
        newGame (20);
        break;
    }
  }
  update ();
}

void MazeBoard::paintEvent (QPaintEvent *event) {
  QFrame::paintEvent (event);
  QRect paint_target (this->lineWidth (), this->lineWidth (),
                      this->width () - this->lineWidth () * 2,
                      this->height () - this->lineWidth () * 2);
  QPainter *painter = new QPainter (this);
  if (is_antialiasing_)
    painter->setRenderHint (QPainter::SmoothPixmapTransform);
  painter->drawPixmap (paint_target, *whole_maze_,
                       QRect ((playerPositionX () - fov_size_ / 2) * textures_res_,
                              (playerPositionY () - fov_size_ / 2) * textures_res_,
                              fov_size_ * textures_res_, fov_size_ * textures_res_));
  painter->drawPixmap (paint_target, QPixmap ("mazes/shadow.png"));

  delete painter;
}

void MazeBoard::redrawMaze () { // dodać jakiś panel ładowania, czy coś
  if (whole_maze_ != nullptr)
    delete whole_maze_;
  whole_maze_ = new QPixmap (game_->mazeWidth () * textures_res_, game_->mazeHeight () * textures_res_);
  QPainter *painter = new QPainter (whole_maze_);
  int offset = textures_res_ * 0.25;
  for (int x = 0; x < game_->mazeWidth (); ++ x)
    for (int y = 0; y < game_->mazeHeight (); ++ y)
      painter->drawPixmap (QPoint (x * textures_res_, y * textures_res_),
                           background_ [game_->backgroundAt (x, y)]);
  for (int x = 0; x < game_->mazeWidth (); ++ x)
    for (int y = 0; y < game_->mazeHeight (); ++ y)
      painter->drawPixmap (QPoint (x * textures_res_ - offset, y * textures_res_ - offset),
                           maze_square_ [game_->at (x, y)]);
  painter->drawPixmap (QPoint (game_->startX () * textures_res_ - offset,
                               game_->startY () * textures_res_ - offset),
                       *start_icon_);
  painter->drawPixmap (QPoint (game_->endX () * textures_res_ - offset,
                               game_->endY () * textures_res_ - offset),
                       *end_icon_);
  delete painter;
}

void MazeBoard::reloadTextures () {
  int textures_res = textures_res_ * 1.5;
  player_icon_->load (":/player_characters/Mummy.png");
  QPixmap maze_textures ("mazes/bricksHDdesert.png");
  for (int i = 0, q = 0; i < 16; ++ q)
    for (int p = 0; p < 5 && i < 16; ++ p, ++ i)
      maze_square_ [i] = maze_textures.copy (textures_res * p, textures_res * q,
                                             textures_res, textures_res);
  for (int i = 0; i < 4; ++ i)
    background_ [i] = maze_textures.copy (textures_res * 6, textures_res * i,
                                          textures_res_, textures_res_);
  *start_icon_ = maze_textures.copy (textures_res * 5, 0,
                                     textures_res, textures_res);
  *end_icon_ = maze_textures.copy (textures_res * 5, textures_res,
                                   textures_res, textures_res);
}
