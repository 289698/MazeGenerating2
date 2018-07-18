#ifndef MAZEWINDOW_H
#define MAZEWINDOW_H

#include <QFrame>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include "mazeboard.h"

class MazeWindow : public QWidget {
  Q_OBJECT

public:
  MazeWindow ();
  ~MazeWindow ();

private:
  MazeBoard *maze_board_;

  QFrame *frame1_;
  QFrame *frame2_;
};

#endif // MAZEWINDOW_H
