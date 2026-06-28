#include "document.h"

void Document::CheckSelection(QPointF point) {
  for (auto shape = shapes_.rbegin(); shape != shapes_.rend(); ++shape) {
    if ((*shape)->Distance(point) <= tolerance_) {
      selected_index_ = std::distance(shape, shapes_.rend()) - 1;
      return;
    }
  }
}

void Document::Cut() {
  if (selected_index_ >= 0 && selected_index_ < shapes_.size()) {
    Modified();
    clipboard_ = shapes_[selected_index_]->Clone();
    shapes_.erase(shapes_.begin() + selected_index_);
    selected_index_ = -1;
  }
}

void Document::Copy() {
  if (selected_index_ >= 0 && selected_index_ < shapes_.size()) {
    clipboard_ = shapes_[selected_index_]->Clone();
  }
}

void Document::Paste(QPointF point) {
  if (clipboard_) {
    Modified();
    shapes_.push_back(clipboard_->Clone_wrt_movedPosition(point));
  }
}

void Document::Modified() {
  is_updated_ = true;
  undo_stack_.emplace_back();
  for (const auto& shape : shapes_) {
    undo_stack_.back().push_back(shape->Clone());
  }
  // limit undo stack to 50 states
  if (undo_stack_.size() > 50) {
    undo_stack_.erase(undo_stack_.begin());
  }
  redo_stack_.clear();
}

void Document::Undo() {
  if (undo_stack_.empty()) return;
  redo_stack_.emplace_back();
  for (const auto& shape : shapes_) {
    redo_stack_.back().push_back(shape->Clone());
  }
  shapes_ = std::move(undo_stack_.back());
  undo_stack_.pop_back();
  is_updated_ = true;
}

void Document::Redo() {
  if (redo_stack_.empty()) return;
  undo_stack_.emplace_back();
  for (const auto& shape : shapes_) {
    undo_stack_.back().push_back(shape->Clone());
  }
  shapes_ = std::move(redo_stack_.back());
  redo_stack_.pop_back();
  is_updated_ = true;
}
