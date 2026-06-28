#include "shapes/individual_shape/line.h"

#include <cmath>
#include <sstream>

#include "utils/utils.h"

void Line::Paint(QPainter &painter) {
  QPen pen(stroke_color_, stroke_width_);
  painter.setPen(pen);
  painter.drawLine(start_point_, end_point_);
}

std::string Line::Serialize() {
  std::stringstream ss;
  ss << "<line \n";
  ss << "style=\"stroke:" << stroke_color_.name().toStdString() << ";";
  ss << "stroke-width:" << stroke_width_ << "\"  \n";
  ss << "x1=\"" << start_point_.x() << "\" \n";
  ss << "y1=\"" << start_point_.y() << "\" \n";
  ss << "x2=\"" << end_point_.x() << "\" \n";
  ss << "y2=\"" << end_point_.y() << "\"" << std::endl;
  ss << "/>\n";
  return ss.str();
}

ShapeType Line::GetType() { return ShapeType::Line; }

std::unique_ptr<Shape> Line::Clone() {
  return std::make_unique<Line>(start_point_, end_point_, fill_color_, stroke_color_, stroke_width_,
                                has_fill_);
}

double Line::Distance(QPointF point) { return distance_from_line(point, start_point_, end_point_); }

void Line::Move(QPointF delta) {
  start_point_ += delta;
  end_point_ += delta;
}

void Line::PaintSurroundingRectangle(QPainter &painter) {
  double min_x = std::min(start_point_.x(), end_point_.x());
  double max_x = std::max(start_point_.x(), end_point_.x());
  double min_y = std::min(start_point_.y(), end_point_.y());
  double max_y = std::max(start_point_.y(), end_point_.y());
  QRectF bounding_rect(min_x, min_y, max_x - min_x, max_y - min_y);
  painter.drawRect(bounding_rect);
}

std::unique_ptr<Shape> Line::Clone_wrt_movedPosition(QPointF point) {
  QPointF center = GetCenter();
  QPointF delta = point - center;
  return std::make_unique<Line>(start_point_ + delta, end_point_ + delta, fill_color_,
                                stroke_color_, stroke_width_, has_fill_);
}

QPointF Line::GetCenter() {
  return QPointF((start_point_.x() + end_point_.x()) / 2, (start_point_.y() + end_point_.y()) / 2);
}

void Line::Resize(QPointF old_position, QPointF new_position) {
  QPointF center = GetCenter();
  double old_dist =
      sqrt(pow(old_position.x() - center.x(), 2) + pow(old_position.y() - center.y(), 2));
  double new_dist =
      sqrt(pow(new_position.x() - center.x(), 2) + pow(new_position.y() - center.y(), 2));
  if (old_dist == 0) return;  // Avoid division by zero
  double scale_factor = new_dist / old_dist;
  start_point_ = center + (start_point_ - center) * scale_factor;
  end_point_ = center + (end_point_ - center) * scale_factor;
}
