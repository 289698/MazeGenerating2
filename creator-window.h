#ifndef CREATORWINDOW_H
#define CREATORWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMenuBar>
#include <QToolBar>
#include <QMenu>
#include <QAction>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QDockWidget>
#include <QFrame>

#include "tool-widget.h"
#include "creator-widget.h"

class CreatorWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit CreatorWindow (Textures *textures, QWidget *parent = 0);

public slots:
  void close ();
  void changeToolButtonStyle (Qt::Orientation orientation);
  void createFileDialog ();

signals:
  void closed ();

protected:
  void keyPressEvent (QKeyEvent *event);
  void closeEvent (QCloseEvent *event);

private:
  QDockWidget *tool_dock_widget_;
  ToolWidget *tool_widget_;
  QFrame *canvas_widget_;
  CreatorWidget *creator_widget_;

  QGridLayout *canvas_layout_;

  QMenu *file_menu_, *layers_menu_;
  QToolBar *layers_tool_bar_;
  QAction *new_file_, *open_file_, *save_file_, *save_as_file_, *close_file_, *quit_;
  QAction *logic_view_, *extra_view_, *block_view_, *ground_view_, *back_view_;
  QAction *help_;

};

#endif // CREATORWINDOW_H
