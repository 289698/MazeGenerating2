#ifndef MAZEWINDOW_H
#define MAZEWINDOW_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QSpinBox>
#include <QLCDNumber>
#include <QSlider>

#include <QGridLayout>
#include <QWidget>
#include <QString>
#include "mazeboard.h"

class MazeWindow : public QWidget {
  Q_OBJECT

public:
  MazeWindow ();

protected:
  void keyPressEvent (QKeyEvent *event);

private:
  void updateLabels ();
  QLabel *createLabel (QLabel *label, const QString &text);

  MazeBoard *maze_board_;
  QFont font_;
  QLabel *level_text_, *width_text_, *height_text_, *position_text_, *time_text_, *steps_text_;
};

#endif // MAZEWINDOW_H
