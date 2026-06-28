#pragma once
#include "shapes/individual_shape/circle.h"
#include "tools/drawing_tool.h"

class CircleTool : public DrawingTool {
  std::shared_ptr<Circle> current_circle_;
  std::shared_ptr<Shape> MakeShape(std::unique_ptr<Document>& doc) override;
  void CalculateParameters() override;

public:
  ToolType GetType() override { return ToolType::Circle; }
};
