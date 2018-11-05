#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QDialog>
#include <QPainter>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QCloseEvent>
#include "game-mechanics.h"

class GameWidget : public QWidget {
  Q_OBJECT

public:
  explicit GameWidget (Textures *textures, QWidget *parent = 0);
  ~GameWidget ();

public slots:
  void close ();

signals:
  void closed (); // flagi z zapisywaniem?

protected:
  void paintEvent (QPaintEvent *event);
  void keyPressEvent (QKeyEvent *event);
  void mousePressEvent (QMouseEvent *event);
  void closeEvent (QCloseEvent *event);

private:
  Textures *const textures_;
  GameMechanics *game_ = nullptr;
  bool grid_flag_ = false, back_flag_ = true, walls_flag_ = true;
};

#endif // GAMEWIDGET_H
