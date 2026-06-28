#include <QIcon>
#include <QPushButton>
#include <QToolBar>

#include "main_window.h"

void MainWindow::MakeVerticalToolbarButton(QPushButton *button, QString icon_path,
                                           QString tooltip) {
  button->setIcon(LoadIcon(icon_path));
  button->setIconSize(QSize(32, 32));
  button->setToolTip(tooltip);  // while hovering over it
  button->setFocusPolicy(
      Qt::NoFocus);  // so that no keyboard letters should activate it in between writing text
  button->setFixedSize(40, 40);
  button->setCheckable(true);  // showing that this is the button selected
  button->setStyleSheet(
      "QPushButton { border: 1px solid gray; } QPushButton:checked { background-color: lightblue; "
      "border: 2px solid blue; }");
}

void MainWindow::CreateVerticalToolbar() {
  QToolBar *verticalToolbar = new QToolBar("Tools");
  verticalToolbar->setMovable(false);
  verticalToolbar->setContextMenuPolicy(Qt::PreventContextMenu);
  addToolBar(Qt::LeftToolBarArea, verticalToolbar);

  // Create all tool buttons (checkable, 32px icon, 40px button)
  circle_button_ = new QPushButton();
  MakeVerticalToolbarButton(circle_button_, "icons/vertical/circle.svg", "Circle");
  rectangle_button_ = new QPushButton();
  MakeVerticalToolbarButton(rectangle_button_, "icons/vertical/rectangle.svg", "Rectangle");
  rounded_rectangle_button_ = new QPushButton();
  MakeVerticalToolbarButton(rounded_rectangle_button_, "icons/vertical/rounded_rect.svg",
                            "Rounded Rectangle");
  hexagon_button_ = new QPushButton();
  MakeVerticalToolbarButton(hexagon_button_, "icons/vertical/hexagon.svg", "Hexagon");
  line_button_ = new QPushButton();
  MakeVerticalToolbarButton(line_button_, "icons/vertical/line.svg", "Line");
  freehand_button_ = new QPushButton();
  MakeVerticalToolbarButton(freehand_button_, "icons/vertical/freehand.svg", "Freehand");
  text_button_ = new QPushButton();
  MakeVerticalToolbarButton(text_button_, "icons/vertical/text.svg", "Text");
  move_button_ = new QPushButton();
  MakeVerticalToolbarButton(move_button_, "icons/vertical/move.svg", "Move");
  resize_button_ = new QPushButton();
  MakeVerticalToolbarButton(resize_button_, "icons/vertical/resize.svg", "Resize");
  eraser_button_ = new QPushButton();
  MakeVerticalToolbarButton(eraser_button_, "icons/vertical/eraser.svg", "Eraser");

  // Add buttons to toolbar
  verticalToolbar->addWidget(circle_button_);
  verticalToolbar->addWidget(rectangle_button_);
  verticalToolbar->addWidget(rounded_rectangle_button_);
  verticalToolbar->addWidget(hexagon_button_);
  verticalToolbar->addWidget(line_button_);
  verticalToolbar->addWidget(freehand_button_);
  verticalToolbar->addWidget(text_button_);
  verticalToolbar->addSeparator();
  verticalToolbar->addWidget(move_button_);
  verticalToolbar->addWidget(resize_button_);
  verticalToolbar->addWidget(eraser_button_);

  // call functions when buttons are
  connect(circle_button_,            &QPushButton::clicked, [this]() { Refresh(); tool_manager_->SelectCircleTool();           update(); });
  connect(rectangle_button_,         &QPushButton::clicked, [this]() { Refresh(); tool_manager_->SelectRectangleTool();        update(); });
  connect(rounded_rectangle_button_, &QPushButton::clicked, [this]() { Refresh(); tool_manager_->SelectRoundedRectangleTool(); update(); });
  connect(hexagon_button_,           &QPushButton::clicked, [this]() { Refresh(); tool_manager_->SelectHexagonTool();          update(); });
  connect(line_button_,              &QPushButton::clicked, [this]() { Refresh(); tool_manager_->SelectLineTool();             update(); });
  connect(freehand_button_,          &QPushButton::clicked, [this]() { Refresh(); tool_manager_->SelectFreehandTool();         update(); });
  connect(text_button_,              &QPushButton::clicked, [this]() { Refresh(); tool_manager_->SelectTextTool();             update(); });
  connect(move_button_,              &QPushButton::clicked, [this]() { Refresh(); tool_manager_->SelectMoveTool();             update(); });
  connect(resize_button_,            &QPushButton::clicked, [this]() { Refresh(); tool_manager_->SelectResizeTool();           update(); });
  connect(eraser_button_,            &QPushButton::clicked, [this]() { Refresh(); tool_manager_->SelectEraserTool();           update(); });
}
