// contains mainwindow,canva, menu_bar,tool_bar,mouse_events,keyboard_events
#pragma once
#include <QIcon>
#include <QMainWindow>
#include <QPointF>
#include <QPushButton>

#include "file_actions/file_manager.h"
#include "tools/individual_tools/circle_tool.h"
#include "tools/tool.h"
#include "tools/tool_manager.h"

class Document;

class MainWindow : public QMainWindow {
Q_OBJECT  // macro for detecting signals and slots(making announcements),generates code which links
          // the various slots
    public : MainWindow(QWidget *parent = nullptr);

  // declare the event handlers
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void paintEvent(QPaintEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;

  // create menubar and toolbar
  void MakeVerticalToolbarButton(QPushButton *button, QString icon_path, QString tooltip);
  void MakeHorizontalToolbarButton(QPushButton *button, QString icon_path, QString tooltip);
  void CreateHorizontalToolbar();
  void CreateVerticalToolbar();
  void CreateMenuBar();

  // load icons
  QIcon LoadIcon(const QString &path);

  // main objects of the application
  std::unique_ptr<Document> document_;
  std::unique_ptr<ToolManager> tool_manager_;
  std::unique_ptr<FileManager> file_manager_;

  // tool buttons for vertical toolbar
  QPushButton *circle_button_;
  QPushButton *eraser_button_;
  QPushButton *move_button_;
  QPushButton *text_button_;
  QPushButton *rectangle_button_;
  QPushButton *hexagon_button_;
  QPushButton *line_button_;
  QPushButton *rounded_rectangle_button_;
  QPushButton *freehand_button_;
  QPushButton *resize_button_;

  // updating various aspects of the window
  void UpdateToolButtons();
  void UpdateWindowTitle();
  void Refresh();

  // destructor
  ~MainWindow();
};
