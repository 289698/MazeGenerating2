#include "launcher-widget.h"
#include <QApplication>

int main (int argc, char *argv[]) {

  srand (time (0));
  QApplication a (argc, argv);
  LauncherWidget w;
  w.show ();

  return a.exec ();
}
