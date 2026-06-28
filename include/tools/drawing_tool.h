#pragma once
#include <memory>
#include "shapes/shape.h"
#include "tools/tool.h"

class DrawingTool : public Tool {
protected:
  std::shared_ptr<Shape> current_shape_;
  virtual std::shared_ptr<Shape> MakeShape(std::unique_ptr<Document>& doc) = 0;
  virtual void CalculateParameters() = 0;

public:
  void MousePressed(std::unique_ptr<Document>& doc, QMouseEvent* event) override;
  void MouseMove(std::unique_ptr<Document>& doc, QMouseEvent* event) override;
  void MouseReleased(std::unique_ptr<Document>& doc, QMouseEvent* event) override;
  void KeyboardEvent(std::unique_ptr<Document>&, QKeyEvent*) override {}
  void WriteInDocument(std::unique_ptr<Document>&) override {}
};
