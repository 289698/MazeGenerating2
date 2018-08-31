#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QDialog>
#include <QPainter>
#include <QKeyEvent>
#include <QCloseEvent>
#include "textures.h"
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
  void closeEvent (QCloseEvent *event);

private:
  void redrawBackLayer ();
  void redrawGroundLayer ();
  void redrawBlockLayer ();
  void redrawExtraLayer ();
  Textures *const textures_;
  GameMechanics *game_ = nullptr;
  QPixmap *back_layer_ = nullptr;
  QPixmap *ground_layer_ = nullptr;
  QPixmap *block_layer_ = nullptr;
  QPixmap *extra_layer_ = nullptr;

  bool grid_flag = false, text_flag_ = false;
};

#endif // GAMEWIDGET_H
