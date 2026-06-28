// draws a freehand path
#include "tools/individual_tools/freehand_tool.h"

#include "document.h"

void FreehandTool::MousePressed(std::unique_ptr<Document>& document, QMouseEvent* event) {
  //   std::cerr << "Drawing Freehand" << std::endl;
  current_freehand_ = std::make_shared<Freehand>();
  current_freehand_->fill_color_ = document->fill_color_;
  current_freehand_->stroke_color_ = document->stroke_color_;
  current_freehand_->stroke_width_ = document->stroke_width_;
  current_freehand_->has_fill_ = false;  // Freehand is always unfilledi
  // Add the starting point
  current_freehand_->points_.push_back(event->pos());

  document->current_shape_ = current_freehand_;  // for real time drawing
}

void FreehandTool::MouseMove(std::unique_ptr<Document>& document, QMouseEvent* event) {
  if (!current_freehand_) return;  // If no freehand is being drawn, do nothing
  // Add the current point to the path
  current_freehand_->points_.push_back(event->pos());
  document->current_shape_ = current_freehand_;  // for real time drawing
}

void FreehandTool::MouseReleased(std::unique_ptr<Document>& document, QMouseEvent* event) {
  if (!current_freehand_) return;  // If no freehand was being drawn, do nothing
  // Add the final point
  current_freehand_->points_.push_back(event->pos());
  document->Modified();  // Mark the document as modified before adding the shape
  document->shapes_.push_back(std::make_unique<Freehand>(*current_freehand_));
  // delete the current freehand and reset the pointer
  current_freehand_ = nullptr;
  document->current_shape_ = nullptr;
}

void FreehandTool::KeyboardEvent(std::unique_ptr<Document>& document, QKeyEvent* event) {
  // No specific keyboard handling for freehand tool yet
}

void FreehandTool::WriteInDocument(std::unique_ptr<Document>& document) {
  // Freehand tool has no pending state to save
}

ToolType FreehandTool::GetType() { return ToolType::Freehand; }
