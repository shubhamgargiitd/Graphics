#include <QPainter>

#include "document.h"
#include "main_window.h"


//only called inside paint event
void MainWindow::UpdateToolButtons() {
  if (!tool_manager_->current_tool_) {
    circle_button_->setChecked(false);
    eraser_button_->setChecked(false);
    move_button_->setChecked(false);
    text_button_->setChecked(false);
    rectangle_button_->setChecked(false);
    hexagon_button_->setChecked(false);
    line_button_->setChecked(false);
    rounded_rectangle_button_->setChecked(false);
    freehand_button_->setChecked(false);
    resize_button_->setChecked(false);
    return;
  }
  ToolType toolType = tool_manager_->current_tool_->GetType();
  circle_button_->setChecked(toolType == ToolType::Circle);
  eraser_button_->setChecked(toolType == ToolType::Eraser);
  move_button_->setChecked(toolType == ToolType::Move);
  text_button_->setChecked(toolType == ToolType::Text);
  rectangle_button_->setChecked(toolType == ToolType::Rectangle);
  hexagon_button_->setChecked(toolType == ToolType::Hexagon);
  line_button_->setChecked(toolType == ToolType::Line);
  rounded_rectangle_button_->setChecked(toolType == ToolType::RoundedRect);
  freehand_button_->setChecked(toolType == ToolType::Freehand);
  resize_button_->setChecked(toolType == ToolType::Resize);
}

void MainWindow::UpdateWindowTitle() {
  std::string title;
  if (file_manager_->current_file_->file_name.empty()) {
    title = "Untitled";
  } else {
    title = file_manager_->current_file_->file_name;
  }
  if (document_->is_updated_) {
    title += "*";
  }
  setWindowTitle(QString::fromStdString(title));
}
// clean up before selecting a new tool
void MainWindow::Refresh() {
  if (tool_manager_->current_tool_) tool_manager_->current_tool_->WriteInDocument(document_);
  if (document_->selected_index_ >= 0) {
    document_->selected_index_ = -1;
  }
  update();
}

void MainWindow::paintEvent(QPaintEvent* event) {
  QPainter painter(this);

  //update mainwindow title and tool buttons
  UpdateToolButtons();
  UpdateWindowTitle();

  //paint the shapes in the document
  painter.setRenderHint(QPainter::Antialiasing);
  for (const auto& shape : document_->shapes_) {
    if (shape)  // check for null
      shape->Paint(painter);
  }
  if (document_->current_shape_) {
    document_->current_shape_->Paint(painter);
  }

  // If a shape is selected, draw a dashed blue rectangle around it
  if (document_->selected_index_ >= 0 && document_->selected_index_ < document_->shapes_.size()) {
    QPen selection_pen(Qt::DashLine);
    selection_pen.setColor(Qt::blue);
    selection_pen.setWidth(2);
    painter.setPen(selection_pen);
       painter.setBrush(Qt::NoBrush);
    document_->shapes_[document_->selected_index_]->PaintSurroundingRectangle(painter);
  }
}