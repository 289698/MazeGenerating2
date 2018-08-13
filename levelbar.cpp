#include "levelbar.h"

LevelBar::LevelBar (QWidget *parent) : QWidget(parent) {
  background_ = new QPixmap (":/hud/level.png");
  setFixedSize (background_->size ());
}

LevelBar::~LevelBar () {
  if (background_ != nullptr)
    delete background_;
}

void LevelBar::paintEvent (QPaintEvent *) {
  QPainter *painter = new QPainter (this);
  painter->drawPixmap (0, 0, *background_);
  delete painter;
}
