#pragma once
#include "shapes/individual_shape/rounded_rectangle.h"
#include "tools/drawing_tool.h"

class RoundedRectangleTool : public DrawingTool {
  std::shared_ptr<RoundedRectangle> current_rounded_rectangle_;
  std::shared_ptr<Shape> MakeShape(std::unique_ptr<Document>& doc) override;
  void CalculateParameters() override;
  void MouseMove(std::unique_ptr<Document>& doc, QMouseEvent* event) override;
  void MouseReleased(std::unique_ptr<Document>& doc, QMouseEvent* event) override;

public:
  ToolType GetType() override { return ToolType::RoundedRect; }
};
