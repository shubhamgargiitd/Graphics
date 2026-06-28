#pragma once
#include <vector>

#include "shapes/shape.h"

class Freehand : public Shape {
public:
  QPointF center_;
  std::vector<QPointF> points_;
  Freehand() {
    Shape::fill_color_ = Qt::black;
    Shape::stroke_color_ = Qt::black;
    Shape::stroke_width_ = 2;
    Shape::has_fill_ = false;
  }
  Freehand(std::vector<QPointF> points, QColor fill_color, QColor stroke_color, float stroke_width,
           bool has_fill)
      : points_(points) {
    Shape::fill_color_ = fill_color;
    Shape::stroke_color_ = stroke_color;
    Shape::stroke_width_ = stroke_width;
    Shape::has_fill_ = has_fill;
  }
  void Paint(QPainter &painter) override;
  QPointF GetCenter() override;
  ShapeType GetType() override;
  std::string Serialize() override;
  double Distance(QPointF point) override;//distance from each point in vector
  void Move(QPointF delta) override;
  std::unique_ptr<Shape> Clone() override;
  void PaintSurroundingRectangle(QPainter &painter) override;
  std::unique_ptr<Shape> Clone_wrt_movedPosition(QPointF point) override;
  void Resize(QPointF old_position, QPointF new_position) override;
  void CalculateParameter();
};
