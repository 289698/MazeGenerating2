#include "tool-widget.h"

ToolWidget::ToolWidget (QWidget *parent) : QWidget (parent) {
  main_layout_ = new QVBoxLayout (this);
  tools_box_ = new QGroupBox ("Tools", this);
  tools_layout_ = new QGridLayout (tools_box_);
  drawing_radio_ = new QRadioButton (tools_box_);
  shaping_radio_ = new QRadioButton (tools_box_);
  painting_radio_ = new QRadioButton (tools_box_);
  erasing_radio_ = new QRadioButton (tools_box_);
  createGroupBox (logic_box_, "Logic", logic_layout_);
  logic_obstacle_check_ = new QCheckBox ("Obstacle", logic_box_);
  createGroupBox (extra_box_, "Extras", extra_layout_);
  extra_item_label_ = new QLabel ("Item:", extra_box_);
  extra_item_combo_ = new QComboBox (extra_box_);
  createGroupBox (block_box_, "Blocks", block_layout_);
  block_color_label_ = new QLabel ("Color:", block_box_);
  block_color_combo_ = new QComboBox (block_box_);
  block_shape_label_ = new QLabel ("Shape:", block_box_);
  block_shape_combo_ = new QComboBox (block_box_);
  createGroupBox (ground_box_, "Ground", ground_layout_);
  ground_color_label_ = new QLabel ("Color:", ground_box_);
  ground_color_combo_ = new QComboBox (ground_box_);
  ground_shape_label_ = new QLabel ("Shape:", ground_box_);
  ground_shape_combo_ = new QComboBox (ground_box_);
  createGroupBox (back_box_, "Background", back_layout_);
  back_color_label_ = new QLabel ("Color:", back_box_);
  back_color_combo_ = new QComboBox (back_box_);

  drawing_radio_->setChecked (true);
  drawing_radio_->setToolTip ("Drawer\n- overwrites everything");
  drawing_radio_->setIcon (QIcon (":/creator_icons/drawer.png"));
  drawing_radio_->setIconSize (QSize (32, 32));
  drawing_radio_->setCursor (Qt::PointingHandCursor);
  shaping_radio_->setToolTip ("Shaper\n- changes only shape");
  shaping_radio_->setIcon (QIcon (":/creator_icons/shaper.png"));
  shaping_radio_->setIconSize (QSize (32, 32));
  shaping_radio_->setCursor (Qt::PointingHandCursor);
  painting_radio_->setToolTip ("Painter\n- changes only color");
  painting_radio_->setIcon (QIcon (":/creator_icons/painter.png"));
  painting_radio_->setIconSize (QSize (32, 32));
  painting_radio_->setCursor (Qt::PointingHandCursor);
  erasing_radio_->setToolTip ("Eraser\n- erases everything");
  erasing_radio_->setIcon (QIcon (":/creator_icons/eraser.png"));
  erasing_radio_->setIconSize (QSize (32, 32));
  erasing_radio_->setCursor (Qt::PointingHandCursor);
  for (int i = 0; i < mapField::extra::NumVariations; ++ i)
    extra_item_combo_->addItem (QIcon (":/creator_icons/pencil.png"), "[ #" + QString::number (i) + " ]");
  extra_item_combo_->setCursor (Qt::PointingHandCursor);
  extra_item_combo_->setFixedWidth (100);
  for (int i = 0; i < mapField::color::NumVariations; ++ i)
    block_color_combo_->addItem (QIcon (":/creator_icons/pencil.png"), "[ #" + QString::number (i) + " ]"); // może lista z nazwami?
  block_color_combo_->setCursor (Qt::PointingHandCursor);
  block_color_combo_->setFixedWidth (100);
  for (int i = 0; i < mapField::block::NumVariations; ++ i)
    block_shape_combo_->addItem (QIcon (":/creator_icons/pencil.png"), "[ #" + QString::number (i) + " ]");
  block_shape_combo_->setCursor (Qt::PointingHandCursor);
  block_shape_combo_->setFixedWidth (100);
  for (int i = 0; i < mapField::color::NumVariations; ++ i)
    ground_color_combo_->addItem (QIcon (":/creator_icons/pencil.png"), "[ #" + QString::number (i) + " ]");
  ground_color_combo_->setCursor (Qt::PointingHandCursor);
  ground_color_combo_->setFixedWidth (100);
  for (int i = 0; i < mapField::ground::NumVariations; ++ i)
    ground_shape_combo_->addItem (QIcon (":/creator_icons/pencil.png"), "[ #" + QString::number (i) + " ]");
  ground_shape_combo_->setCursor (Qt::PointingHandCursor);
  ground_shape_combo_->setFixedWidth (100);
  for (int i = 0; i < mapField::color::NumVariations; ++ i)
    back_color_combo_->addItem (QIcon (":/creator_icons/pencil.png"), "[ #" + QString::number (i) + " ]");
  back_color_combo_->setCursor (Qt::PointingHandCursor);
  back_color_combo_->setFixedWidth (100);

  tools_layout_->addWidget (drawing_radio_, 0, 0);
  tools_layout_->addWidget (shaping_radio_, 0, 1);
  tools_layout_->addWidget (painting_radio_, 1, 0);
  tools_layout_->addWidget (erasing_radio_, 1, 1);
  logic_layout_->addWidget (logic_obstacle_check_, 0, 0);
  extra_layout_->addWidget (extra_item_label_, 0, 0, Qt::AlignLeft);
  extra_layout_->addWidget (extra_item_combo_, 0, 1, Qt::AlignRight);
  block_layout_->addWidget (block_color_label_, 0, 0, Qt::AlignLeft);
  block_layout_->addWidget (block_color_combo_, 0, 1, Qt::AlignRight);
  block_layout_->addWidget (block_shape_label_, 1, 0, Qt::AlignLeft);
  block_layout_->addWidget (block_shape_combo_, 1, 1, Qt::AlignRight);
  ground_layout_->addWidget (ground_color_label_, 0, 0, Qt::AlignLeft);
  ground_layout_->addWidget (ground_color_combo_, 0, 1, Qt::AlignRight);
  ground_layout_->addWidget (ground_shape_label_, 1, 0, Qt::AlignLeft);
  ground_layout_->addWidget (ground_shape_combo_, 1, 1, Qt::AlignRight);
  back_layout_->addWidget (back_color_label_, 0, 0, Qt::AlignLeft);
  back_layout_->addWidget (back_color_combo_, 0, 1, Qt::AlignRight);
  main_layout_->addWidget (tools_box_);
  main_layout_->addSpacing (40);
  main_layout_->addWidget (logic_box_);
  main_layout_->addWidget (extra_box_);
  main_layout_->addWidget (block_box_);
  main_layout_->addWidget (ground_box_);
  main_layout_->addWidget (back_box_);

  this->setLayout (main_layout_);
  this->setSizePolicy (QSizePolicy::Fixed, QSizePolicy::Fixed);
  this->setFixedWidth (180);
  this->setContentsMargins (0, 0, 0, 0);

  connect (drawing_radio_, SIGNAL (clicked ()), this, SLOT (setDrawingScheme ()));
  connect (shaping_radio_, SIGNAL (clicked ()), this, SLOT (setShapingScheme ()));
  connect (painting_radio_, SIGNAL (clicked ()), this, SLOT (setPaintingScheme ()));
  connect (erasing_radio_, SIGNAL (clicked ()), this, SLOT (setErasingScheme ()));

  //--------------TEMP--------------
  logic_box_->setEnabled (false);
  logic_box_->setChecked (false);
  logic_obstacle_check_->setChecked (false);
  //--------------------------------
}

void ToolWidget::createGroupBox (QGroupBox *&group_box, const QString &text, QGridLayout *&layout) {
  group_box = new QGroupBox (text, this);
  layout = new QGridLayout (group_box);
  group_box->setCheckable (true);
//  group_box->setChecked (false);
  group_box->setLayout (layout);
  group_box->setSizePolicy (QSizePolicy::Minimum, QSizePolicy::Fixed);
}

void ToolWidget::setDrawingScheme () {
  logic_box_->show ();
  logic_obstacle_check_->show ();
  extra_box_->show ();
  extra_item_label_->show ();
  extra_item_combo_->show ();
  block_color_label_->show ();
  block_color_combo_->show ();
  block_shape_label_->show ();
  block_shape_combo_->show ();
  ground_color_label_->show ();
  ground_color_combo_->show ();
  ground_shape_label_->show ();
  ground_shape_combo_->show ();
  back_box_->show ();
}

void ToolWidget::setShapingScheme () {
  logic_box_->hide ();
  extra_box_->show ();
  extra_item_label_->show ();
  extra_item_combo_->show ();
  block_color_label_->hide ();
  block_color_combo_->hide ();
  block_shape_label_->show ();
  block_shape_combo_->show ();
  ground_color_label_->hide ();
  ground_color_combo_->hide ();
  ground_shape_label_->show ();
  ground_shape_combo_->show ();
  back_box_->hide ();
}

void ToolWidget::setPaintingScheme () {
  logic_box_->hide ();
  extra_box_->hide ();
  block_color_label_->show ();
  block_color_combo_->show ();
  block_shape_label_->hide ();
  block_shape_combo_->hide ();
  ground_color_label_->show ();
  ground_color_combo_->show ();
  ground_shape_label_->hide ();
  ground_shape_combo_->hide ();
  back_box_->show ();
}

void ToolWidget::setFillingScheme () {
  logic_box_->show ();
  logic_obstacle_check_->show ();
  extra_box_->show ();
  extra_item_label_->show ();
  extra_item_combo_->show ();
  block_color_label_->show ();
  block_color_combo_->show ();
  block_shape_label_->show ();
  block_shape_combo_->show ();
  ground_color_label_->show ();
  ground_color_combo_->show ();
  ground_shape_label_->show ();
  ground_shape_combo_->show ();
  back_box_->show ();
}

void ToolWidget::setErasingScheme () {
  logic_box_->show ();
  logic_obstacle_check_->hide ();
  extra_box_->show ();
  extra_item_label_->hide ();
  extra_item_combo_->hide ();
  block_color_label_->hide ();
  block_color_combo_->hide ();
  block_shape_label_->hide ();
  block_shape_combo_->hide ();
  ground_color_label_->hide ();
  ground_color_combo_->hide ();
  ground_shape_label_->hide ();
  ground_shape_combo_->hide ();
  back_box_->hide ();
}
