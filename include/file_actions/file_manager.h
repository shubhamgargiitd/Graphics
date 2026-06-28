#pragma once
#include <QWidget>
#include <memory>
#include <string>
#include <vector>

#include "document.h"

struct File {
  std::string file_name = "";
  std::string file_location = "";
};

class FileManager : public QObject {
  Q_OBJECT
public:
  FileManager(QWidget* parent = nullptr);
  ~FileManager() = default;
  QWidget* parent_;

  // current file ptr
  std::unique_ptr<File> current_file_;

  // main functions which are called
  void NewFile(std::unique_ptr<Document>& document);
  void OpenFile(std::unique_ptr<Document>& document);
  void SaveFile(std::unique_ptr<Document>& document);
  void SaveAsFile(std::unique_ptr<Document>& document);
  // helper functions
  std::string AskLocationToOpenFile();
  std::string AskLocationToSaveFile();

  // parser functions
  void Parse(std::string filename, std::unique_ptr<Document>& document);
  void ParseCommand(std::vector<std::string> command, std::unique_ptr<Document>& document);
  void Serializer(std::string filename, std::unique_ptr<Document>& document);
  void ParseCircle(std::vector<std::string> command, std::unique_ptr<Document>& document);
  void ParseText(std::vector<std::string> command, std::unique_ptr<Document>& document);
  void ParseRectangle(std::vector<std::string> command, std::unique_ptr<Document>& document);
  void ParseHexagon(std::vector<std::string> command, std::unique_ptr<Document>& document);
  void ParseLine(std::vector<std::string> command, std::unique_ptr<Document>& document);
  void ParseRoundedRectangle(std::vector<std::string> command, std::unique_ptr<Document>& document);
  void ParseFreehand(std::vector<std::string> command, std::unique_ptr<Document>& document);
};