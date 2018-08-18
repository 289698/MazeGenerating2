#ifndef MAZEWINDOW_H
#define MAZEWINDOW_H

#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include "game-mechanics.h"

class MazeWindow : public QWidget {
  Q_OBJECT

public:
  MazeWindow ();
  ~MazeWindow ();

protected:
  void paintEvent (QPaintEvent *event);
  void keyPressEvent (QKeyEvent *event);

private:
  GameMechanics *game_ = nullptr;
  QPixmap **block_textures_ = nullptr;
  QPixmap *extra_textures_ = nullptr;
  int tex_res_ = 16;

  bool grid_flag = false, text_flag_ = false;

  void reloadTextures ();
};

#endif // MAZEWINDOW_H
