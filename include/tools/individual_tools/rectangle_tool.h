#pragma once
#include "shapes/individual_shape/rectangle.h"
#include "tools/drawing_tool.h"

class RectangleTool : public DrawingTool {
  std::shared_ptr<Rectangle> current_rectangle_;
  std::shared_ptr<Shape> MakeShape(std::unique_ptr<Document>& doc) override;
  void CalculateParameters() override;

public:
  ToolType GetType() override { return ToolType::Rectangle; }
};
