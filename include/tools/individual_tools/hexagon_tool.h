#pragma once
#include "shapes/individual_shape/hexagon.h"
#include "tools/drawing_tool.h"

class HexagonTool : public DrawingTool {
  std::shared_ptr<Hexagon> current_hexagon_;
  std::shared_ptr<Shape> MakeShape(std::unique_ptr<Document>& doc) override;
  void CalculateParameters() override;

public:
  ToolType GetType() override { return ToolType::Hexagon; }
};
