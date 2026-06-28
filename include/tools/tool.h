#pragma once
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPointF>
#include <memory>
#include "types.h"

class Document;

class Tool {
protected:
  QPointF start_point_;
  QPointF ending_point_;
  QPointF current_point_;

public:
  virtual void MousePressed(std::unique_ptr<Document>& document, QMouseEvent* event) = 0;
  virtual void MouseMove(std::unique_ptr<Document>& document, QMouseEvent* event) = 0;
  virtual void MouseReleased(std::unique_ptr<Document>& document, QMouseEvent* event) = 0;
  virtual void KeyboardEvent(std::unique_ptr<Document>& document, QKeyEvent* event) = 0;
  virtual ToolType GetType() = 0;
  virtual void WriteInDocument(std::unique_ptr<Document>& document) = 0;
  virtual ~Tool() = default;
};
