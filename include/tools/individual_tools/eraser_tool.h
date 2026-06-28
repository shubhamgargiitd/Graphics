#pragma once
#include "document.h"
#include "tools/tool.h"

class EraserTool : public Tool {
public:
  void MousePressed(std::unique_ptr<Document>& document, QMouseEvent* event) override;
  void MouseMove(std::unique_ptr<Document>& document, QMouseEvent* event) override;
  void MouseReleased(std::unique_ptr<Document>& document, QMouseEvent* event) override;
  void KeyboardEvent(std::unique_ptr<Document>& document, QKeyEvent* event) override;
  void Erase(std::unique_ptr<Document>& document, QPointF point);
  ToolType GetType() override;
  void WriteInDocument(std::unique_ptr<Document>& document) override;
};
