#ifndef LAUNCHERWIDGET_H
#define LAUNCHERWIDGET_H

#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include "game-widget.h"
#include "creator-window.h"

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
  CreatorWindow *creator_window_ = nullptr;

private slots:
  void newGame ();
  void newCreator ();
  void QWidgetClosed ();

};

#endif // LAUNCHERWIDGET_H
