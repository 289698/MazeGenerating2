#ifndef MAZEBOARD_H
#define MAZEBOARD_H

#include <QFrame>
#include <QKeyEvent>
#include <QPainter>
#include <gamemechanics.h>

class MazeBoard : public QFrame {
  Q_OBJECT
public:
  MazeBoard (QWidget *parent = 0);
  ~MazeBoard ();

protected:
  void keyPressEvent (QKeyEvent *event);
  void paintEvent (QPaintEvent *event);

private:
  void drawBorders (QPainter *painter, int x, int y);
  void drawPlayer (QPainter *painter);
  void newGame (int num_levels);
  int grid (int p);
  GameMechanics *game_ = nullptr;
  int maze_size_ = 12;
};

#endif // MAZEBOARD_H
