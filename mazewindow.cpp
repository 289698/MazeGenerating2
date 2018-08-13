#include "mazewindow.h"

MazeWindow::MazeWindow () {
  showFullScreen ();
  setStyleSheet ("background-color: #222");

//  font_.setFamily ("Digital-7");
//  font_.setFamily ("Snap ITC");
//  font_.setPixelSize (40);
//  font_.setStyleHint (QFont::OldEnglish);
//  font_.setWeight (QFont::Bold);
//  QFrame *temp_frame_3 = new QFrame;
//  temp_frame_3->setFrameStyle (QFrame::Panel | QFrame::Sunken);
//  temp_frame_3->setLineWidth (5);
//  temp_frame_3->setStyleSheet ("background-color: #888");
//  layout->addWidget (temp_frame_3, 0, 1);
//  updateLabels ();
//  timer_ = new QTimer;
//  connect (timer_, SIGNAL (timeout ()), this, SLOT (tick ()));
//  timer_->start (100);

  QGridLayout *layout = new QGridLayout;
  layout->setMargin (0);
  layout->setSpacing (10);

  maze_board_ = new MazeBoard (this->width (), this->height (), this);
  maze_board_->setFocus ();
  layout->addWidget (maze_board_);

  level_bar_ = new LevelBar ();
  level_bar_->setFocusPolicy (Qt::NoFocus);
  layout->addWidget (level_bar_, 0, 0, Qt::AlignTop | Qt::AlignHCenter);

  setLayout (layout);
}

void MazeWindow::tick () {
  game_time_ += 100;
//  updateLabels ();
}

MazeWindow::~MazeWindow () {
  if (timer_ != nullptr)
    delete timer_;
}

void MazeWindow::keyPressEvent (QKeyEvent *event) {
  maze_board_->handleKeyEvent (event);
}

QLabel *MazeWindow::createLabel (QLabel *label, const QString &text) {
  label->setText (text);
  label->setFont (*font_);
  label->setStyleSheet ("QLabel { color : darkred; }");
  return label;
}

//void MazeWindow::updateLabels () {
//  level_text_->setText (QString ("LEVEL: %1 / %2").arg (maze_board_->currentLevel () + 1)
//                        .arg(maze_board_->numLevels ()));
//  width_text_->setText (QString ("MAZE WIDTH: %1").arg (maze_board_->mazeWidth ()));
//  height_text_->setText (QString ("MAZE HEIGHT: %1").arg (maze_board_->mazeHeight ()));
//  position_text_->setText (QString ("POSITION: %1 x %2").arg (maze_board_->playerPositionX ())
//                           .arg (maze_board_->playerPositionY ()));
//  time_text_->setText (QString ("TIME: %1 s").arg (game_time_ / 1000.0, 2, 'f', 1));
//  steps_text_->setText (QString ("STEPS: %1").arg (maze_board_->playerSteps ()));
//}
