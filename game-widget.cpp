#include "game-widget.h"

GameWidget::GameWidget (Textures *textures, QWidget *parent) : QWidget (parent), textures_ (textures) {
  this->setAttribute (Qt::WA_DeleteOnClose);
  //  this->setWindowFlags (Qt::FramelessWindowHint);

  game_ = new GameMechanics (textures_, 30, 16);
  this->showMaximized ();
}

GameWidget::~GameWidget () {
  if (game_ != nullptr)
    delete game_;
}

void GameWidget::close () {
  QWidget::close ();
  emit closed ();
}

void GameWidget::paintEvent (QPaintEvent *) {
  if (game_ == nullptr)
    return;
  QPainter *painter = new QPainter (this);

  if (back_flag_)
    painter->drawPixmap (0, 0, *game_->background ());
  if (walls_flag_)
    painter->drawPixmap (0, 0, *game_->walls ());

  if (grid_flag_) {
    painter->setPen (Qt::green);
    for (int x = 0; x < 50; ++ x)
      for (int y = 0; y < 50; ++ y)
        painter->drawRect (x * Textures::FullRes, y * Textures::FullRes,
                           Textures::FullRes, Textures::FullRes);
    painter->setPen (Qt::red);
    for (int x = 0; x < 50; x += 5)
      for (int y = 0; y < 50; y += 5)
        painter->drawRect (x * Textures::FullRes, y * Textures::FullRes,
                           Textures::FullRes * 5, Textures::FullRes * 5);
  }
  delete painter;
}

void GameWidget::keyPressEvent (QKeyEvent *event) {
  switch (event->key ()) {
  case Qt::Key_G:
    grid_flag_ = !grid_flag_;
    break;
  case Qt::Key_R:
    if (game_ != nullptr)
      delete game_;
    game_ = new GameMechanics (textures_, 30, 15);
    break;
  case Qt::Key_B:
    back_flag_ = !back_flag_;
    break;
  case Qt::Key_N:
    walls_flag_= !walls_flag_;
    break;
  case Qt::Key_Escape:
    this->close ();
    return;
  }
  this->repaint ();
}

void GameWidget::mousePressEvent(QMouseEvent *event) {
  switch (event->button ()) {
  case Qt::LeftButton:
    game_->onGrid (event->x () / 64, event->y () / 64);
    event->accept ();
    break;
  case Qt::RightButton:
    game_->offGrid (event->x () / 64, event->y () / 64);
    event->accept ();
    break;
  default:
    break;
  }
  this->repaint ();
}

void GameWidget::closeEvent (QCloseEvent *event) {
  emit closed ();
  QWidget::closeEvent (event);
}
