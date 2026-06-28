#include "tools/manipulation_tool.h"
#include "document.h"

void ManipulationTool::MousePressed(std::unique_ptr<Document>& doc, QMouseEvent* event) {
  doc->CheckSelection(event->pos());
  if (doc->selected_index_ < 0 || doc->selected_index_ >= (int)doc->shapes_.size()) return;
  doc->Modified();
  shape_index_ = doc->selected_index_;
  doc->current_shape_ = doc->shapes_[shape_index_]->Clone();
  doc->shapes_.erase(doc->shapes_.begin() + shape_index_);
  doc->selected_index_ = -1;
  anchor_point_ = event->pos();
}

void ManipulationTool::MouseMove(std::unique_ptr<Document>& doc, QMouseEvent* event) {
  if (!doc->current_shape_) return;
  ApplyTransform(doc, event->pos());
}

void ManipulationTool::MouseReleased(std::unique_ptr<Document>& doc, QMouseEvent* event) {
  if (!doc->current_shape_) return;
  doc->shapes_.push_back(doc->current_shape_->Clone());
  doc->current_shape_ = nullptr;
  shape_index_ = -1;
}
