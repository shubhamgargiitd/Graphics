#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <QPointF>

// Trims leading and trailing spaces from a string
std::string trim(std::string s);

// Splits a string by a delimiter
std::vector<std::string> split(std::string str, char delimiter);

// Calculate distance from a point to a line segment
double distance_from_line(QPointF point, QPointF line_start, QPointF line_end);

std::string DeEscapedLine(std::string line);

std::string EscapedCharacter(char c);