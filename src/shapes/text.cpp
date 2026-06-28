#include "shapes/individual_shape/text.h"
#include "utils/utils.h"
#include <QPainter>
#include <cmath>
#include <sstream>
void Text::Paint(QPainter &painter) {
  painter.setPen(QPen(stroke_color_, stroke_width_));
  painter.setFont(QFont("Arial", font_size_));
  // Use a large rect to allow for multiline text
  QRectF rect(position_.x(), position_.y(), 10000, 10000);
  painter.drawText(rect, Qt::AlignLeft | Qt::AlignTop | Qt::TextDontClip, content_);
}

QPointF Text::GetCenter() {
  CalculateParameter();
  return position_ + QPointF(width_ / 2.0, height_ / 2.0);
}

ShapeType Text::GetType() { return ShapeType::Text; }

void Text::CalculateParameter() {
  QFontMetrics fm(QFont("Arial", font_size_));
  QRect rect = fm.boundingRect(QRect(0, 0, 10000, 10000), Qt::AlignLeft | Qt::AlignTop, content_);
  width_ = rect.width();
  height_ = rect.height();
}

std::string Text::Serialize() {
  std::stringstream ss;
  ss << "<text \n";
  ss << "style=\"stroke:" << stroke_color_.name().toStdString() << ";";
  ss << "stroke-width:" << stroke_width_ << "\"  \n";
  ss << "x=\"" << position_.x() << "\" \n";
  ss << "y=\"" << position_.y() << "\" \n";
  ss << "font-size=\"" << font_size_ << "\" >\n";
  // Escape special characters in content
  std::string content_str = content_.toStdString();
  for (const auto &c : content_str) {
    ss << EscapedCharacter(c);
  }
  ss << "\n</text>\n";
  return ss.str();
}

double Text::Distance(QPointF point) {
  CalculateParameter();
  QPointF center = position_ + QPointF(width_ / 2.0, height_ / 2.0);
  double dx = std::max(0.0, std::abs(point.x() - center.x()) - width_ / 2);
  double dy = std::max(0.0, std::abs(point.y() - center.y()) - height_ / 2);
  return sqrt(dx * dx + dy * dy);
}

void Text::Move(QPointF delta) {
  position_ += delta;
}

std::unique_ptr<Shape> Text::Clone() { return std::make_unique<Text>(*this); }

void Text::PaintSurroundingRectangle(QPainter &painter) {
  QFontMetrics fm(QFont("Arial", font_size_));
  QRect rect = fm.boundingRect(QRect(0, 0, 10000, 10000), Qt::AlignLeft | Qt::AlignTop, content_);
  QRectF bounding_rect(position_.x(), position_.y(), rect.width(), rect.height());
  painter.drawRect(bounding_rect);
}

std::unique_ptr<Shape> Text::Clone_wrt_movedPosition(QPointF point) {
  auto text = std::make_unique<Text>(*this);
  text->position_ = point;
  return text;
}

void Text::Resize(QPointF old_position, QPointF new_position) {
  // resize w.r.t to starting point
  CalculateParameter();
  double old_dist =
      sqrt(pow(old_position.x() - position_.x(), 2) + pow(old_position.y() - position_.y(), 2));
  double new_dist =
      sqrt(pow(new_position.x() - position_.x(), 2) + pow(new_position.y() - position_.y(), 2));
  if (old_dist == 0) return;  // Avoid division by zero
  double scale_factor = new_dist / old_dist;
  font_size_ = font_size_ * scale_factor;
  if (font_size_ < 6) font_size_ = 6;      // Minimum font size
  if (font_size_ > 300) font_size_ = 300;  // Maximum font size
}
