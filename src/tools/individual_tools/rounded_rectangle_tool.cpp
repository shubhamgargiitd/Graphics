// draws a rounded rectangle
#include "tools/individual_tools/rounded_rectangle_tool.h"
#include <QInputDialog>
#include <cmath>
#include "document.h"

std::shared_ptr<Shape> RoundedRectangleTool::MakeShape(std::unique_ptr<Document>& doc) {
  current_rounded_rectangle_ = std::make_shared<RoundedRectangle>();
  current_rounded_rectangle_->fill_color_    = doc->fill_color_;
  current_rounded_rectangle_->stroke_color_  = doc->stroke_color_;
  current_rounded_rectangle_->stroke_width_  = doc->stroke_width_;
  current_rounded_rectangle_->has_fill_      = doc->has_fill_;
  current_rounded_rectangle_->corner_radius_ = 10;
  return current_rounded_rectangle_;
}

void RoundedRectangleTool::CalculateParameters() {
  double min_x = std::min(start_point_.x(), current_point_.x());
  double max_x = std::max(start_point_.x(), current_point_.x());
  double min_y = std::min(start_point_.y(), current_point_.y());
  double max_y = std::max(start_point_.y(), current_point_.y());
  current_rounded_rectangle_->top_left_ = QPointF(min_x, min_y);
  current_rounded_rectangle_->width_    = std::abs(max_x - min_x);
  current_rounded_rectangle_->height_   = std::abs(max_y - min_y);
}

void RoundedRectangleTool::MouseMove(std::unique_ptr<Document>& doc, QMouseEvent* event) {
  DrawingTool::MouseMove(doc, event);
  if (current_rounded_rectangle_)
    current_rounded_rectangle_->corner_radius_ =
        std::min(current_rounded_rectangle_->width_, current_rounded_rectangle_->height_) / 8;
}

void RoundedRectangleTool::MouseReleased(std::unique_ptr<Document>& doc, QMouseEvent* event) {
  if (!current_shape_) return;
  ending_point_ = current_point_ = event->pos();
  CalculateParameters();
  bool ok;
  double radius = QInputDialog::getDouble(
      nullptr, "Corner Radius", "Enter corner radius:", 10, 0,
      std::min(current_rounded_rectangle_->width_, current_rounded_rectangle_->height_) * 10, 1, &ok);
  current_rounded_rectangle_->corner_radius_ =
      ok ? radius
         : std::min(current_rounded_rectangle_->width_, current_rounded_rectangle_->height_) / 8;
  doc->Modified();
  doc->shapes_.push_back(current_shape_->Clone());
  current_shape_ = nullptr;
  doc->current_shape_ = nullptr;
}
