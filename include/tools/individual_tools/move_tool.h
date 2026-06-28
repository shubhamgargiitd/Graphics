#pragma once
#include "tools/manipulation_tool.h"

class MoveTool : public ManipulationTool {
  void ApplyTransform(std::unique_ptr<Document>& doc, QPointF current) override;

public:
  ToolType GetType() override { return ToolType::Move; }
};
