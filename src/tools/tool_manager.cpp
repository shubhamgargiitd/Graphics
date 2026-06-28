// stores the current state of the application,what all objects have been stored,which tool is
// selected and so on.
#include "tools/tool_manager.h"

// #include <iostream>

ToolManager::ToolManager() {
  current_tool_ = nullptr;
  circle_tool_ = std::make_shared<CircleTool>();  // shared with current tool
  eraser_tool_ = std::make_shared<EraserTool>();
  move_tool_ = std::make_shared<MoveTool>();
  text_tool_ = std::make_shared<TextTool>();
  rectangle_tool_ = std::make_shared<RectangleTool>();
  hexagon_tool_ = std::make_shared<HexagonTool>();
  line_tool_ = std::make_shared<LineTool>();
  rounded_rectangle_tool_ = std::make_shared<RoundedRectangleTool>();
  freehand_tool_ = std::make_shared<FreehandTool>();
  resize_tool_ = std::make_shared<ResizeTool>();
}

void ToolManager::SelectCircleTool() {
  current_tool_ = (current_tool_ && current_tool_->GetType() == ToolType::Circle) ? nullptr : circle_tool_;
}

void ToolManager::SelectEraserTool() {
  current_tool_ = (current_tool_ && current_tool_->GetType() == ToolType::Eraser) ? nullptr : eraser_tool_;
}

void ToolManager::SelectMoveTool() {
  current_tool_ = (current_tool_ && current_tool_->GetType() == ToolType::Move) ? nullptr : move_tool_;
}

void ToolManager::SelectTextTool() {
  current_tool_ = (current_tool_ && current_tool_->GetType() == ToolType::Text) ? nullptr : text_tool_;
}

void ToolManager::SelectRectangleTool() {
  current_tool_ = (current_tool_ && current_tool_->GetType() == ToolType::Rectangle) ? nullptr : rectangle_tool_;
}

void ToolManager::SelectHexagonTool() {
  current_tool_ = (current_tool_ && current_tool_->GetType() == ToolType::Hexagon) ? nullptr : hexagon_tool_;
}

void ToolManager::SelectLineTool() {
  current_tool_ = (current_tool_ && current_tool_->GetType() == ToolType::Line) ? nullptr : line_tool_;
}

void ToolManager::SelectRoundedRectangleTool() {
  current_tool_ = (current_tool_ && current_tool_->GetType() == ToolType::RoundedRect) ? nullptr : rounded_rectangle_tool_;
}

void ToolManager::SelectFreehandTool() {
  current_tool_ = (current_tool_ && current_tool_->GetType() == ToolType::Freehand) ? nullptr : freehand_tool_;
}

void ToolManager::SelectResizeTool() {
  current_tool_ = (current_tool_ && current_tool_->GetType() == ToolType::Resize) ? nullptr : resize_tool_;
}
