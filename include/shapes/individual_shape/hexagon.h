#pragma once
#include "shapes/shape.h"

class Hexagon : public Shape {
public:
  QPointF centre_;
  double radius_;
  Hexagon() : centre_(QPointF(0, 0)), radius_(0) {
    Shape::fill_color_ = Qt::black;
    Shape::stroke_color_ = Qt::black;
    Shape::stroke_width_ = 1;
    Shape::has_fill_ = false;
  }
  Hexagon(QPointF center, double radius, QColor fill_color, QColor stroke_color, float stroke_width,
          bool has_fill)
      : centre_(center), radius_(radius) {
    Shape::fill_color_ = fill_color;
    Shape::stroke_color_ = stroke_color;
    Shape::stroke_width_ = stroke_width;
    Shape::has_fill_ = has_fill;
  }
  void Paint(QPainter &painter) override;
  QPointF GetCenter() override;
  ShapeType GetType() override;
  std::string Serialize() override;
  double Distance(QPointF point) override;  // distance from each line segment
  void Move(QPointF delta) override;
  std::unique_ptr<Shape> Clone() override;
  void PaintSurroundingRectangle(QPainter &painter) override;
  std::unique_ptr<Shape> Clone_wrt_movedPosition(QPointF point) override;
  void Resize(QPointF old_position, QPointF new_position) override;
};
