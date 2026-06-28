#include "shapes/individual_shape/freehand.h"

#include <cmath>
#include <sstream>

void Freehand::Paint(QPainter &painter) {
  if (points_.empty()) return;

  QPen pen(stroke_color_, stroke_width_);
  pen.setCapStyle(Qt::RoundCap);
  pen.setJoinStyle(Qt::RoundJoin);
  painter.setPen(pen);
  painter.setBrush(Qt::NoBrush);

  // Draw connected lines between points
  for (int i = 1; i < points_.size(); i++) {
    painter.drawLine(points_[i - 1], points_[i]);
  }
}

std::string Freehand::Serialize() {
  if (points_.empty()) return "";
  std::stringstream ss;
  ss << "<path \n";
  ss << "style=\"stroke:" << stroke_color_.name().toStdString() << ";";
  ss << "stroke-width:" << stroke_width_ << "\"  \n";
  ss << "d=\"";
  for (int i = 0; i < points_.size(); i++) {
    if (i == 0) {
      ss << "M " << points_[i].x() << " " << points_[i].y();
    } else {
      ss << " L " << points_[i].x() << " " << points_[i].y();
    }
  }
  ss << "\"" << std::endl;
  ss << "/>\n";
  return ss.str();
}

ShapeType Freehand::GetType() { return ShapeType::Freehand; }

std::unique_ptr<Shape> Freehand::Clone() {
  return std::make_unique<Freehand>(points_, fill_color_, stroke_color_, stroke_width_, has_fill_);
}

double Freehand::Distance(QPointF point) {
  double min_distance = 1e9;  // Initialize with a large number
  for (int i = 0; i < points_.size(); i++) {
    double dist_from_point = std::sqrt(std::pow(points_[i].x() - point.x(), 2) +
                                       std::pow(points_[i].y() - point.y(), 2));
    min_distance = std::min(min_distance, dist_from_point);
  }
  return min_distance;
}

void Freehand::Move(QPointF delta) {
  for (auto &point : points_) {
    point += delta;
  }
}

void Freehand::PaintSurroundingRectangle(QPainter &painter) {
  if (points_.empty()) return;

  double min_x = points_[0].x();
  double max_x = points_[0].x();
  double min_y = points_[0].y();
  double max_y = points_[0].y();

  for (const auto &point : points_) {
    min_x = std::min(min_x, point.x());
    max_x = std::max(max_x, point.x());
    min_y = std::min(min_y, point.y());
    max_y = std::max(max_y, point.y());
  }

  QRectF bounding_rect(min_x, min_y, max_x - min_x, max_y - min_y);
  painter.drawRect(bounding_rect);
}

std::unique_ptr<Shape> Freehand::Clone_wrt_movedPosition(QPointF point) {
  QPointF center = GetCenter();
  QPointF delta = point - center;
  std::vector<QPointF> new_points;
  for (const auto &p : points_) {
    new_points.push_back(p + delta);
  }
  auto new_freehand =
      std::make_unique<Freehand>(new_points, fill_color_, stroke_color_, stroke_width_, has_fill_);
  return new_freehand;
}

QPointF Freehand::GetCenter() {
  CalculateParameter();
  return center_;
}

void Freehand::Resize(QPointF old_position, QPointF new_position) {
  // For freehand, we can implement resize as scaling the points based on the distance from center
  QPointF center = GetCenter();
  double old_dist =
      sqrt(pow(old_position.x() - center.x(), 2) + pow(old_position.y() - center.y(), 2));
  double new_dist =
      sqrt(pow(new_position.x() - center.x(), 2) + pow(new_position.y() - center.y(), 2));
  if (old_dist == 0) return;  // Avoid division by zero
  double scale_factor = new_dist / old_dist;
  for (auto &point : points_) {
    point = center + (point - center) * scale_factor;
  }
  CalculateParameter();  // Recalculate parameters after resizing
}

void Freehand::CalculateParameter() {
  if (points_.empty()) return;

  double min_x = points_[0].x(), max_x = points_[0].x();
  double min_y = points_[0].y(), max_y = points_[0].y();

  for (const auto &point : points_) {
    min_x = std::min(min_x, point.x());
    max_x = std::max(max_x, point.x());
    min_y = std::min(min_y, point.y());
    max_y = std::max(max_y, point.y());
  }
  center_ = QPointF((min_x + max_x) / 2, (min_y + max_y) / 2);
}
