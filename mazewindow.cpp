#include "mazewindow.h"

MazeWindow::MazeWindow () {
  QGridLayout *layout = new QGridLayout;

  font_.setFamily ("Digital-7");
//  font_.setFamily ("Snap ITC");
  font_.setPixelSize (40);
  font_.setStyleHint (QFont::OldEnglish);
  font_.setWeight (QFont::Bold);

  layout->addWidget (createLabel (new QLabel, "YOU ARE HERE"), 0, 0, 1, 1, Qt::AlignHCenter);

  QFrame *temp_frame_1 = new QFrame;
  temp_frame_1->setFrameStyle (QFrame::Panel | QFrame::Sunken);
  temp_frame_1->setLineWidth (5);
  layout->addWidget (temp_frame_1, 1, 0, 1, 1);

  level_text_ = new QLabel;
  layout->addWidget (createLabel (level_text_, "LEVEL: XX/XX"), 2, 0, 1, 1, Qt::AlignHCenter);

  width_text_ = new QLabel;
  layout->addWidget (createLabel (width_text_, "MAZE WIDTH: XX"), 3, 0, 1, 1, Qt::AlignHCenter);

  height_text_ = new QLabel;
  layout->addWidget (createLabel (height_text_, "MAZE HEIGHT: XX"), 4, 0, 1, 1, Qt::AlignHCenter);

  position_text_ = new QLabel;
  layout->addWidget (createLabel (position_text_, "POSITION: XX x XX"), 5, 0, 1, 1, Qt::AlignHCenter);

  time_text_ = new QLabel;
  layout->addWidget (createLabel (time_text_, "TIME: XXXX s"), 6, 0, 1, 1, Qt::AlignHCenter);

  steps_text_ = new QLabel;
  layout->addWidget (createLabel (steps_text_, "STEPS: XXXX"), 7, 0, 1, 1, Qt::AlignHCenter);

  maze_board_ = new MazeBoard (this);
  maze_board_->setFrameStyle (QFrame::Panel | QFrame::Sunken);
  maze_board_->setLineWidth (10);
  maze_board_->setFocus ();
  maze_board_->setStyleSheet ("background-color: #c71");
  maze_board_->setFixedSize (800, 800);
  layout->addWidget (maze_board_, 0, 1, -1, 1, Qt::AlignCenter);

  layout->addWidget (createLabel (new QLabel, "CHARACTER"), 0, 2, 1, 1, Qt::AlignHCenter);

  QFrame *temp_frame_3 = new QFrame;
  temp_frame_3->setFrameStyle (QFrame::Panel | QFrame::Sunken);
  temp_frame_3->setLineWidth (5);
  layout->addWidget (temp_frame_3, 1, 2, 1, 1);

//  layout->setSpacing (20);
  setLayout (layout);
  setStyleSheet ("background-color: #c71");
//  resize (800, 800);
  showMaximized ();
//  showFullScreen ();
  updateLabels ();
  timer_ = new QTimer;
  connect (timer_, SIGNAL (timeout ()), this, SLOT(tick ()));
  timer_->start (100);
}

void MazeWindow::tick () {
  game_time_ += 100;
  updateLabels ();
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
  label->setFont (font_);
  label->setStyleSheet ("QLabel { color : darkred; }");
  return label;
}

void MazeWindow::updateLabels () {
  level_text_->setText (QString ("LEVEL: %1 / %2").arg (maze_board_->currentLevel () + 1)
                        .arg(maze_board_->numLevels ()));
  width_text_->setText (QString ("MAZE WIDTH: %1").arg (maze_board_->mazeWidth ()));
  height_text_->setText (QString ("MAZE HEIGHT: %1").arg (maze_board_->mazeHeight ()));
  position_text_->setText (QString ("POSITION: %1 x %2").arg (maze_board_->playerPositionX ())
                           .arg (maze_board_->playerPositionY ()));
  time_text_->setText (QString ("TIME: %1 s").arg (game_time_ / 1000.0, 2, 'f', 1));
  steps_text_->setText (QString ("STEPS: %1").arg (maze_board_->playerSteps ()));
}
