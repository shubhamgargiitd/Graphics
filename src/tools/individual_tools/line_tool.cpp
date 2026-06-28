// draws a line
#include "tools/individual_tools/line_tool.h"
#include "document.h"

std::shared_ptr<Shape> LineTool::MakeShape(std::unique_ptr<Document>& doc) {
  current_line_ = std::make_shared<Line>();
  current_line_->fill_color_ = doc->fill_color_;
  current_line_->stroke_color_ = doc->stroke_color_;
  current_line_->stroke_width_ = doc->stroke_width_;
  current_line_->has_fill_ = doc->has_fill_;
  return current_line_;
}

void LineTool::CalculateParameters() {
  current_line_->start_point_ = start_point_;
  current_line_->end_point_   = current_point_;
}
