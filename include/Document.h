#pragma once
#include <memory>
#include <vector>

#include "QColor"
#include "QPointF"
#include "shapes/shape.h"

class Document {
public:
  Document()
      : is_updated_(false),
        fill_color_(Qt::green),
        has_fill_(false),
        stroke_color_(Qt::magenta),
        stroke_width_(4.0f),
        font_size_(24) {}

  // member variables
  std::vector<std::unique_ptr<Shape>> shapes_;  // stores all the shapes
  bool is_updated_;                             // checks if any pending changes to be saved
  const double tolerance_ = 10.0;
  QColor fill_color_;
  bool has_fill_;
  QColor stroke_color_;
  float stroke_width_;
  int font_size_;
  std::shared_ptr<Shape> current_shape_;  // stores the shape currently being drawn
  std::vector<std::vector<std::unique_ptr<Shape>>> undo_stack_;  // stores the history of shapes
  std::vector<std::vector<std::unique_ptr<Shape>>> redo_stack_;  // stores the redo history of
                                                                 // shapes
  std::unique_ptr<Shape> clipboard_;                             // stores the clipboard
  int selected_index_ = -1;         // stores the index of the selected shape
  QPointF current_mouse_position_;  // stores the current mouse position

  // member functions
  void CheckSelection(QPointF point);  // checks if any shape is selected
  void Modified();                     // updates undo and redo stack
  void Undo();
  void Redo();
  void Cut();
  void Copy();
  void Paste(QPointF point);
};
