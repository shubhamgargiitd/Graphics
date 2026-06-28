// draws a hexagon
#include "tools/individual_tools/hexagon_tool.h"
#include "document.h"

std::shared_ptr<Shape> HexagonTool::MakeShape(std::unique_ptr<Document>& doc) {
  current_hexagon_ = std::make_shared<Hexagon>();
  current_hexagon_->fill_color_   = doc->fill_color_;
  current_hexagon_->stroke_color_ = doc->stroke_color_;
  current_hexagon_->stroke_width_ = doc->stroke_width_;
  current_hexagon_->has_fill_     = doc->has_fill_;
  return current_hexagon_;
}

void HexagonTool::CalculateParameters() {
  current_hexagon_->radius_ = (sqrt(pow(current_point_.y() - start_point_.y(), 2) +
                                    pow(current_point_.x() - start_point_.x(), 2))) / 2;
  current_hexagon_->centre_ = (start_point_ + current_point_) / 2;
}
