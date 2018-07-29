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
  void drawBorders (QPainter *painter);
  void adjustElementsSize ();
  void newQPolygonFs ();
  void deleteQPolygonFs ();

  GameMechanics *game_ = nullptr;
  qreal maze_size_ = 0;
  int pix_x_ = 0, pix_y_ = 0;

  QPolygonF *wall_main_corner_ = nullptr, *wall_shadow_corner_ = nullptr,
  *wall_main_vertical_ = nullptr, *wall_shadow_vertical_ = nullptr,
  *wall_main_horizontal_ = nullptr, *wall_shadow_horizontal_ = nullptr,
  *wall_main_empty_ = nullptr, *wall_shadow_empty_ = nullptr;

  QImage player_icon_;
  QTransform player_rotation_;
};

#endif // MAZEBOARD_H
