#include "creator-widget.h"

CreatorWidget::CreatorWidget (Textures *textures, ToolWidget *tool_widget, QWidget *parent) :
  QWidget (parent), textures_ (textures), tool_widget_ (tool_widget) {
  newMap (80, 50, ""); // !!!!!!!!!! TEMP
  this->setMinimumSize (500, 500);
  this->setMaximumSize (map_canvas_->mapWidth () * Textures::Resolution,
                        map_canvas_->mapHeight () * Textures::Resolution);
  this->setSizePolicy (QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
  redrawBackLayer ();
  redrawGroundLayer ();
  redrawBlockLayer ();
  redrawExtraLayer ();
  activeTool_ = drawTool;
//  this->setCursor (Qt::PointingHandCursor);
}

void CreatorWidget::toggleGrid () {
  isGridEnabled_ = !isGridEnabled_;
  this->repaint ();
}

CreatorWidget::~CreatorWidget () {
  if (map_canvas_ != nullptr)
    delete map_canvas_;
  if (back_layer_ != nullptr)
    delete back_layer_;
  if (ground_layer_ != nullptr)
    delete ground_layer_;
  if (block_layer_ != nullptr)
    delete block_layer_;
  if (extra_layer_ != nullptr)
    delete extra_layer_;
}

void CreatorWidget::newMap () {
  if (map_canvas_ != nullptr)
    delete map_canvas_;
  map_canvas_ = new CreatorMechanics (50, 50, "");
  this->repaint ();
}

void CreatorWidget::newMap(int width, int height, const QString &name) {
  if (map_canvas_ != nullptr)
    delete map_canvas_;
  map_canvas_ = new CreatorMechanics (width, height, name);
}

void CreatorWidget::setDrawingTool () {
  activeTool_ = drawTool;
}

void CreatorWidget::setShapingTool () {
  activeTool_ = shapeTool;
}

void CreatorWidget::setPaintingTool () {
  activeTool_ = paintTool;
}

void CreatorWidget::setErasingTool () {
  activeTool_ = eraseTool;
}

void CreatorWidget::setToolExtra (const int tool_extra_index) {
  tool_extra_ = static_cast<mapField::extra::extra> (tool_extra_index);
}

void CreatorWidget::setToolBlock (const int tool_block_index) {
  tool_block_ = static_cast<mapField::block::block> (tool_block_index);
}

void CreatorWidget::setToolBlockColor (const int tool_block_color_index) {
  tool_block_color_ = static_cast<mapField::color::color> (tool_block_color_index);
}

void CreatorWidget::setToolGround (const int tool_ground_index) {
  tool_ground_ = static_cast<mapField::ground::ground> (tool_ground_index);
}

void CreatorWidget::setToolGroundColor (const int tool_ground_color_index) {
  tool_ground_color_ = static_cast<mapField::color::color> (tool_ground_color_index);
}

void CreatorWidget::setToolBackColor (const int tool_back_color_index) {
  tool_back_color_ = static_cast<mapField::color::color> (tool_back_color_index);
}

void CreatorWidget::toggleLogicEditing (bool is_on) {
  isLogicEditingEnabled_ = is_on;
}

void CreatorWidget::toggleExtraEditing (bool is_on) {
  isExtraEditingEnabled_ = is_on;
}

void CreatorWidget::toggleBlockEditing (bool is_on) {
  isBlockEditingEnabled_ = is_on;
}

void CreatorWidget::toggleGroundEditing (bool is_on) {
  isGroundEditingEnabled_ = is_on;
}

void CreatorWidget::toggleBackEditing (bool is_on) {
  isBackEditingEnabled_ = is_on;
}

void CreatorWidget::toggleLogicVisibility (bool is_on) {
  isLogicVisible_ = is_on;
  this->repaint ();
}

void CreatorWidget::toggleExtraVisibility (bool is_on) {
  isExtraVisible_ = is_on;
  this->repaint ();
}

void CreatorWidget::toggleBlockVisibility (bool is_on) {
  isBlockVisible_ = is_on;
  this->repaint ();
}

void CreatorWidget::toggleGroundVisibility (bool is_on) {
  isGroundVisible_ = is_on;
  this->repaint ();
}

void CreatorWidget::toggleBackVisibility (bool is_on) {
  isBackVisible_ = is_on;
  this->repaint ();
}

void CreatorWidget::zoomIn () {
  if (zoom_magnitude_ < 4.0)
    zoom_magnitude_ *= 2;
  this->setMaximumSize (map_canvas_->mapWidth () * Textures::Resolution * zoom_magnitude_,
                        map_canvas_->mapHeight () * Textures::Resolution * zoom_magnitude_);
  this->repaint ();
}

void CreatorWidget::zoomOut () {
  if (zoom_magnitude_ > 0.25)
    zoom_magnitude_ /= 2;
  this->setMaximumSize (map_canvas_->mapWidth () * Textures::Resolution * zoom_magnitude_,
                        map_canvas_->mapHeight () * Textures::Resolution * zoom_magnitude_);
  this->repaint ();
}

void CreatorWidget::zoomReset () {
  zoom_magnitude_ = 1.0;
  this->setMinimumSize (500, 500);
  this->setMaximumSize (map_canvas_->mapWidth () * Textures::Resolution,
                        map_canvas_->mapHeight () * Textures::Resolution);
  this->repaint ();
}

void CreatorWidget::paintEvent (QPaintEvent *) {
  QPainter *painter = new QPainter (this);
  QSize target (map_canvas_->mapWidth () * Textures::Resolution * zoom_magnitude_,
                map_canvas_->mapHeight () * Textures::Resolution * zoom_magnitude_);
  if (isBackVisible_)
    painter->drawPixmap (0, 0, back_layer_->scaled (target));
  if (isGroundVisible_)
    painter->drawPixmap (0, 0, ground_layer_->scaled (target));
  if (isBlockVisible_)
    painter->drawPixmap (0, 0, block_layer_->scaled (target));
  if (isExtraVisible_)
    painter->drawPixmap (0, 0, extra_layer_->scaled (target));

  if (isGridEnabled_) {
    painter->setPen (Qt::gray);
    for (int x = 0; x < map_canvas_->mapWidth (); ++ x)
      for (int y = 0; y < map_canvas_->mapHeight (); ++ y)
        painter->drawRect (x * Textures::Resolution * zoom_magnitude_,
                           y * Textures::Resolution * zoom_magnitude_,
                           Textures::Resolution * zoom_magnitude_,
                           Textures::Resolution * zoom_magnitude_);
    painter->setPen (Qt::black);
    for (int x = 0; x < map_canvas_->mapWidth (); x += 5)
      for (int y = 0; y < map_canvas_->mapHeight (); y += 5)
        painter->drawRect (x * Textures::Resolution * zoom_magnitude_,
                           y * Textures::Resolution * zoom_magnitude_,
                           Textures::Resolution * zoom_magnitude_ * 5,
                           Textures::Resolution * zoom_magnitude_ * 5);
  }
  delete painter;
}

void CreatorWidget::mousePressEvent (QMouseEvent *event) {
  switch (event->button ()) {
    case Qt::LeftButton:
      (this->*activeTool_) (event->x () / (Textures::Resolution * zoom_magnitude_),
                            event->y () / (Textures::Resolution * zoom_magnitude_));
      event->accept ();
      break;
    default:
      break;
  }
}

void CreatorWidget::mouseMoveEvent (QMouseEvent *event) {
  switch (event->buttons ()) {
    case Qt::LeftButton:
      (this->*activeTool_) (event->x () / (Textures::Resolution * zoom_magnitude_),
                            event->y () / (Textures::Resolution * zoom_magnitude_));
      event->accept ();
      break;
    default:
      break;
  }
}

void CreatorWidget::redrawBackLayer () {
  if (back_layer_ != nullptr)
    delete back_layer_;
  back_layer_ = new QPixmap (map_canvas_->mapWidth () * Textures::Resolution,
                             map_canvas_->mapHeight () * Textures::Resolution);
  //  back_layer_->fill (Qt::transparent);
  QPainter *painter = new QPainter (back_layer_);
  for (int x = 0; x < map_canvas_->mapWidth (); ++ x)
    for (int y = 0; y < map_canvas_->mapHeight (); ++ y)
      painter->drawPixmap (x * Textures::Resolution, y * Textures::Resolution,
                           textures_->backTexture (map_canvas_->backColor (x, y)));
  delete painter;
}

void CreatorWidget::redrawGroundLayer () {
  if (ground_layer_ != nullptr)
    delete ground_layer_;
  ground_layer_ = new QPixmap (map_canvas_->mapWidth () * Textures::Resolution,
                               map_canvas_->mapHeight () * Textures::Resolution);
  ground_layer_->fill (Qt::transparent);
  QPainter *painter = new QPainter (ground_layer_);
  for (int x = 0; x < map_canvas_->mapWidth (); ++ x)
    for (int y = 0; y < map_canvas_->mapHeight (); ++ y)
      if (map_canvas_->groundPrintFlag (x, y))
        painter->drawPixmap (x * Textures::Resolution, y * Textures::Resolution,
                             textures_->groundTexture (map_canvas_->ground (x, y), map_canvas_->groundColor (x, y)));
  delete painter;
}

void CreatorWidget::redrawBlockLayer () {
  if (block_layer_ != nullptr)
    delete block_layer_;
  block_layer_ = new QPixmap (map_canvas_->mapWidth () * Textures::Resolution,
                              map_canvas_->mapHeight () * Textures::Resolution);
  block_layer_->fill (Qt::transparent);
  QPainter *painter = new QPainter (block_layer_);
  for (int x = 0; x < map_canvas_->mapWidth (); ++ x)
    for (int y = 0; y < map_canvas_->mapHeight (); ++ y)
      if (map_canvas_->blockPrintFlag (x, y))
        painter->drawPixmap (x * Textures::Resolution, y * Textures::Resolution,
                             textures_->blockTexture (map_canvas_->block (x, y), map_canvas_->blockColor (x, y)));
  delete painter;
}

void CreatorWidget::redrawExtraLayer () {
  if (extra_layer_ != nullptr)
    delete extra_layer_;
  extra_layer_ = new QPixmap (map_canvas_->mapWidth () * Textures::Resolution,
                              map_canvas_->mapHeight () * Textures::Resolution);
  extra_layer_->fill (Qt::transparent);
  QPainter *painter = new QPainter (extra_layer_);
  for (int x = 0; x < map_canvas_->mapWidth (); ++ x)
    for (int y = 0; y < map_canvas_->mapHeight (); ++ y)
      if (map_canvas_->extraPrintFlag (x, y))
        painter->drawPixmap (x * Textures::Resolution, y * Textures::Resolution,
                             textures_->extraTexture (map_canvas_->extra (x, y)));
  delete painter;
}

void CreatorWidget::drawTool (int x, int y) {
  if (isExtraEditingEnabled_) {
    map_canvas_->setExtra (tool_extra_, x, y);
    map_canvas_->setExtraPrintFlag (true, x, y);
    redrawExtraLayer ();
  }
  if (isBlockEditingEnabled_) {
    map_canvas_->setBlock (tool_block_, x, y);
    map_canvas_->setBlockColor (tool_block_color_, x, y);
    map_canvas_->setBlockPrintFlag (true, x, y);
    redrawBlockLayer ();
  }
  if (isGroundEditingEnabled_) {
    map_canvas_->setGround (tool_ground_, x, y);
    map_canvas_->setGroundColor (tool_ground_color_, x, y);
    map_canvas_->setGroundPrintFlag (true, x, y);
    redrawGroundLayer ();
  }
  if (isBackEditingEnabled_) {
    map_canvas_->setBackColor (tool_back_color_, x, y);
    redrawBackLayer ();
  }
  this->repaint ();
}

void CreatorWidget::shapeTool (int x, int y) {
  if (isExtraEditingEnabled_) {
    map_canvas_->setExtra (tool_extra_, x, y);
    redrawExtraLayer ();
  }
  if (isBlockEditingEnabled_) {
    map_canvas_->setBlock (tool_block_, x, y);
    redrawBlockLayer ();
  }
  if (isGroundEditingEnabled_) {
    map_canvas_->setGround (tool_ground_, x, y);
    redrawGroundLayer ();
  }
  this->repaint ();
}

void CreatorWidget::paintTool (int x, int y) {
  if (isBlockEditingEnabled_) {
    map_canvas_->setBlockColor (tool_block_color_, x, y);
    redrawBlockLayer ();
  }
  if (isGroundEditingEnabled_) {
    map_canvas_->setGroundColor (tool_ground_color_, x, y);
    redrawGroundLayer ();
  }
  if (isBackEditingEnabled_) {
    map_canvas_->setBackColor (tool_back_color_, x, y);
    redrawBackLayer ();
  }
  this->repaint ();
}

void CreatorWidget::eraseTool (int x, int y) {
  if (isExtraEditingEnabled_) {
    map_canvas_->setExtraPrintFlag (false, x, y);
    redrawExtraLayer ();
  }
  if (isBlockEditingEnabled_) {
    map_canvas_->setBlockPrintFlag (false, x, y);
    redrawBlockLayer ();
  }
  if (isGroundEditingEnabled_) {
    map_canvas_->setGroundPrintFlag (false, x, y);
    redrawGroundLayer ();
  }
  this->repaint ();
}
