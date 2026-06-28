#include "tools/individual_tools/text_tool.h"

#include <QKeyEvent>

#include "document.h"

void TextTool::MousePressed(std::unique_ptr<Document>& document, QMouseEvent* event) {
  if (current_text_) {
    WriteInDocument(document);
  }
  // std::cerr << "Text Tool Activated" << std::endl;
  text_position_ = event->pos();
  current_text_ = std::make_shared<Text>();
  current_text_->position_ = text_position_;
  current_text_->content_ = "|";  // cursor
  current_text_->fill_color_ = document->fill_color_;
  current_text_->stroke_color_ = document->stroke_color_;
  current_text_->stroke_width_ = document->stroke_width_;
  current_text_->has_fill_ = document->has_fill_;
  current_text_->font_size_ = document->font_size_;
  document->current_shape_ = current_text_;
}

void TextTool::MouseMove(std::unique_ptr<Document>& document, QMouseEvent* event) {
  // No action on mouse move for text tool
}

void TextTool::MouseReleased(std::unique_ptr<Document>& document, QMouseEvent* event) {
  // No action on mouse release for text tool
}

void TextTool::WriteInDocument(std::unique_ptr<Document>& document) {
  if (!current_text_) return;

  if (current_text_->content_.length() > 1) {  // More than just cursor
    document->Modified();
    current_text_->content_.remove(current_text_->content_.length() - 1, 1);  // Remove cursor
    document->shapes_.push_back(std::make_unique<Text>(*current_text_));
  }
  current_text_ = nullptr;
  document->current_shape_ = nullptr;
}

void TextTool::KeyboardEvent(std::unique_ptr<Document>& document, QKeyEvent* event) {
  if (!current_text_) return;
  if (event->key() == Qt::Key_Escape) {
    WriteInDocument(document);
  } else if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
    // Add \n to current text content before cursor
    current_text_->content_.insert(current_text_->content_.length() - 1, '\n');
  } else if (event->key() == Qt::Key_Backspace) {
    // Remove character before cursor
    if (current_text_->content_.length() > 1) {
      current_text_->content_.remove(current_text_->content_.length() - 2, 1);
    }
  } else if (!event->text().isEmpty()) {
    QString text = event->text();
    // Insert text before cursor
    current_text_->content_.insert(current_text_->content_.length() - 1, text);
  }
}

ToolType TextTool::GetType() { return ToolType::Text; }
