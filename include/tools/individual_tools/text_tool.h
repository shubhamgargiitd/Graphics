#pragma once
#include "shapes/individual_shape/text.h"
#include "tools/tool.h"

class TextTool : public Tool {
  QPointF text_position_;
  std::shared_ptr<Text> current_text_;

public:
  void MousePressed(std::unique_ptr<Document>& document, QMouseEvent* event) override;
  void MouseMove(std::unique_ptr<Document>& document, QMouseEvent* event) override;
  void MouseReleased(std::unique_ptr<Document>& document, QMouseEvent* event) override;
  void KeyboardEvent(std::unique_ptr<Document>& document, QKeyEvent* event) override;
  void WriteInDocument(std::unique_ptr<Document>& document) override;
  ToolType GetType() override;
};
