// initialize the main window and creates objects required in the whole app
#include "main_window.h"

#include <QAction>
#include <QApplication>
#include <QMenuBar>
#include <QMouseEvent>
#include <QPainter>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  resize(800, 600);                         // window size
  setContextMenuPolicy(Qt::NoContextMenu);  // when you right click no default options come
  document_ = std::make_unique<Document>();
  file_manager_ = std::make_unique<FileManager>(this);
  tool_manager_ = std::make_unique<ToolManager>();
  CreateHorizontalToolbar();
  CreateVerticalToolbar();
  CreateMenuBar();
  UpdateWindowTitle();
}

QIcon MainWindow::LoadIcon(const QString &path) {
  QIcon icon(path);
  if (icon.isNull()) {
    return QIcon();  // Return empty icon if file doesn't exist yet
  }
  return icon;
}

MainWindow::~MainWindow() = default;
