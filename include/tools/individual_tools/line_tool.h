#pragma once
#include "shapes/individual_shape/line.h"
#include "tools/drawing_tool.h"

class LineTool : public DrawingTool {
  std::shared_ptr<Line> current_line_;
  std::shared_ptr<Shape> MakeShape(std::unique_ptr<Document>& doc) override;
  void CalculateParameters() override;

public:
  ToolType GetType() override { return ToolType::Line; }
};
