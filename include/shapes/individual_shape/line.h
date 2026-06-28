#pragma once
#include "shapes/shape.h"

class Line : public Shape {
public:
  QPointF start_point_;
  QPointF end_point_;

  Line() : start_point_(QPointF(0, 0)), end_point_(QPointF(0, 0)) {
    Shape::fill_color_ = Qt::black;
    Shape::stroke_color_ = Qt::black;
    Shape::stroke_width_ = 1;
    Shape::has_fill_ = false;
  }
  Line(QPointF start, QPointF end, QColor fill_color, QColor stroke_color, float stroke_width,
       bool has_fill)
      : start_point_(start), end_point_(end) {
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
