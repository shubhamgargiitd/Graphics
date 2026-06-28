#include "document.h"
#include "main_window.h"
#include "tools/tool_manager.h"

void MainWindow::mousePressEvent(QMouseEvent *event) {
  document_->current_mouse_position_ = event->pos();

  // if no tool is selected, check for selection
  if (tool_manager_->current_tool_ == nullptr) {
    if (document_->selected_index_ >= 0) {
      document_->selected_index_ = -1;
      update();
    } else {
      document_->CheckSelection(event->pos());
      update();
    }
  } else {  // if tool is selected, call the tool's mouse press event
    tool_manager_->current_tool_->MousePressed(document_, event);
    update();
  }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
  document_->current_mouse_position_ = event->pos();
  if (tool_manager_->current_tool_ == nullptr) return;
  tool_manager_->current_tool_->MouseMove(document_, event);
  update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
  document_->current_mouse_position_ = event->pos();
  if (tool_manager_->current_tool_ == nullptr) return;
  tool_manager_->current_tool_->MouseReleased(document_, event);
  update();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  // If text tool is active, all keyboard input goes to it
  if (tool_manager_->current_tool_ && tool_manager_->current_tool_->GetType() == ToolType::Text) {
    tool_manager_->current_tool_->KeyboardEvent(document_, event);
    update();
    return;
  }

  if (event->matches(QKeySequence::Cut)) {
    document_->Cut();
    update();
    return;
  }

  if (event->matches(QKeySequence::Copy)) {
    document_->Copy();
    return;
  }

  if (event->matches(QKeySequence::Paste)) {
    if (document_->clipboard_ == nullptr) return;
    document_->Paste(document_->current_mouse_position_);
    update();
    return;
  }

  if (event->matches(QKeySequence::Undo)) {
    document_->Undo();
    update();
    return;
  }

  if (event->matches(QKeySequence::Redo)) {
    document_->Redo();
    update();
    return;
  }

  if (tool_manager_->current_tool_ == nullptr) return;
  tool_manager_->current_tool_->KeyboardEvent(document_, event);
  update();
}