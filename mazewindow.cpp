#include "mazewindow.h"

MazeWindow::MazeWindow () {
  QGridLayout *layout = new QGridLayout;

  font_.setFamily ("Snap ITC");
  font_.setPixelSize (20);
  font_.setStyleHint (QFont::OldEnglish);
  font_.setWeight (QFont::Thin);

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
  maze_board_->setLineWidth (7);
  maze_board_->setStyleSheet ("background-color: #50dd31");
  layout->addWidget (maze_board_, 0, 1, -1, 3);

  layout->addWidget (createLabel (new QLabel, "CHARACTER"), 0, 4, 1, 1, Qt::AlignHCenter);

  QFrame *temp_frame_3 = new QFrame;
  temp_frame_3->setFrameStyle (QFrame::Panel | QFrame::Sunken);
  temp_frame_3->setLineWidth (5);
  layout->addWidget (temp_frame_3, 1, 4, 1, 1);


//  layout->setSpacing (20);
  setLayout (layout);
  setStyleSheet ("background-color: #cc7711");
//  resize (800, 800);
  showMaximized ();
  //    showFullScreen ();
  updateLabels ();
}

void MazeWindow::keyPressEvent (QKeyEvent *event) {
  maze_board_->handleKeyEvent (event);
  updateLabels ();
}

QLabel *MazeWindow::createLabel (QLabel *label, const QString &text) {
  label->setText (text);
  label->setFont (font_);
  label->setStyleSheet ("QLabel { color : darkred; }");
  return label;
}

void MazeWindow::updateLabels () {
  level_text_->setText ("LEVEL: " + QString::number (maze_board_->currentLevel () + 1)
                        + "/" + QString::number (maze_board_->numLevels ()));
  width_text_->setText ("MAZE WIDTH: " + QString::number (maze_board_->mazeWidth ()));
  height_text_->setText ("MAZE HEIGHT: " + QString::number (maze_board_->mazeHeight ()));
  position_text_->setText ("POSITION: " + QString::number (maze_board_->playerPositionX ())
                           + " x " + QString::number (maze_board_->playerPositionY ()));
//  time_text_->setText ();
//  steps_text_->setText ();
}
