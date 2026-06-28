#pragma once
#include <QColor>
#include <QPainter>
#include <QPointF>
#include "types.h"

class Shape {
public:
  QColor fill_color_;
  QColor stroke_color_;
  float stroke_width_;
  bool has_fill_;

  // functions for polymorphism
  virtual QPointF GetCenter() = 0;  // resizing of shapes are done w.r.t centers
  virtual void Paint(QPainter &painter) = 0;
  virtual ShapeType GetType() = 0;
  virtual std::string Serialize() = 0;
  virtual double Distance(QPointF point) = 0;
  virtual void Move(QPointF delta) = 0;
  virtual ~Shape() = default;
  virtual std::unique_ptr<Shape> Clone() = 0;
  virtual void PaintSurroundingRectangle(QPainter &painter) = 0;
  virtual std::unique_ptr<Shape> Clone_wrt_movedPosition(QPointF point) = 0;
  virtual void Resize(QPointF old_position, QPointF new_position) = 0;
};
