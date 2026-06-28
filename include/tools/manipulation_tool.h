#pragma once
#include "tools/tool.h"

class ManipulationTool : public Tool {
protected:
  int shape_index_ = -1;
  QPointF anchor_point_;
  virtual void ApplyTransform(std::unique_ptr<Document>& doc, QPointF current) = 0;

public:
  void MousePressed(std::unique_ptr<Document>& doc, QMouseEvent* event) override;
  void MouseMove(std::unique_ptr<Document>& doc, QMouseEvent* event) override;
  void MouseReleased(std::unique_ptr<Document>& doc, QMouseEvent* event) override;
  void KeyboardEvent(std::unique_ptr<Document>&, QKeyEvent*) override {}
  void WriteInDocument(std::unique_ptr<Document>&) override {}
};
