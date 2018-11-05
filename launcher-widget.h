#ifndef LAUNCHERWIDGET_H
#define LAUNCHERWIDGET_H

#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include "game-widget.h"

class LauncherWidget : public QWidget {
  Q_OBJECT

public:
  explicit LauncherWidget (QWidget *parent = 0);
  ~LauncherWidget ();

protected:
  void keyPressEvent (QKeyEvent *event);

private:
  Textures *textures_ = nullptr;
  GameWidget *game_widget_ = nullptr;

private slots:
  void newGame ();
  void QWidgetClosed ();

};

#endif // LAUNCHERWIDGET_H
