#include "mazeboard.h"

MazeBoard::MazeBoard (QWidget *parent) : QFrame (parent) {
  game_ = new GameMechanics ();
  setFocusPolicy (Qt::StrongFocus);
  setFrameStyle (QFrame::Panel | QFrame::Sunken);
  setLineWidth (5);
}

MazeBoard::~MazeBoard () {
  if (game_ != nullptr)
    delete game_;
}

void MazeBoard::generateMaze () {
  if (game_ != nullptr)
    delete game_;
  game_ = new GameMechanics ();
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
    case Qt::Key_Up:
      game_->nextLevel ();
      break;
    case Qt::Key_Down:
      game_->previousLevel ();
      break;
    case Qt::Key_G:
      generateMaze ();
      update ();
      break;
    case Qt::Key_Q:
      exit (0);

//    default:
//      qDebug() << "klawisz bez funkcji, MazeBoards";
  }
  update ();
}

inline int MazeBoard::grid (int p) {
  return (p+1) * maze_size_ * 2 + p * 2 + 30;
}

void MazeBoard::paintEvent(QPaintEvent *event) {
  QFrame::paintEvent (event);
  QPainter painter (this);

  for (int x = -1; x <= game_->mazeWidth (); ++x)
    for (int y = -1; y <= game_->mazeHeight (); ++y){
      drawBorders (&painter, x, y);
      //painter.drawText (grid (x) - 2, grid (y) + 5, "8");
    }
  drawPlayer(&painter);
  painter.drawText (grid (game_->endX ()), grid (game_->endY ()), "X");
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
