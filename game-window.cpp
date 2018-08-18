#include "maze-window.h"

MazeWindow::MazeWindow () {
  block_textures_ = new QPixmap *[gameField::block::NumVariations];
  for (int i = 0; i < gameField::block::NumVariations; ++ i)
    block_textures_ [i] = new QPixmap [gameField::colour::NumVariations];
  extra_textures_ = new QPixmap [gameField::extra::NumVariations];
  game_ = new GameMechanics ();
  reloadTextures ();
  resize (800, 800);
}

MazeWindow::~MazeWindow () {
  if (block_textures_ != nullptr) {
    for (int i = 0; i < gameField::block::NumVariations; ++ i)
      delete [] block_textures_ [i];
    delete [] block_textures_;
  }
  if (extra_textures_ != nullptr)
    delete [] extra_textures_;
  if (game_ != nullptr)
    delete game_;
}

void MazeWindow::paintEvent (QPaintEvent *) {
  if (game_ == nullptr)
    return;
  QPainter *painter = new QPainter (this);

  for (int x = 0; x < game_->mapWidth (); ++ x)
    for (int y = 0; y < game_->mapHeight (); ++ y)
      for (int layer = 0; layer < game_->mapNumLayers (); ++ layer)
        if (game_->printFlagBrick (x, y, layer))
          painter->drawPixmap (x * tex_res_, y * tex_res_, block_textures_
                               [game_->blockIndex (x ,y, layer)] [game_->colorIndex (x, y, layer)]);
  if (grid_flag) {
    painter->setPen (Qt::gray);
    for (int x = 0; x < 50; ++ x)
      for (int y = 0; y < 50; ++ y)
        painter->drawRect (x * tex_res_, y * tex_res_, tex_res_, tex_res_);
    painter->setPen (Qt::black);
    for (int x = 0; x < 50; x += 5)
      for (int y = 0; y < 50; y += 5)
        painter->drawRect (x * tex_res_, y * tex_res_, tex_res_ * 5, tex_res_ * 5);
  }
  if (text_flag_)
    for (int x = 0; x < 50; ++ x)
      for (int y = 0; y < 50; ++ y)
        painter->drawText (x * tex_res_, (y + 1) * tex_res_,
                           QString::number (game_->blockIndex (x ,y, 0)));
  delete painter;
}

void MazeWindow::keyPressEvent (QKeyEvent *event) {
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
      game_ = new GameMechanics ();
      break;
    case Qt::Key_Escape:
      exit (0);
  }
  repaint ();
}

void MazeWindow::reloadTextures () {
  QPixmap *block_full = new QPixmap (":/textures/blocks.png");
//  QPixmap *extra_full = new QPixmap (":/textures/extras.png");
//  for (int i = 0; i < gameField::extra::NumVariations; ++ i)
//    extra_textures_ [i] = extra_full->copy (0, tex_res_ * i, tex_res_, tex_res_);
  for (int y = 0; y < gameField::colour::NumVariations; ++ y)
    for (int x = 0; x < gameField::block::NumVariations; ++ x)
      block_textures_ [x] [y] = block_full->copy (x * tex_res_, y * tex_res_, tex_res_, tex_res_);
//  delete extra_full;
  delete block_full;
//  delete items_full;
}
