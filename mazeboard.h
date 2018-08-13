#ifndef MAZEBOARD_H
#define MAZEBOARD_H

#include <QFrame>
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <gamemechanics.h>

class MazeBoard : public QWidget {
  Q_OBJECT
public:
  MazeBoard (int vision_width, int vision_height, QWidget *parent = 0);
  ~MazeBoard ();

  void handleKeyEvent (QKeyEvent *event);

  inline int mazeWidth () const { return game_->mazeWidth (); }
  inline int mazeHeight () const { return game_->mazeHeight (); }
  inline int playerPositionX () const { return game_->playerPositionX (); }
  inline int playerPositionY () const { return game_->playerPositionY (); }
  inline int numLevels () const { return game_->numLevels (); }
  inline int currentLevel () const { return game_->currentLevel (); }
  inline int playerSteps () const { return playerSteps_; }

  void setVisionWidth (int vision_width);
  void setVisionHeight (int vision_height);

protected:
  void paintEvent (QPaintEvent *event);

private:
  void newGame (int num_levels);
  void redrawMaze();
  void reloadTextures ();

  QTimer *timer_ = nullptr;
  GameMechanics *game_ = nullptr;
  int textures_res_ = 128, vision_width_ = 19, vision_height_ = 10, playerSteps_ = 0;
  bool is_antialiasing_= true;

  QPixmap *whole_maze_ = nullptr, *maze_square_ = nullptr, *start_icon_ = nullptr, *end_icon_ = nullptr,
  *background_ = nullptr, *player_icon_ = nullptr;
  QTransform player_rotation_;

};

#endif // MAZEBOARD_H
