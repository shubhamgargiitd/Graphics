#include "tools/drawing_tool.h"
#include "document.h"

void DrawingTool::MousePressed(std::unique_ptr<Document>& doc, QMouseEvent* event) {
  current_shape_ = MakeShape(doc);
  start_point_ = current_point_ = event->pos();
  CalculateParameters();
  doc->current_shape_ = current_shape_;
}

void DrawingTool::MouseMove(std::unique_ptr<Document>& doc, QMouseEvent* event) {
  if (!current_shape_) return;
  current_point_ = event->pos();
  CalculateParameters();
  doc->current_shape_ = current_shape_;
}

void DrawingTool::MouseReleased(std::unique_ptr<Document>& doc, QMouseEvent* event) {
  if (!current_shape_) return;
  ending_point_ = current_point_ = event->pos();
  CalculateParameters();
  doc->Modified();
  doc->shapes_.push_back(current_shape_->Clone());
  current_shape_ = nullptr;
  doc->current_shape_ = nullptr;
}
