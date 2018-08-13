#ifndef LEVELBAR_H
#define LEVELBAR_H

#include <QWidget>
#include <QPainter>

class LevelBar : public QWidget {
  Q_OBJECT
public:
  explicit LevelBar (QWidget *parent = 0);
  ~LevelBar ();

protected:
  void paintEvent (QPaintEvent *event);

private:
  QPixmap *background_ = nullptr;
};

#endif // LEVELBAR_H
