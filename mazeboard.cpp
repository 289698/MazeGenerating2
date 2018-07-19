#include "mazeboard.h"

MazeBoard::MazeBoard (QWidget *parent) : QFrame (parent) {
  game_ = new GameMechanics (10, Size {13, 13}, 1); // ma pobierać z widgetów
  setFocusPolicy (Qt::StrongFocus);
  setFrameStyle (QFrame::Panel | QFrame::Sunken);
  setLineWidth (5);
}

MazeBoard::~MazeBoard () {
  if (game_ != nullptr)
    delete game_;
}

void MazeBoard::newGame (int num_levels) {
  if (game_ != nullptr)
    delete game_;
  game_ = new GameMechanics (num_levels, Size {13, 13}, 1); // ma pobierać z widgetów
}

void MazeBoard::keyPressEvent (QKeyEvent *event) {
  switch (event->key ()) {
    case Qt::Key_W:
      game_->tryMove (direction::kUp);
      break;
    case Qt::Key_D:
      game_->tryMove (direction::kRight);
      break;
    case Qt::Key_S:
      game_->tryMove (direction::kDown);
      break;
    case Qt::Key_A:
      game_->tryMove (direction::kLeft);
      break;
    case Qt::Key_E:
      game_->tryEnter ();
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
      case Qt::Key_L:
        is_distance_enabled_ = !is_distance_enabled_;
        break;
      case Qt::Key_G:
        newGame (10);
        update ();
        break;
    }
  }
  update ();
}

inline int MazeBoard::grid (int p) {
  p += game_->numLevels () - game_->currentLevel ();
  return (p+1) * maze_size_ * 2 + p * 2 + 30;
}

void MazeBoard::paintEvent(QPaintEvent *event) {
  QFrame::paintEvent (event);
  QPainter painter (this);

  for (int x = -1; x <= game_->mazeWidth (); ++ x)
    for (int y = -1; y <= game_->mazeHeight (); ++ y)
      drawBorders (&painter, x, y);

  painter.setPen (Qt::blue);
  drawPlayer(&painter);

  painter.setPen (Qt::green);
  painter.drawRect (grid (game_->startX ()) - 10, grid (game_->startY ()) - 10, 20, 20);

  painter.setPen (Qt::red);
  painter.drawRect (grid (game_->endX ()) - 10, grid (game_->endY ()) - 10, 20, 20);

  if (is_distance_enabled_) {
    painter.setPen (Qt::gray);
    for (int x = 0; x < game_->mazeWidth (); ++ x)
      for (int y = 0; y < game_->mazeWidth (); ++ y)
        painter.drawText (grid (x) - 8, grid (y) + 5,
                          QString::number (game_->distanceFromPlayer (x, y)));
  }
}

void MazeBoard::drawBorders (QPainter *painter, int x, int y) {
  int current_square = game_->at (x, y);
  x = grid (x), y = grid (y);
  if ((current_square & square::kUp) == square::kUp)
    painter->drawLine (x - maze_size_, y - maze_size_,
                       x + maze_size_, y - maze_size_);
  if ((current_square & square::kRight) == square::kRight)
    painter->drawLine (x + maze_size_, y - maze_size_,
                       x + maze_size_, y + maze_size_);
  if ((current_square & square::kDown) == square::kDown)
    painter->drawLine (x - maze_size_, y + maze_size_,
                       x + maze_size_, y + maze_size_);
  if ((current_square & square::kLeft) == square::kLeft)
    painter->drawLine (x - maze_size_, y - maze_size_,
                       x - maze_size_, y + maze_size_);
}

void MazeBoard::drawPlayer (QPainter *painter) {
  painter->drawEllipse(QPoint (grid (game_->playerPositionX ()),
                              grid (game_->playerPositionY ())),
                      5, 5);
  painter->drawEllipse(QPoint (grid (game_->playerPositionX ()),
                              grid (game_->playerPositionY ())),
                      8, 8);
  painter->drawEllipse(QPoint (grid (game_->playerPositionX ()),
                              grid (game_->playerPositionY ())),
                      11, 11);
}
