#include "shapes/individual_shape/hexagon.h"

#include <cmath>
#include <sstream>

#include "utils/utils.h"

#define PI 3.14159265359
void Hexagon::Paint(QPainter &painter) {
  QPen pen(stroke_color_, stroke_width_);
  painter.setPen(pen);
  if (has_fill_) {
    painter.setBrush(fill_color_);
  } else {
    painter.setBrush(Qt::NoBrush);
  }
  // Calculate hexagon vertices
  QPolygonF hexagon;
  for (int i = 0; i < 6; ++i) {
    double angle = PI / 3.0 * i;  // 60 degrees in radians
    double x = centre_.x() + radius_ * cos(angle);
    double y = centre_.y() + radius_ * sin(angle);
    hexagon << QPointF(x, y);
  }
  painter.drawPolygon(hexagon);
}

std::string Hexagon::Serialize() {
  std::stringstream ss;
  ss << "<polygon \n";
  ss << "style=\"fill:" << fill_color_.name().toStdString() << ";";
  ss << "fill-opacity:" << (has_fill_ ? 1 : 0) << ";";
  ss << "stroke:" << stroke_color_.name().toStdString() << ";";
  ss << "stroke-width:" << stroke_width_ << "\"  \n";
  ss << "cx=\"" << centre_.x() << "\" \n";
  ss << "cy=\"" << centre_.y() << "\" \n";
  ss << "r=\"" << radius_ << "\" \n";
  ss << "shape-type=\"hexagon\"" << std::endl;
  ss << "/>\n";
  return ss.str();
}

ShapeType Hexagon::GetType() { return ShapeType::Hexagon; }

std::unique_ptr<Shape> Hexagon::Clone() {
  return std::make_unique<Hexagon>(centre_, radius_, fill_color_, stroke_color_, stroke_width_,
                                   has_fill_);
}

double Hexagon::Distance(QPointF point) {
  // Calculate hexagon vertices
  std::vector<QPointF> vertices;
  for (int i = 0; i < 6; ++i) {
    double angle = PI / 3.0 * i;  // 60 degrees in radians
    double x = centre_.x() + radius_ * cos(angle);
    double y = centre_.y() + radius_ * sin(angle);
    vertices.push_back(QPointF(x, y));
  }

  if (has_fill_) {
    // For simplicity, we use distance from center as approximation
    double dist_to_center = sqrt(pow(point.x() - centre_.x(), 2) + pow(point.y() - centre_.y(), 2));
    if (dist_to_center <= radius_) {
      return 0;
    }
  }

  // Calculate distance to nearest edge
  double min_distance = 1e9;
  for (int i = 0; i < 6; ++i) {
    QPointF p1 = vertices[i];
    QPointF p2 = vertices[(i + 1) % 6];
    double dist = distance_from_line(point, p1, p2);
    min_distance = std::min(min_distance, dist);
  }
  return min_distance;
}

void Hexagon::Move(QPointF delta) { centre_ += delta; }

void Hexagon::PaintSurroundingRectangle(QPainter &painter) {
  QRectF bounding_rect(centre_.x() - radius_, centre_.y() - radius_, 2 * radius_, 2 * radius_);
  painter.drawRect(bounding_rect);
}

std::unique_ptr<Shape> Hexagon::Clone_wrt_movedPosition(QPointF point) {
  return std::make_unique<Hexagon>(point, radius_, fill_color_, stroke_color_, stroke_width_,
                                   has_fill_);
}

QPointF Hexagon::GetCenter() { return centre_; }

void Hexagon::Resize(QPointF old_position, QPointF new_position) {
  double old_dist =
      sqrt(pow(old_position.x() - centre_.x(), 2) + pow(old_position.y() - centre_.y(), 2));
  double new_dist =
      sqrt(pow(new_position.x() - centre_.x(), 2) + pow(new_position.y() - centre_.y(), 2));
  if (old_dist == 0) return;  // Avoid division by zero
  double scale_factor = new_dist / old_dist;
  radius_ *= scale_factor;
}
