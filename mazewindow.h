#ifndef MAZEWINDOW_H
#define MAZEWINDOW_H

#include <QLabel>

#include <QGridLayout>
#include "mazeboard.h"

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

  MazeBoard *maze_board_;
  QFont font_;
  QTimer *timer_;
  QLabel *level_text_, *width_text_, *height_text_, *position_text_, *time_text_, *steps_text_;
  int game_time_ = 0;

private slots:
  void tick ();
};

#endif // MAZEWINDOW_H
