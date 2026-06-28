// draws a rectangle
#include "tools/individual_tools/rectangle_tool.h"
#include "document.h"

std::shared_ptr<Shape> RectangleTool::MakeShape(std::unique_ptr<Document>& doc) {
  current_rectangle_ = std::make_shared<Rectangle>();
  current_rectangle_->fill_color_ = doc->fill_color_;
  current_rectangle_->stroke_color_ = doc->stroke_color_;
  current_rectangle_->stroke_width_ = doc->stroke_width_;
  current_rectangle_->has_fill_ = doc->has_fill_;
  return current_rectangle_;
}

void RectangleTool::CalculateParameters() {
  double x1 = start_point_.x(), y1 = start_point_.y();
  double x2 = current_point_.x(), y2 = current_point_.y();
  current_rectangle_->top_left_ = QPointF(std::min(x1, x2), std::min(y1, y2));
  current_rectangle_->width_    = std::abs(x2 - x1);
  current_rectangle_->height_   = std::abs(y2 - y1);
}
