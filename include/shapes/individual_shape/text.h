#pragma once
#include <QString>

#include "shapes/shape.h"

class Text : public Shape {
public:
  QPointF position_;
  QString content_;
  double width_;
  double height_;
  double font_size_;
  void CalculateParameter();
  Text() : position_(QPointF(0, 0)), content_(""), font_size_(12) {
    Shape::fill_color_ = Qt::black;
    Shape::stroke_color_ = Qt::black;
    Shape::stroke_width_ = 1;
    Shape::has_fill_ = false;
  }
  Text(QPointF position, QString content, QColor fill_color, QColor stroke_color,
       float stroke_width, bool has_fill, double font_size)
      : position_(position), content_(content), font_size_(font_size) {
    Shape::fill_color_ = fill_color;
    Shape::stroke_color_ = stroke_color;
    Shape::stroke_width_ = stroke_width;
    Shape::has_fill_ = has_fill;
  }
  void Paint(QPainter &painter) override;
  QPointF GetCenter() override;
  ShapeType GetType() override;
  std::string Serialize() override;
  double Distance(QPointF point) override;
  void Move(QPointF delta) override;
  std::unique_ptr<Shape> Clone() override;
  void PaintSurroundingRectangle(QPainter &painter) override;
  std::unique_ptr<Shape> Clone_wrt_movedPosition(QPointF point) override;
  void Resize(QPointF old_position, QPointF new_position) override;
};
