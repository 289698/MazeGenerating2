#include "launcher-widget.h"

LauncherWidget::LauncherWidget (QWidget *parent) : QWidget (parent) {
  this->setWindowFlags (Qt::FramelessWindowHint);
  this->resize (200, 100);
  QGridLayout *layout = new QGridLayout (this);

  QPushButton *game = new QPushButton ("GAME", this);
  game->setCursor (Qt::PointingHandCursor);
  connect (game, SIGNAL(clicked ()), this, SLOT (newGame ()));
  layout->addWidget (game, 0, 0);

  QPushButton *quitb = new QPushButton ("QUIT", this);
  quitb->setCursor (Qt::PointingHandCursor);
  connect (quitb, SIGNAL (clicked ()), QApplication::instance (), SLOT (quit ()));
  layout->addWidget (quitb, 1, 0);

  this->setLayout (layout);

  textures_ = new Textures ();
}

LauncherWidget::~LauncherWidget () {
  if (textures_ != nullptr)
    delete textures_;
}

void LauncherWidget::keyPressEvent (QKeyEvent *event) {
  switch (event->key ()) {
    case Qt::Key_1:
      newGame ();
      break;
    case Qt::Key_Escape:
      QApplication::instance ()->quit ();
  }
}

void LauncherWidget::newGame () {
  game_widget_ = new GameWidget (textures_);
  connect (game_widget_, SIGNAL (closed ()), this, SLOT (QWidgetClosed ()));
  game_widget_->show ();
  this->hide ();
}

void LauncherWidget::QWidgetClosed () {
  this->show ();
}
