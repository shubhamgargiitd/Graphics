#pragma once
#include <QPoint>

#include "shapes/individual_shape/freehand.h"
#include "tools/tool.h"

class FreehandTool : public Tool {
  std::shared_ptr<Freehand> current_freehand_;

public:
  void MousePressed(std::unique_ptr<Document>& document, QMouseEvent* event) override;
  void MouseMove(std::unique_ptr<Document>& document, QMouseEvent* event) override;
  void MouseReleased(std::unique_ptr<Document>& document, QMouseEvent* event) override;
  void KeyboardEvent(std::unique_ptr<Document>& document, QKeyEvent* event) override;
  ToolType GetType() override;
  void WriteInDocument(std::unique_ptr<Document>& document) override;
};
