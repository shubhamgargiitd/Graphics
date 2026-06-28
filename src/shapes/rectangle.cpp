#include "shapes/individual_shape/rectangle.h"

#include <sstream>

void Rectangle::Paint(QPainter &painter) {
  QPen pen(stroke_color_, stroke_width_);
  painter.setPen(pen);
  if (has_fill_) {
    painter.setBrush(fill_color_);
  } else {
    painter.setBrush(Qt::NoBrush);
  }
  painter.drawRect(QRectF(top_left_.x(), top_left_.y(), width_, height_));
}

std::string Rectangle::Serialize() {
  std::stringstream ss;
  ss << "<rect \n";
  ss << "style=\"fill:" << fill_color_.name().toStdString() << ";";
  ss << "fill-opacity:" << (has_fill_ ? 1 : 0) << ";";
  ss << "stroke:" << stroke_color_.name().toStdString() << ";";
  ss << "stroke-width:" << stroke_width_ << "\"  \n";
  ss << "x=\"" << top_left_.x() << "\" \n";
  ss << "y=\"" << top_left_.y() << "\" \n";
  ss << "width=\"" << width_ << "\" \n";
  ss << "height=\"" << height_ << "\"" << std::endl;
  ss << "/>\n";
  return ss.str();
}

ShapeType Rectangle::GetType() { return ShapeType::Rectangle; }

std::unique_ptr<Shape> Rectangle::Clone() {
  return std::make_unique<Rectangle>(top_left_, width_, height_, fill_color_, stroke_color_,
                                     stroke_width_, has_fill_);
}

double Rectangle::Distance(QPointF point) {
  QPointF center(top_left_.x() + width_ / 2, top_left_.y() + height_ / 2);
  double dx = std::abs(point.x() - center.x());//x coordinate of distance from center
  double dy = std::abs(point.y() - center.y());

  if (has_fill_) {
    // If filled, check if point is inside
    dx = std::max(0.0, dx - width_ / 2);
    dy = std::max(0.0, dy - height_ / 2);
    return std::sqrt(dx * dx + dy * dy);
  } else {
    // If not filled, distance to nearest edge
    double inside_dx = std::max(0.0, dx - width_ / 2);
    double inside_dy = std::max(0.0, dy - height_ / 2);
    double outside_dx = std::max(0.0, width_ / 2 - dx);
    double outside_dy = std::max(0.0, height_ / 2 - dy);

    if (dx <= width_ / 2 && dy <= height_ / 2) {
      // Point is inside, return distance to nearest edge
      return std::min({width_ / 2 - dx, height_ / 2 - dy, dx - (-width_ / 2), dy - (-height_ / 2)});
    } else {
      // Point is outside
      return std::sqrt(inside_dx * inside_dx + inside_dy * inside_dy);
    }
  }
}

void Rectangle::Move(QPointF delta) { top_left_ += delta; }

void Rectangle::PaintSurroundingRectangle(QPainter &painter) {
  QRectF bounding_rect(top_left_.x(), top_left_.y(), width_, height_);
  painter.drawRect(bounding_rect);
}

std::unique_ptr<Shape> Rectangle::Clone_wrt_movedPosition(QPointF point) {
  QPointF center = GetCenter();
  QPointF delta = point - center;
  return std::make_unique<Rectangle>(top_left_ + delta, width_, height_, fill_color_, stroke_color_,
                                     stroke_width_, has_fill_);
}

QPointF Rectangle::GetCenter() {
  return QPointF(top_left_.x() + width_ / 2, top_left_.y() + height_ / 2);
}

void Rectangle::Resize(QPointF old_position, QPointF new_position) {
  QPointF center = GetCenter();
  double old_dist =
      sqrt(pow(old_position.x() - center.x(), 2) + pow(old_position.y() - center.y(), 2));
  double new_dist =
      sqrt(pow(new_position.x() - center.x(), 2) + pow(new_position.y() - center.y(), 2));
  if (old_dist == 0) return;  // Avoid division by zero
  double scale_factor = new_dist / old_dist;
  width_ *= scale_factor;
  height_ *= scale_factor;
  // Adjust top_left to keep center fixed
  top_left_ = center - QPointF(width_ / 2, height_ / 2);
}
