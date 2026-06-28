#include "file_actions/file_manager.h"

#include <QColor>
#include <QPointF>
#include <QString>
#include <fstream>
#include <iostream>
#include <sstream>

#include "document.h"
#include "shapes/individual_shape/circle.h"
#include "shapes/individual_shape/freehand.h"
#include "shapes/individual_shape/hexagon.h"
#include "shapes/individual_shape/line.h"
#include "shapes/individual_shape/rectangle.h"
#include "shapes/individual_shape/rounded_rectangle.h"
#include "shapes/individual_shape/text.h"
#include "utils/utils.h"

void FileManager::ParseCommand(std::vector<std::string> command,
                               std::unique_ptr<Document>& document) {
  if (command.empty()) return;
  int start_index = 0;
  while (start_index < (int)command.size() && command[start_index].empty()) start_index++;
  if (start_index == (int)command.size()) return;

  std::string maintag = command[start_index];
  if (maintag.find("circle") != std::string::npos)
    ParseCircle(command, document);
  else if (maintag.find("text") != std::string::npos)
    ParseText(command, document);
  else if (maintag.find("rounded_rect") != std::string::npos)
    ParseRoundedRectangle(command, document);
  else if (maintag.find("rect") != std::string::npos)
    ParseRectangle(command, document);
  else if (maintag.find("polygon") != std::string::npos)
    ParseHexagon(command, document);
  else if (maintag.find("line") != std::string::npos)
    ParseLine(command, document);
  else if (maintag.find("path") != std::string::npos)
    ParseFreehand(command, document);
}

void FileManager::Parse(std::string filename, std::unique_ptr<Document>& document) {
  std::ifstream file(filename);
  if (!file.is_open()) return;

  std::string line;
  std::vector<std::string> command;

  // skip the opening <svg ...> tag
  while (getline(file, line)) {
    line = trim(line);
    if (line.empty()) continue;
    command.push_back(line);
    if (line.find(">") != std::string::npos) { command.clear(); break; }
  }

  while (getline(file, line)) {
    line = trim(line);
    if (line == "</svg>") break;
    if (line.find("/") != std::string::npos && line.find(">") != std::string::npos) {
      ParseCommand(command, document);
      command.clear();
    } else {
      command.push_back(line);
    }
  }
}

// ── helpers ───────────────────────────────────────────────────────────────────

static std::vector<std::string> cleanCommand(std::vector<std::string> command) {
  std::vector<std::string> out;
  for (auto& s : command)
    if (!s.empty()) out.push_back(s);
  return out;
}

struct StyleAttrs { QColor fill, stroke; float stroke_w; bool has_fill; };

static StyleAttrs parseStyle(const std::string& style_line) {
  auto tokens     = split(split(style_line, '"')[1], ';');
  QColor fill     = QColor(QString::fromStdString(split(tokens[0], ':')[1]));
  bool has_fill   = (split(tokens[1], ':')[1] == "1");
  QColor stroke   = QColor(QString::fromStdString(split(tokens[2], ':')[1]));
  float  stroke_w = std::stof(split(tokens[3], ':')[1]);
  return {fill, stroke, stroke_w, has_fill};
}

// ── shape parsers ─────────────────────────────────────────────────────────────

void FileManager::ParseCircle(std::vector<std::string> command,
                              std::unique_ptr<Document>& document) {
  command = cleanCommand(command);
  if (command.size() != 5) return;

  auto s  = parseStyle(command[1]);
  double cx = std::stod(split(command[2], '"')[1]);
  double cy = std::stod(split(command[3], '"')[1]);
  double r  = std::stod(split(command[4], '"')[1]);

  document->shapes_.push_back(
      std::make_unique<Circle>(QPointF(cx, cy), r, s.fill, s.stroke, s.stroke_w, s.has_fill));
}

void FileManager::ParseRectangle(std::vector<std::string> command,
                                 std::unique_ptr<Document>& document) {
  command = cleanCommand(command);
  if (command.size() != 6) return;

  auto s        = parseStyle(command[1]);
  double x      = std::stod(split(command[2], '"')[1]);
  double y      = std::stod(split(command[3], '"')[1]);
  double width  = std::stod(split(command[4], '"')[1]);
  double height = std::stod(split(command[5], '"')[1]);

  document->shapes_.push_back(std::make_unique<Rectangle>(
      QPointF(x, y), width, height, s.fill, s.stroke, s.stroke_w, s.has_fill));
}

void FileManager::ParseRoundedRectangle(std::vector<std::string> command,
                                        std::unique_ptr<Document>& document) {
  command = cleanCommand(command);
  if (command.size() < 7) {
    std::cerr << "SVG file for rounded rectangle not correct" << std::endl;
    return;
  }

  auto style_tokens    = split(split(command[1], '"')[1], ';');
  std::string fill_str = split(style_tokens[0], ':')[1];
  bool   has_fill      = (fill_str != "none");
  QColor fill_color    = has_fill ? QColor(QString::fromStdString(fill_str)) : Qt::white;
  QColor stroke_color  = QColor(QString::fromStdString(split(style_tokens[1], ':')[1]));
  float  stroke_w      = std::stof(split(style_tokens[2], ':')[1]);
  double x             = std::stod(split(command[2], '"')[1]);
  double y             = std::stod(split(command[3], '"')[1]);
  double width         = std::stod(split(command[4], '"')[1]);
  double height        = std::stod(split(command[5], '"')[1]);
  double corner_radius = std::stod(split(command[6], '"')[1]);

  document->shapes_.push_back(std::make_unique<RoundedRectangle>(
      QPointF(x, y), width, height, corner_radius, fill_color, stroke_color, stroke_w, has_fill));
}

void FileManager::ParseHexagon(std::vector<std::string> command,
                               std::unique_ptr<Document>& document) {
  command = cleanCommand(command);
  if (command.size() != 6) return;

  auto s    = parseStyle(command[1]);
  double cx = std::stod(split(command[2], '"')[1]);
  double cy = std::stod(split(command[3], '"')[1]);
  double r  = std::stod(split(command[4], '"')[1]);

  document->shapes_.push_back(std::make_unique<Hexagon>(
      QPointF(cx, cy), r, s.fill, s.stroke, s.stroke_w, s.has_fill));
}

void FileManager::ParseLine(std::vector<std::string> command,
                            std::unique_ptr<Document>& document) {
  command = cleanCommand(command);
  if (command.size() != 6) return;

  auto style_tokens  = split(split(command[1], '"')[1], ';');
  QColor stroke_color= QColor(QString::fromStdString(split(style_tokens[0], ':')[1]));
  float  stroke_w    = std::stof(split(style_tokens[1], ':')[1]);
  double x1 = std::stod(split(command[2], '"')[1]);
  double y1 = std::stod(split(command[3], '"')[1]);
  double x2 = std::stod(split(command[4], '"')[1]);
  double y2 = std::stod(split(command[5], '"')[1]);

  document->shapes_.push_back(std::make_unique<Line>(
      QPointF(x1, y1), QPointF(x2, y2), Qt::black, stroke_color, stroke_w, false));
}

void FileManager::ParseFreehand(std::vector<std::string> command,
                                std::unique_ptr<Document>& document) {
  command = cleanCommand(command);
  if (command.size() < 3) {
    std::cerr << "Parsing for freehand failed" << std::endl;
    return;
  }

  auto style_tokens = split(split(command[1], '"')[1], ';');
  std::string stroke_str = "black";
  std::string stroke_width_val = "2";
  for (const auto& token : style_tokens) {
    if (token.find("stroke-width") != std::string::npos)
      stroke_width_val = split(token, ':')[1];
    else if (token.find("stroke:") != std::string::npos)
      stroke_str = split(token, ':')[1];
  }

  std::string path_data = split(command[2], '"')[1];
  std::vector<QPointF> points;
  std::stringstream ss(path_data);
  char cmd_char;
  double x, y;
  while (ss >> cmd_char) {
    if ((cmd_char == 'M' || cmd_char == 'L') && (ss >> x >> y))
      points.push_back(QPointF(x, y));
  }

  document->shapes_.push_back(std::make_unique<Freehand>(
      points, Qt::black, QColor(QString::fromStdString(stroke_str)),
      std::stof(stroke_width_val), false));
}

void FileManager::ParseText(std::vector<std::string> command,
                            std::unique_ptr<Document>& document) {
  std::vector<std::string> meta_data;
  std::vector<std::string> content;
  bool content_started = false;

  for (auto& str : command) {
    if (str.find("</text>") != std::string::npos) break;
    if (str.empty() && !content_started) continue;
    if (str.find(">") != std::string::npos) { content_started = true; meta_data.push_back(str); }
    else if (!content_started) meta_data.push_back(str);
    else content.push_back(str);
  }

  if (meta_data.size() != 5) {
    std::cerr << "Parsing for text failed" << std::endl;
    return;
  }

  auto style_tokens  = split(split(meta_data[1], '"')[1], ';');
  QColor stroke_color= QColor(QString::fromStdString(split(style_tokens[0], ':')[1]));
  float  stroke_w    = std::stof(split(style_tokens[1], ':')[1]);
  double x           = std::stod(split(meta_data[2], '"')[1]);
  double y           = std::stod(split(meta_data[3], '"')[1]);
  int    font_size   = std::stoi(split(meta_data[4], '"')[1]);

  std::string content_string;
  for (auto& str : content) { content_string += DeEscapedLine(str); content_string += '\n'; }
  if (!content_string.empty() && content_string.back() == '\n')
    content_string.pop_back();

  Text text;
  text.position_     = QPointF(x, y);
  text.stroke_color_ = stroke_color;
  text.stroke_width_ = stroke_w;
  text.font_size_    = font_size;
  text.has_fill_     = false;
  text.content_      = QString::fromStdString(content_string);
  document->shapes_.push_back(std::make_unique<Text>(text));
}
