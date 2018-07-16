#include "mazewindow.h"

MazeWindow::MazeWindow () {
  maze_board_ = new MazeBoard (this);
  //maze_board_->setLineWidth(2);
  QGridLayout *layout = new QGridLayout;
  layout->addWidget (maze_board_, 0, 0);
//  QPushButton *button = new QPushButton ("PUSH ME");
//  layout->addWidget (button, 0, 0);
//  QPushButton *button2 = new QPushButton ("PUSH ME 2");
//  layout->addWidget (button2, 1, 0);
//  QFrame *frame1 = new QFrame;
//  frame1->setFrameStyle(QFrame::Panel | QFrame::Sunken);
//  layout->addWidget(frame1, 1, 0);
  setLayout (layout);
  resize (800, 800);
}

MazeWindow::~MazeWindow () {

}
