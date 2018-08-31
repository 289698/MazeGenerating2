#include "game-widget.h"

GameWidget::GameWidget (Textures *textures, QWidget *parent) : QWidget (parent), textures_ (textures) {
  this->setAttribute (Qt::WA_DeleteOnClose);
  this->setWindowFlags (Qt::FramelessWindowHint);

  game_ = new GameMechanics (50, 50, "");
  this->resize (800, 800);
  redrawBackLayer ();
  redrawGroundLayer ();
  redrawBlockLayer ();
  redrawExtraLayer ();
}

GameWidget::~GameWidget () {
  if (game_ != nullptr)
    delete game_;
  if (back_layer_ != nullptr)
    delete back_layer_;
  if (ground_layer_ != nullptr)
    delete ground_layer_;
  if (block_layer_ != nullptr)
    delete block_layer_;
  if (extra_layer_ != nullptr)
    delete extra_layer_;
}

void GameWidget::close () {
  QWidget::close ();
  emit closed ();
}

void GameWidget::paintEvent (QPaintEvent *) {
  if (game_ == nullptr)
    return;
  QPainter *painter = new QPainter (this);
  painter->drawPixmap (0, 0, *back_layer_);
  painter->drawPixmap (0, 0, *ground_layer_);
  painter->drawPixmap (0, 0, *block_layer_);
  painter->drawPixmap (0, 0, *extra_layer_);

  if (grid_flag) {
    painter->setPen (Qt::gray);
    for (int x = 0; x < 50; ++ x)
      for (int y = 0; y < 50; ++ y)
        painter->drawRect (x * Textures::Resolution, y * Textures::Resolution, Textures::Resolution, Textures::Resolution);
    painter->setPen (Qt::black);
    for (int x = 0; x < 50; x += 5)
      for (int y = 0; y < 50; y += 5)
        painter->drawRect (x * Textures::Resolution, y * Textures::Resolution, Textures::Resolution * 5, Textures::Resolution * 5);
  }
  //  if (text_flag_)
  //    for (int x = 0; x < 50; ++ x)
  //      for (int y = 0; y < 50; ++ y)
  //        painter->drawText (x * Textures::Resolution, (y + 1) * Textures::Resolution,
  //                           QString::number (game_->blockIndex (x ,y, 0)));
  delete painter;
}

void GameWidget::keyPressEvent (QKeyEvent *event) {
  switch (event->key ()) {
    case Qt::Key_G:
      grid_flag = !grid_flag;
      break;
    case Qt::Key_T:
      text_flag_ = !text_flag_;
      break;
    case Qt::Key_R:
      if (game_ != nullptr)
        delete game_;
      game_ = new GameMechanics (50, 50, "");
      break;
    case Qt::Key_Escape:
      this->close ();
      return;
  }
  this->repaint ();
}

void GameWidget::closeEvent (QCloseEvent *event) {
  emit closed ();
  QWidget::closeEvent (event);
}

void GameWidget::redrawBackLayer () {
  if (back_layer_ != nullptr)
    delete back_layer_;
  back_layer_ = new QPixmap (game_->mapWidth () * Textures::Resolution,
                             game_->mapHeight () * Textures::Resolution);
//  back_layer_->fill (Qt::transparent);
  QPainter *painter = new QPainter (back_layer_);
  for (int x = 0; x < game_->mapWidth (); ++ x)
    for (int y = 0; y < game_->mapHeight (); ++ y)
      painter->drawPixmap (x * Textures::Resolution, y * Textures::Resolution,
                           textures_->backTexture (game_->backColor (x, y)));
  delete painter;
}

void GameWidget::redrawGroundLayer () {
  if (ground_layer_ != nullptr)
    delete ground_layer_;
  ground_layer_ = new QPixmap (game_->mapWidth () * Textures::Resolution,
                               game_->mapHeight () * Textures::Resolution);
  ground_layer_->fill (Qt::transparent);
  QPainter *painter = new QPainter (ground_layer_);
  for (int x = 0; x < game_->mapWidth (); ++ x)
    for (int y = 0; y < game_->mapHeight (); ++ y)
      if (game_->groundPrintFlag (x, y))
        painter->drawPixmap (x * Textures::Resolution, y * Textures::Resolution,
                             textures_->groundTexture (game_->ground (x, y), game_->groundColor (x, y)));
  delete painter;
}

void GameWidget::redrawBlockLayer () {
  if (block_layer_ != nullptr)
    delete block_layer_;
  block_layer_ = new QPixmap (game_->mapWidth () * Textures::Resolution,
                             game_->mapHeight () * Textures::Resolution);
  block_layer_->fill (Qt::transparent);
  QPainter *painter = new QPainter (block_layer_);
  for (int x = 0; x < game_->mapWidth (); ++ x)
    for (int y = 0; y < game_->mapHeight (); ++ y)
      if (game_->blockPrintFlag (x, y))
        painter->drawPixmap (x * Textures::Resolution, y * Textures::Resolution,
                             textures_->blockTexture (game_->block (x, y), game_->blockColor (x, y)));
  delete painter;
}

void GameWidget::redrawExtraLayer () {
  if (extra_layer_ != nullptr)
    delete extra_layer_;
  extra_layer_ = new QPixmap (game_->mapWidth () * Textures::Resolution,
                             game_->mapHeight () * Textures::Resolution);
  extra_layer_->fill (Qt::transparent);
  QPainter *painter = new QPainter (extra_layer_);
  for (int x = 0; x < game_->mapWidth (); ++ x)
    for (int y = 0; y < game_->mapHeight (); ++ y)
      if (game_->extraPrintFlag (x, y))
        painter->drawPixmap (x * Textures::Resolution, y * Textures::Resolution,
                             textures_->extraTexture (game_->extra (x, y)));
  delete painter;
}
