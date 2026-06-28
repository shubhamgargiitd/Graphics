#include "tools/individual_tools/eraser_tool.h"

#include <QPointF>

#include "document.h"

void EraserTool::Erase(std::unique_ptr<Document>& document, QPointF point) {
  std::vector<int> indices_to_be_deleted;
  // erase from the end because it would be the upper element in the vector
  for (int i = document->shapes_.size() - 1; i >= 0; i--) {
    if (document->shapes_[i]->Distance(point) < document->tolerance_) {
      indices_to_be_deleted.push_back(i);
    }
  }
  for (int index : indices_to_be_deleted) {
    document->Modified();  // Mark the document as modified before erasing the shape
    document->shapes_.erase(document->shapes_.begin() + index);
  }
}

void EraserTool::MousePressed(std::unique_ptr<Document>& document, QMouseEvent* event) {
  QPointF point = event->pos();
  Erase(document, point);
}

void EraserTool::MouseMove(std::unique_ptr<Document>& document, QMouseEvent* event) {
  QPointF point = event->pos();
  Erase(document, point);
}

void EraserTool::MouseReleased(std::unique_ptr<Document>& document, QMouseEvent* event) {
  QPointF point = event->pos();
  Erase(document, point);
}

void EraserTool::KeyboardEvent(std::unique_ptr<Document>& document, QKeyEvent* event) {}

void EraserTool::WriteInDocument(std::unique_ptr<Document>& document) {
  // Eraser tool has no pending state to save
}

ToolType EraserTool::GetType() { return ToolType::Eraser; }
