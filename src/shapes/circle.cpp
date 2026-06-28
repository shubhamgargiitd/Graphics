
#include "shapes/individual_shape/circle.h"

#include <sstream>

void Circle::Paint(QPainter &painter) {
  QPen pen(stroke_color_, stroke_width_);
  painter.setPen(pen);
  if (has_fill_) {
    painter.setBrush(fill_color_);
  } else {
    painter.setBrush(Qt::NoBrush);
  }
  painter.drawEllipse(centre_, radius_, radius_);
}

std::string Circle::Serialize() {
  std::stringstream ss;
  ss << "<circle \n";
  ss << "style=\"fill:" << fill_color_.name().toStdString() << ";";
  ss << "fill-opacity:" << (has_fill_ ? 1 : 0) << ";";
  ss << "stroke:" << stroke_color_.name().toStdString() << ";";
  ss << "stroke-width:" << stroke_width_ << "\"  \n";
  ss << "cx=\"" << centre_.x() << "\" \n";
  ss << "cy=\"" << centre_.y() << "\" \n";
  ss << "r=\"" << radius_ << "\"" << std::endl;
  ss << "/>\n";
  return ss.str();
}

ShapeType Circle::GetType() { return ShapeType::Circle; }

std::unique_ptr<Shape> Circle::Clone() {
  return std::make_unique<Circle>(centre_, radius_, fill_color_, stroke_color_, stroke_width_,
                                  has_fill_);
}

double Circle::Distance(QPointF point) {
  double dist_to_center = sqrt(pow(point.x() - centre_.x(), 2) + pow(point.y() - centre_.y(), 2));
  if (has_fill_) {
    return dist_to_center <= radius_ ? 0 : dist_to_center - radius_;
  } else {
    return abs(dist_to_center - radius_);
  }
}

void Circle::Move(QPointF delta) { centre_ += delta; }

void Circle::PaintSurroundingRectangle(QPainter &painter) {
  QRectF bounding_rect(centre_.x() - radius_, centre_.y() - radius_, 2 * radius_, 2 * radius_);
  painter.drawRect(bounding_rect);
}

std::unique_ptr<Shape> Circle::Clone_wrt_movedPosition(QPointF point) {
  return std::make_unique<Circle>(point, radius_, fill_color_, stroke_color_, stroke_width_,
                                  has_fill_);
}

QPointF Circle::GetCenter() { return centre_; }

void Circle::Resize(QPointF old_position, QPointF new_position) {
  double old_dist =
      sqrt(pow(old_position.x() - centre_.x(), 2) + pow(old_position.y() - centre_.y(), 2));
  double new_dist =
      sqrt(pow(new_position.x() - centre_.x(), 2) + pow(new_position.y() - centre_.y(), 2));
  radius_ *= (new_dist / old_dist);
}