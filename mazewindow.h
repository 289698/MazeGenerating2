#ifndef MAZEWINDOW_H
#define MAZEWINDOW_H

#include <QLabel>

#include <QGridLayout>
#include "mazeboard.h"
#include "levelbar.h"

class MazeWindow : public QWidget {
  Q_OBJECT

public:
  MazeWindow ();
  ~MazeWindow ();

protected:
  void keyPressEvent (QKeyEvent *event);

private:
  void updateLabels ();
  QLabel *createLabel (QLabel *label, const QString &text);

  MazeBoard *maze_board_ = nullptr;
  LevelBar *level_bar_ = nullptr;
  QFont *font_ = nullptr;
  QTimer *timer_ = nullptr;
  int game_time_ = 0;

private slots:
  void tick ();
};

#endif // MAZEWINDOW_H
