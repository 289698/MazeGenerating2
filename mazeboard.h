#ifndef MAZEBOARD_H
#define MAZEBOARD_H

#include <QFrame>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <gamemechanics.h>

class MazeBoard : public QFrame {
  Q_OBJECT
public:
  MazeBoard (QWidget *parent = 0);
  ~MazeBoard ();

  void handleKeyEvent (QKeyEvent *event);

  inline int mazeWidth () const { return game_->mazeWidth (); }
  inline int mazeHeight () const { return game_->mazeHeight (); }
  inline int playerPositionX () const { return game_->playerPositionX (); }
  inline int playerPositionY () const { return game_->playerPositionY (); }
  inline int numLevels () const { return game_->numLevels (); }
  inline int currentLevel () const { return game_->currentLevel (); }

protected:
  void paintEvent (QPaintEvent *event);

private:
  void newGame (int num_levels);
  void reloadTextures ();

  QTimer *timer = nullptr;
  GameMechanics *game_ = nullptr;
  int texture_resolution_ = 64, maze_size_, margin_x_, margin_y_;
  bool is_antialiasing_= false;

  QImage /**maze_ = nullptr, */*maze_square_ = nullptr, *player_icon_ = nullptr;
  QTransform player_rotation_;

  double angle_ = 0;

private slots:
  void increaseAngle () { angle_ = (angle_ + 0.2); update (); }
};

#endif // MAZEBOARD_H
