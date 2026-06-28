// draws a circle
#include "tools/individual_tools/circle_tool.h"
#include "document.h"

std::shared_ptr<Shape> CircleTool::MakeShape(std::unique_ptr<Document>& doc) {
  current_circle_ = std::make_shared<Circle>();
  current_circle_->fill_color_   = doc->fill_color_;
  current_circle_->stroke_color_ = doc->stroke_color_;
  current_circle_->stroke_width_ = doc->stroke_width_;
  current_circle_->has_fill_     = doc->has_fill_;
  return current_circle_;
}

void CircleTool::CalculateParameters() {
  current_circle_->radius_ = (sqrt(pow(current_point_.y() - start_point_.y(), 2) +
                                   pow(current_point_.x() - start_point_.x(), 2))) / 2;
  current_circle_->centre_ = (start_point_ + current_point_) / 2;
}
