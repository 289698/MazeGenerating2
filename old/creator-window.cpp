#include "creator-window.h"

CreatorWindow::CreatorWindow (Textures *textures, QWidget *parent) : QMainWindow (parent) {
  tool_dock_widget_ = new QDockWidget ("Tool Dock Window", this);
  tool_widget_ = new ToolWidget (tool_dock_widget_);
  canvas_widget_ = new QFrame (this);
  canvas_layout_ = new QGridLayout (canvas_widget_);
  creator_widget_ = new CreatorWidget (textures, tool_widget_, canvas_widget_);

  file_menu_ = menuBar ()->addMenu ("Map File");
  new_file_ = file_menu_->addAction ("New...");
  open_file_ = file_menu_->addAction ("Open...");
  file_menu_->addSeparator ();
  save_file_ = file_menu_->addAction ("Save");
  save_as_file_ = file_menu_->addAction ("Save as...");
  file_menu_->addSeparator ();
  close_file_ = file_menu_->addAction ("Close map");
  quit_ = file_menu_->addAction ("Quit Creator");
  layers_menu_ = menuBar ()->addMenu ("Layer View");
  logic_view_ = layers_menu_->addAction ("Logic layer");
  extra_view_ = layers_menu_->addAction ("Extra layer");
  block_view_ = layers_menu_->addAction ("Block layer");
  ground_view_ = layers_menu_->addAction ("Ground layer");
  back_view_ = layers_menu_->addAction ("Background layer");
  help_ = menuBar ()->addAction ("Help");

  layers_tool_bar_ = this->addToolBar ("Layers Tool Bar");
  layers_tool_bar_->setToolButtonStyle (Qt::ToolButtonTextBesideIcon);
  layers_tool_bar_->addAction (logic_view_);
  layers_tool_bar_->addAction (extra_view_);
  layers_tool_bar_->addAction (block_view_);
  layers_tool_bar_->addAction (ground_view_);
  layers_tool_bar_->addAction (back_view_);

  tool_dock_widget_->setFocusPolicy (Qt::NoFocus);
  tool_dock_widget_->setAllowedAreas (Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  tool_dock_widget_->setWidget (tool_widget_);

  canvas_layout_->addWidget (creator_widget_, 0, 0);
  canvas_widget_->setLayout (canvas_layout_);
  canvas_widget_->setFrameStyle (QFrame::Panel | QFrame::Raised);
  canvas_widget_->setLineWidth (10);
  creator_widget_->setFocusPolicy (Qt::NoFocus);

  logic_view_->setCheckable (false);
  logic_view_->setChecked (false);
  logic_view_->setIcon (QIcon (":/creator_icons/logic-layer.png"));
  extra_view_->setCheckable (true);
  extra_view_->setChecked (true);
  extra_view_->setIcon (QIcon (":/creator_icons/extra-layer.png"));
  block_view_->setCheckable (true);
  block_view_->setChecked (true);
  block_view_->setIcon (QIcon (":/creator_icons/block-layer.png"));
  ground_view_->setCheckable (true);
  ground_view_->setChecked (true);
  ground_view_->setIcon (QIcon (":/creator_icons/ground-layer.png"));
  back_view_->setCheckable (true);
  back_view_->setChecked (true);
  back_view_->setIcon (QIcon (":/creator_icons/back-layer.png"));

  this->addDockWidget (Qt::RightDockWidgetArea, tool_dock_widget_);
  this->setCentralWidget (canvas_widget_);
  this->setAttribute (Qt::WA_DeleteOnClose);

  connect (tool_widget_->drawing_radio_, SIGNAL (clicked ()),
           creator_widget_, SLOT (setDrawingTool ()));
  connect (tool_widget_->shaping_radio_, SIGNAL (clicked ()),
           creator_widget_, SLOT (setShapingTool ()));
  connect (tool_widget_->painting_radio_, SIGNAL (clicked ()),
           creator_widget_, SLOT (setPaintingTool ()));
  connect (tool_widget_->erasing_radio_, SIGNAL (clicked ()),
           creator_widget_, SLOT (setErasingTool ()));

  connect (tool_widget_->extra_item_combo_, SIGNAL (currentIndexChanged(int)),
           creator_widget_, SLOT (setToolExtra (int)));
  connect (tool_widget_->block_shape_combo_, SIGNAL (currentIndexChanged(int)),
           creator_widget_, SLOT (setToolBlock (int)));
  connect (tool_widget_->block_color_combo_, SIGNAL (currentIndexChanged(int)),
           creator_widget_, SLOT (setToolBlockColor (int)));
  connect (tool_widget_->ground_shape_combo_, SIGNAL (currentIndexChanged(int)),
           creator_widget_, SLOT (setToolGround (int)));
  connect (tool_widget_->ground_color_combo_, SIGNAL (currentIndexChanged(int)),
           creator_widget_, SLOT (setToolGroundColor (int)));
  connect (tool_widget_->back_color_combo_, SIGNAL (currentIndexChanged(int)),
           creator_widget_, SLOT (setToolBackColor (int)));

  connect (tool_widget_->logic_box_, SIGNAL (toggled (bool)),
           creator_widget_, SLOT (toggleLogicEditing (bool)));
  connect (tool_widget_->extra_box_, SIGNAL (toggled (bool)),
           creator_widget_, SLOT (toggleExtraEditing (bool)));
  connect (tool_widget_->block_box_, SIGNAL (toggled (bool)),
           creator_widget_, SLOT (toggleBlockEditing (bool)));
  connect (tool_widget_->ground_box_, SIGNAL (toggled (bool)),
           creator_widget_, SLOT (toggleGroundEditing (bool)));
  connect (tool_widget_->back_box_, SIGNAL (toggled (bool)),
           creator_widget_, SLOT (toggleBackEditing (bool)));

  connect (this->new_file_, SIGNAL (triggered ()),
           creator_widget_, SLOT (newMap ()));
  connect (this->open_file_, SIGNAL (triggered ()),
           this, SLOT (createFileDialog ()));
  connect (this->quit_, SIGNAL (triggered ()),
           this, SLOT (close ()));
  connect (this->layers_tool_bar_, SIGNAL (orientationChanged (Qt::Orientation)),
           this, SLOT (changeToolButtonStyle (Qt::Orientation)));
  connect (this->logic_view_, SIGNAL (toggled (bool)),
           creator_widget_, SLOT (toggleLogicVisibility (bool)));
  connect (this->extra_view_, SIGNAL (toggled (bool)),
           creator_widget_, SLOT (toggleExtraVisibility (bool)));
  connect (this->block_view_, SIGNAL (toggled (bool)),
           creator_widget_, SLOT (toggleBlockVisibility (bool)));
  connect (this->ground_view_, SIGNAL (toggled (bool)),
           creator_widget_, SLOT (toggleGroundVisibility (bool)));
  connect (this->back_view_, SIGNAL (toggled (bool)),
           creator_widget_, SLOT (toggleBackVisibility (bool)));
}

void CreatorWindow::close () {
  QMainWindow::close ();
  emit closed ();
}

void CreatorWindow::changeToolButtonStyle (Qt::Orientation orientation) {
  switch (orientation) {
    case Qt::Horizontal:
      layers_tool_bar_->setToolButtonStyle (Qt::ToolButtonTextBesideIcon);
      break;
    case Qt::Vertical:
      layers_tool_bar_->setToolButtonStyle (Qt::ToolButtonIconOnly);
      break;
  }
}

void CreatorWindow::createFileDialog () {
  QFileDialog *file_dialog = new QFileDialog (this, "Open Game Map to edit (*.json file)",
                                              "C:/Users/kamil/Documents/My Games/Terraria", "JSON Files (*.json)");
  file_dialog->setAcceptMode (QFileDialog::AcceptSave);
  file_dialog->exec ();
  delete file_dialog;
}

void CreatorWindow::keyPressEvent (QKeyEvent *event) {
  switch (event->key ()) {
    case Qt::Key_G:
      creator_widget_->toggleGrid ();
      break;
    case Qt::Key_PageUp:
      creator_widget_->zoomIn ();
      break;
    case Qt::Key_PageDown:
      creator_widget_->zoomOut ();
      break;
    case Qt::Key_Home:
      creator_widget_->zoomReset ();
      break;
    case Qt::Key_Escape:
      this->close ();
      return;
  }
}

void CreatorWindow::closeEvent (QCloseEvent *event) {
  QMainWindow::closeEvent (event);
  emit closed ();
}
