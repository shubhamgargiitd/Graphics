#include "tools/individual_tools/resize_tool.h"
#include "document.h"

void ResizeTool::ApplyTransform(std::unique_ptr<Document>& doc, QPointF current) {
  doc->current_shape_->Resize(anchor_point_, current);
  anchor_point_ = current;
}
