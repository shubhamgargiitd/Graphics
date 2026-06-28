#include "tools/individual_tools/move_tool.h"
#include "document.h"

void MoveTool::ApplyTransform(std::unique_ptr<Document>& doc, QPointF current) {
  doc->current_shape_->Move(current - anchor_point_);
  anchor_point_ = current;
}
