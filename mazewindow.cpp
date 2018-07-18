#include "mazewindow.h"

MazeWindow::MazeWindow () {
  maze_board_ = new MazeBoard (this);
  frame1_ = new QFrame;
  frame1_->setFrameStyle (QFrame::Panel | QFrame::Sunken);
  frame1_->setLineWidth (5);
  frame2_ = new QFrame;
  frame2_->setFrameStyle (QFrame::Panel | QFrame::Sunken);
  frame2_->setLineWidth (5);

  QGridLayout *layout = new QGridLayout;
  layout->addWidget (frame1_, 0, 0);
  layout->addWidget (maze_board_, 0, 1, -1, 4);
  layout->addWidget (frame2_, 0, 6);
  setLayout (layout);
  //resize (800, 800);
  showMaximized ();
  //showFullScreen ();
}

MazeWindow::~MazeWindow () {
  delete maze_board_;
  delete frame1_;
  delete frame2_;
}
