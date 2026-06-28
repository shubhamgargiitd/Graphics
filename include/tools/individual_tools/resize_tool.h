#pragma once
#include "tools/manipulation_tool.h"

class ResizeTool : public ManipulationTool {
  void ApplyTransform(std::unique_ptr<Document>& doc, QPointF current) override;

public:
  ToolType GetType() override { return ToolType::Resize; }
};
