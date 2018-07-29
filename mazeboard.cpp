#include "mazeboard.h"

MazeBoard::MazeBoard (QWidget *parent) : QFrame (parent) {
  game_ = new GameMechanics (10, Size {13, 13}, 1); // ma pobierać z widgetów
  //  setFixedSize (500, 500);
  player_icon_.load ("firetruck.png");
}

MazeBoard::~MazeBoard () {
  if (game_ != nullptr)
    delete game_;
  deleteQPolygonFs ();
}

void MazeBoard::newGame (int num_levels) {
  if (game_ != nullptr)
    delete game_;
  game_ = new GameMechanics (num_levels, Size {13, 13}, 1); // ma pobierać z widgetów
}

void MazeBoard::handleKeyEvent (QKeyEvent *event) {
  switch (event->key ()) {
    case Qt::Key_W:
      game_->tryMove (direction::kUp);
      player_rotation_.reset ();
      player_rotation_.rotate (0);
      break;
    case Qt::Key_D:
      game_->tryMove (direction::kRight);
      player_rotation_.reset ();
      player_rotation_.rotate (90);
      break;
    case Qt::Key_S:
      game_->tryMove (direction::kDown);
      player_rotation_.reset ();
      player_rotation_.rotate (180);
      break;
    case Qt::Key_A:
      game_->tryMove (direction::kLeft);
      player_rotation_.reset ();
      player_rotation_.rotate (270);
      break;
    case Qt::Key_E:
      game_->tryEnter ();
      break;
    case Qt::Key_QuoteLeft:
      game_->toogleGodMode ();
      break;
    case Qt::Key_Escape:
      exit (0);
      //    default:
      //      qDebug() << event;
  }
  if (game_->isGod ()) {
    switch (event->key ()) {
      case Qt::Key_Right:
        game_->nextLevel ();
        break;
      case Qt::Key_Left:
        game_->previousLevel ();
        break;
      case Qt::Key_O:
        game_->jumpToStart ();
        break;
      case Qt::Key_P:
        game_->jumpToEnd ();
        break;
      case Qt::Key_G:
        newGame (10);
        update ();
        break;
    }
  }
  update ();
}

void MazeBoard::paintEvent(QPaintEvent *event) {
  QFrame::paintEvent (event);
  QPainter painter (this);
  painter.setRenderHint (QPainter::Antialiasing);
  adjustElementsSize ();

  //  painter.setPen (QColor (90, 40, 10));
  painter.setPen (Qt::NoPen);

  painter.setBrush (QColor (190, 120, 20));
  painter.drawRect (pix_x_ - maze_size_ * 3, pix_y_ - maze_size_ * 3,
                    (game_->mazeWidth () + 2.0) * 6.0 * maze_size_,
                    (game_->mazeHeight() + 2.0) * 6.0 * maze_size_);
  painter.setBrush (QColor (220, 150, 10));
  painter.drawRect (pix_x_ + maze_size_ * 3, pix_y_ + maze_size_ * 3,
                    game_->mazeWidth () * 6.0 * maze_size_, game_->mazeHeight() * 6.0 * maze_size_);
  drawBorders (&painter);

  painter.setPen (Qt::black);
  //  painter.drawEllipse (pix_x_ + ((game_->playerPositionX () + 0.5) * 6.0 + 1) * maze_size_,
  //                       pix_y_ + ((game_->playerPositionY () + 0.5) * 6.0 + 1) * maze_size_,
  //                       2, 2);
  painter.drawImage (QRectF (pix_x_ + ((game_->playerPositionX () + 0.5) * 6.0 + 1) * maze_size_,
                             pix_y_ + ((game_->playerPositionY () + 0.5) * 6.0 + 1) * maze_size_,
                             maze_size_ * 4.0, maze_size_ * 4.0),
                     player_icon_.transformed (player_rotation_));
}

void MazeBoard::drawBorders (QPainter *painter) {
  int corner_side [] = {square::kUp, square::kRight, square::kDown, square::kLeft, square::kUp};
  qreal pix_x = pix_x_;
  for (int x = -1; x <= game_->mazeWidth (); ++ x, pix_x += maze_size_ * 6.0) {
    qreal pix_y = pix_y_;
    for (int y = -1; y <= game_->mazeHeight (); ++ y, pix_y += maze_size_ * 6.0) {
      for (int i = 0; i < 4; ++ i) {
        int corner_info = game_->at (x, y) & (corner_side [i] + corner_side [i + 1]);
        QTransform transform;
        transform.translate (pix_x, pix_y).rotate (90 * i);
        if (corner_info == corner_side [i] + corner_side [i + 1]) {
          painter->setBrush (QColor (210, 130, 20));
          painter->drawPolygon (transform.map (*wall_main_corner_));
          painter->setBrush (QColor (160, 100, 10));
          painter->drawPolygon (transform.map (*wall_shadow_corner_));
        } else if (corner_info == corner_side [i]) {
          painter->setBrush (QColor (210, 130, 20));
          painter->drawPolygon (transform.map (*wall_main_horizontal_));
          painter->setBrush (QColor (160, 100, 10));
          painter->drawPolygon (transform.map (*wall_shadow_horizontal_));
        } else if (corner_info == corner_side [i + 1]) {
          painter->setBrush (QColor (210, 130, 20));
          painter->drawPolygon (transform.map (*wall_main_vertical_));
          painter->setBrush (QColor (160, 100, 10));
          painter->drawPolygon (transform.map (*wall_shadow_vertical_));
        } else if (corner_info == square::kEmpty) {
          painter->setBrush (QColor (210, 130, 20));
          painter->drawPolygon (transform.map (*wall_main_empty_));
          painter->setBrush (QColor (160, 100, 10));
          painter->drawPolygon (transform.map (*wall_shadow_empty_));
        } // if end
      } // for (i) end
    } // for (y) end
  } // for (x) end
} // function end

void MazeBoard::adjustElementsSize () {
  qDebug () << "wow";

  if (this->width () - 50 < this->height () - 50) {
    maze_size_ = (this->width () - 50.0) / (game_->mazeWidth () + 2.0) / 6.0;
    pix_x_ = maze_size_ * 3.0 + 25;
    pix_y_ = this->height () / 2.0 - (2.0 + (game_->mazeHeight ()) * 3.0 + 1.0) * maze_size_;
  }
  else {
    maze_size_ = (this->height () - 50.0) / (game_->mazeWidth () + 2.0) / 6.0;
    pix_x_ = this->width () / 2.0 - (2.0 + (game_->mazeWidth ()) * 3.0 + 1.0) * maze_size_;
    pix_y_ = maze_size_ * 3.0 + 25;
  }

  deleteQPolygonFs (); newQPolygonFs ();
  const qreal size_4_0 = maze_size_ * 2.0,
      size_4_5 = maze_size_ * 2.5,
      size_5_0 = maze_size_ * 3.0;
  *wall_main_corner_ << QPointF (0.0, - size_5_0)
                     << QPointF (size_5_0, - size_5_0)
                     << QPointF (size_5_0, 0.0)
                     << QPointF (size_4_5, 0.0)
                     << QPointF (size_4_5, - size_4_5)
                     << QPointF (0.0, - size_4_5);
  *wall_shadow_corner_ << QPointF (0.0, - size_4_5)
                       << QPointF (size_4_5, - size_4_5)
                       << QPointF (size_4_5, 0.0)
                       << QPointF (size_4_0, 0.0)
                       << QPointF (size_4_0, - size_4_0)
                       << QPointF (0.0, - size_4_0);
  *wall_main_vertical_ << QPointF (size_4_5, - size_5_0)
                       << QPointF (size_5_0, - size_5_0)
                       << QPointF (size_5_0, 0.0)
                       << QPointF (size_4_5, 0.0);
  *wall_shadow_vertical_ << QPointF (size_4_0, - size_5_0)
                         << QPointF (size_4_5, - size_5_0)
                         << QPointF (size_4_5, 0.0)
                         << QPointF (size_4_0, 0.0);
  *wall_main_horizontal_ << QPointF (0.0, - size_5_0)
                         << QPointF (size_5_0, - size_5_0)
                         << QPointF (size_5_0, - size_4_5)
                         << QPointF (0.0, - size_4_5);
  *wall_shadow_horizontal_ << QPointF (0.0, - size_4_5)
                           << QPointF (size_5_0, - size_4_5)
                           << QPointF (size_5_0, - size_4_0)
                           << QPointF (0.0, - size_4_0);
  *wall_main_empty_ << QPointF (size_4_5, - size_5_0)
                    << QPointF (size_5_0, - size_5_0)
                    << QPointF (size_5_0, - size_4_5)
                    << QPointF (size_4_5, - size_4_5);
  *wall_shadow_empty_ << QPointF (size_4_0, - size_5_0)
                      << QPointF (size_4_5, - size_5_0)
                      << QPointF (size_4_5, - size_4_5)
                      << QPointF (size_5_0, - size_4_5)
                      << QPointF (size_5_0, - size_4_0)
                      << QPointF (size_4_0, - size_4_0);
}

void MazeBoard::newQPolygonFs () {
  wall_main_corner_ = new QPolygonF;
  wall_shadow_corner_ = new QPolygonF;
  wall_main_vertical_ = new QPolygonF;
  wall_shadow_vertical_ = new QPolygonF;
  wall_main_horizontal_ = new QPolygonF;
  wall_shadow_horizontal_ = new QPolygonF;
  wall_main_empty_ = new QPolygonF;
  wall_shadow_empty_ = new QPolygonF;
}

void MazeBoard::deleteQPolygonFs () {
  if (wall_main_corner_ != nullptr) {
    delete wall_main_corner_;
    wall_main_corner_ = nullptr;
  }
  if (wall_shadow_corner_ != nullptr) {
    delete wall_shadow_corner_;
    wall_shadow_corner_ = nullptr;
  }
  if (wall_main_vertical_ != nullptr) {
    delete wall_main_vertical_;
    wall_main_vertical_ = nullptr;
  }
  if (wall_shadow_vertical_ != nullptr) {
    delete wall_shadow_vertical_;
    wall_shadow_vertical_ = nullptr;
  }
  if (wall_main_horizontal_ != nullptr) {
    delete wall_main_horizontal_;
    wall_main_horizontal_ = nullptr;
  }
  if (wall_shadow_horizontal_ != nullptr) {
    delete wall_shadow_horizontal_;
    wall_shadow_horizontal_ = nullptr;
  }
  if (wall_main_empty_ != nullptr) {
    delete wall_main_empty_;
    wall_main_empty_ = nullptr;
  }
  if (wall_shadow_empty_ != nullptr) {
    delete wall_shadow_empty_;
    wall_shadow_empty_ = nullptr;
  }
}
