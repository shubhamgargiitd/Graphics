#include "utils/utils.h"

#include <cmath>
#include <sstream>

std::string trim(std::string s) {
  if (s.empty()) return s;
  int i = 0;
  while (i < (int)s.size() && s[i] == ' ') i++;
  if (i == (int)s.size()) return "";
  int j = (int)s.size() - 1;
  while (j > i && s[j] == ' ') j--;
  return s.substr(i, j - i + 1);
}

std::vector<std::string> split(std::string str, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::stringstream ss(str);
  while (std::getline(ss, token, delimiter))
    tokens.push_back(token);
  return tokens;
}

double distance_from_line(QPointF point, QPointF line_start, QPointF line_end) {
  double len = std::sqrt(std::pow(line_start.x() - line_end.x(), 2) +
                         std::pow(line_start.y() - line_end.y(), 2));
  double d_start = std::sqrt(std::pow(point.x() - line_start.x(), 2) +
                              std::pow(point.y() - line_start.y(), 2));
  double d_end   = std::sqrt(std::pow(point.x() - line_end.x(), 2) +
                              std::pow(point.y() - line_end.y(), 2));
  if (len == 0) return d_start;

  double costheta = (d_start * d_start + len * len - d_end * d_end) / (2 * d_start * len);
  double sin2     = 1 - costheta * costheta;
  double extra    = costheta < 0 ? d_start * costheta
                                 : std::max(0.0, d_start * costheta - len);
  return std::sqrt(d_start * d_start * sin2 + extra * extra);
}

std::string EscapedCharacter(char c) {
  switch (c) {
    case '&':  return "&amp;";
    case '<':  return "&lt;";
    case '>':  return "&gt;";
    case '"':  return "&quot;";
    case '\'': return "&apos;";
    default:   return std::string(1, c);
  }
}

std::string DeEscapedLine(std::string line) {
  std::string result;
  int i = 0;
  while (i < (int)line.size()) {
    if (line[i] != '&') { result += line[i++]; continue; }
    if      (line.substr(i, 5) == "&amp;")  { result += '&';  i += 5; }
    else if (line.substr(i, 4) == "&lt;")   { result += '<';  i += 4; }
    else if (line.substr(i, 4) == "&gt;")   { result += '>';  i += 4; }
    else if (line.substr(i, 6) == "&quot;") { result += '"';  i += 6; }
    else if (line.substr(i, 6) == "&apos;") { result += '\''; i += 6; }
    else { result += line[i++]; }
  }
  return result;
}
