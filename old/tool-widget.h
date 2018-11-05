#ifndef TOOLKWIDGET_H
#define TOOLKWIDGET_H

#include <QDebug>
#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QGroupBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QLabel>
#include <QComboBox>
//#include <QSpacerItem>
#include "map-field.h"

class ToolWidget : public QWidget {
  Q_OBJECT

public:
  explicit ToolWidget (QWidget *parent = 0);

  QRadioButton *drawing_radio_, *shaping_radio_, *painting_radio_, *filling_radio_, *erasing_radio_;
  QGroupBox *logic_box_;
  QGroupBox *extra_box_;
  QGroupBox *block_box_;
  QGroupBox *ground_box_;
  QGroupBox *back_box_;
  QCheckBox *logic_obstacle_check_;
  QComboBox *extra_item_combo_;
  QComboBox *block_color_combo_, *block_shape_combo_;
  QComboBox *ground_color_combo_, *ground_shape_combo_;
  QComboBox *back_color_combo_;

private:
  void createGroupBox (QGroupBox *&group_box, const QString &text, QGridLayout *&layout);
  QGroupBox *tools_box_;
  QVBoxLayout *main_layout_;
  QGridLayout *tools_layout_;
  QGridLayout *logic_layout_;
  QGridLayout *extra_layout_;
  QGridLayout *block_layout_;
  QGridLayout *ground_layout_;
  QGridLayout *back_layout_;
  QLabel *extra_item_label_;
  QLabel *block_color_label_, *block_shape_label_;
  QLabel *ground_color_label_, *ground_shape_label_;
  QLabel *back_color_label_;

private slots:
  void setDrawingScheme ();
  void setShapingScheme ();
  void setPaintingScheme ();
  void setFillingScheme ();
  void setErasingScheme ();

};

#endif // TOOLWIDGET_H
