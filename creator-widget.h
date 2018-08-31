#ifndef CREATORWIDGET_H
#define CREATORWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QMouseEvent>
#include "textures.h"
#include "creator-mechanics.h"
#include "tool-widget.h"

class CreatorWidget : public QWidget {
  Q_OBJECT

public:
  explicit CreatorWidget (Textures *textures, ToolWidget *tool_widget, QWidget *parent = 0);
  ~CreatorWidget ();

signals:

public slots:
  void newMap ();
  void newMap (int width, int height, const QString &name);
//  void loadMap (const QString &name);

  void setDrawingTool ();
  void setShapingTool ();
  void setPaintingTool ();
  void setErasingTool ();

  void setToolExtra (const int tool_extra_index);
  void setToolBlock (const int tool_block_index);
  void setToolBlockColor (const int tool_block_color_index);
  void setToolGround (const int tool_ground_index);
  void setToolGroundColor (const int tool_ground_color_index);
  void setToolBackColor (const int tool_back_color_index);

  void toggleLogicEditing (bool is_on);
  void toggleExtraEditing (bool is_on);
  void toggleBlockEditing (bool is_on);
  void toggleGroundEditing (bool is_on);
  void toggleBackEditing (bool is_on);

  void toggleLogicVisibility (bool is_on);
  void toggleExtraVisibility (bool is_on);
  void toggleBlockVisibility (bool is_on);
  void toggleGroundVisibility (bool is_on);
  void toggleBackVisibility (bool is_on);

  void zoomIn ();
  void zoomOut ();
  void zoomReset ();

  void toggleGrid ();

protected:
  void paintEvent (QPaintEvent *event);
  void mousePressEvent (QMouseEvent *event);
  void mouseMoveEvent (QMouseEvent *event);

private:
  void redrawBackLayer ();
  void redrawGroundLayer ();
  void redrawBlockLayer ();
  void redrawExtraLayer ();
  void drawTool (int x, int y);
  void shapeTool (int x, int y);
  void paintTool (int x, int y);
  void eraseTool (int x, int y);
  void (CreatorWidget::*activeTool_) (int, int);

  CreatorMechanics *map_canvas_ = nullptr;
  Textures *const textures_;
  ToolWidget *const tool_widget_;
  QPixmap *back_layer_ = nullptr;
  QPixmap *ground_layer_ = nullptr;
  QPixmap *block_layer_ = nullptr;
  QPixmap *extra_layer_ = nullptr;

  mapField::extra::extra tool_extra_ = mapField::extra::Bush;
  mapField::block::block tool_block_ = mapField::block::Quoin1;
  mapField::color::color tool_block_color_ = mapField::color::Dirt;
  mapField::ground::ground tool_ground_ = mapField::ground::Plain;
  mapField::color::color tool_ground_color_ = mapField::color::Dirt;
  mapField::color::color tool_back_color_ = mapField::color::Dirt;

  bool isLogicEditingEnabled_ = true;
  bool isExtraEditingEnabled_ = true;
  bool isBlockEditingEnabled_ = true;
  bool isGroundEditingEnabled_ = true;
  bool isBackEditingEnabled_ = true;
  bool isGridEnabled_ = false;

  bool isLogicVisible_ = false;
  bool isExtraVisible_ = true;
  bool isBlockVisible_ = true;
  bool isGroundVisible_ = true;
  bool isBackVisible_ = true;

  float zoom_magnitude_ = 1.0;
};

#endif // CREATORWIDGET_H
