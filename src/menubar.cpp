#include <QApplication>
#include <QMenuBar>
#include <QMessageBox>

#include "main_window.h"

void MainWindow::CreateMenuBar() {
  // Create menus
  menuBar()->setNativeMenuBar(false);  // Menu bar appears in the application window

  QMenu *fileMenu = menuBar()->addMenu("File");  // menuBar() is function of QMainWindow
  fileMenu->setFocusPolicy(Qt::NoFocus);  // Remove focus from menu items to prevent accidental
                                          // activation with keyboard shortcuts

  QMenu *editMenu = menuBar()->addMenu("Edit");
  editMenu->setFocusPolicy(Qt::NoFocus);  // Remove focus from menu items to prevent accidental
                                          // activation with keyboard shortcuts

  // Create and add File menu actions
  QAction *saveAction = fileMenu->addAction("Save");
  QAction *openAction = fileMenu->addAction("Open");
  QAction *newAction = fileMenu->addAction("New");
  QAction *saveAsAction = fileMenu->addAction("Save As");
  QAction *closeAction = fileMenu->addAction("Close");

  // Create and add Edit menu actions
  QAction *undoAction = editMenu->addAction("Undo");
  QAction *redoAction = editMenu->addAction("Redo");
  QAction *cutAction = editMenu->addAction("Cut");
  QAction *copyAction = editMenu->addAction("Copy");
  QAction *pasteAction = editMenu->addAction("Paste");

  // Now connect the actions to their respective slots in FileManager and Document
  //  Connect File menu actions
  connect(saveAction, &QAction::triggered, [this]() {
    file_manager_->SaveFile(document_);
    Refresh();
  });

  connect(openAction, &QAction::triggered, [this]() {
    file_manager_->OpenFile(document_);
    Refresh();
  });

  connect(newAction, &QAction::triggered, [this]() {
    file_manager_->NewFile(document_);
    Refresh();
  });

  connect(saveAsAction, &QAction::triggered, [this]() {
    file_manager_->SaveAsFile(document_);
    Refresh();
  });

  connect(closeAction, &QAction::triggered, [this]() {
    if (document_->is_updated_) {
      auto reply =
          QMessageBox::question(this, "Save Changes", "Do you want to save changes before closing?",
                                QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

      if (reply == QMessageBox::Yes) {
        file_manager_->SaveFile(document_);
        QApplication::quit();
      } else if (reply == QMessageBox::No) {
        QApplication::quit();
      }
      // If Cancel, do nothing (don't close)
    } else {
      QApplication::quit();
    }
  });

  // Connect Edit menu actions
  connect(undoAction, &QAction::triggered, [this]() {
    document_->Undo();
    Refresh();
  });

  connect(redoAction, &QAction::triggered, [this]() {
    document_->Redo();
    Refresh();
  });

  connect(cutAction, &QAction::triggered, [this]() {
    document_->Cut();
    Refresh();
  });

  connect(copyAction, &QAction::triggered, [this]() {
    document_->Copy();
    Refresh();
  });

  connect(pasteAction, &QAction::triggered, [this]() {
    if (document_->clipboard_ == nullptr) return;
    document_->Paste(document_->clipboard_->GetCenter() + QPointF(10, 10));
    Refresh();
  });
}
