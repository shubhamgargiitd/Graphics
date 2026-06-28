#include "file_actions/file_manager.h"

#include <QFileDialog>
#include <QMessageBox>
#include <filesystem>
#include <fstream>

#include "document.h"
#include "utils/utils.h"

FileManager::FileManager(QWidget* parent) : parent_(parent) {
  current_file_ = std::make_unique<File>();
}

void FileManager::NewFile(std::unique_ptr<Document>& document) {
  if (document->is_updated_) {
    auto reply = QMessageBox::question(parent_, "Save Changes", "Do you want to save changes?",
                                       QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if (reply == QMessageBox::Yes) {
      SaveFile(document);
    } else if (reply == QMessageBox::Cancel) {
      return;
    }
  }
  document->shapes_.clear();
  document->undo_stack_.clear();
  document->redo_stack_.clear();
  document->is_updated_ = false;
  current_file_->file_name = "";
  current_file_->file_location = "";
  parent_->update();
}

void FileManager::OpenFile(std::unique_ptr<Document>& document) {
  if (document->is_updated_) {
    auto reply = QMessageBox::question(parent_, "Save Changes", "Do you want to save changes?",
                                       QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if (reply == QMessageBox::Yes) {
      SaveFile(document);
    } else if (reply == QMessageBox::Cancel) {
      return;
    }
  }
  std::string file_location = AskLocationToOpenFile();
  if (file_location.empty()) return;

  document->shapes_.clear();
  Parse(file_location, document);
  current_file_->file_location = file_location;
  current_file_->file_name = split(split(file_location, '/').back(), '.')[0];
  document->is_updated_ = false;
}

void FileManager::SaveFile(std::unique_ptr<Document>& document) {
  if (current_file_->file_location.empty()) {
    current_file_->file_location = AskLocationToSaveFile();
    if (current_file_->file_location.empty()) return;
    current_file_->file_name = split(split(current_file_->file_location, '/').back(), '.')[0];
  }
  Serializer(current_file_->file_location, document);
  document->is_updated_ = false;
}

void FileManager::SaveAsFile(std::unique_ptr<Document>& document) {
  current_file_->file_location = AskLocationToSaveFile();
  if (current_file_->file_location.empty()) return;
  current_file_->file_name = split(split(current_file_->file_location, '/').back(), '.')[0];
  Serializer(current_file_->file_location, document);
  document->is_updated_ = false;
}

std::string FileManager::AskLocationToOpenFile() {
  QString fileName = QFileDialog::getOpenFileName(
      nullptr, "Open File",
      QString::fromStdString(std::filesystem::current_path().string() + "/../xml_directory"),
      "SVG Files (*.svg);;All Files (*)");
  return fileName.toStdString();
}

std::string FileManager::AskLocationToSaveFile() {
  QString fileName = QFileDialog::getSaveFileName(
      nullptr, "Save File",
      QString::fromStdString(std::filesystem::current_path().string() + "/../xml_directory"),
      "SVG Files (*.svg);;All Files (*)");
  return fileName.toStdString();
}

void FileManager::Serializer(std::string filename, std::unique_ptr<Document>& document) {
  std::ofstream file(filename);
  if (!file.is_open()) return;
  file << "<svg \n width=\"800\" \n height=\"600\" \n xmlns=\"http://www.w3.org/2000/svg\" \n >\n";
  for (const auto& shape : document->shapes_) {
    if (shape) file << shape->Serialize();
  }
  file << "</svg>\n";
}
