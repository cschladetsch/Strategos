
#include "utils.hpp"
#include "rang.hpp"
#include <sstream>

std::string color(const std::string& text, const std::string& color_name) {
    std::ostringstream oss;
    if (color_name == "red") oss << rang::fg::red << text << rang::style::reset;
    else if (color_name == "blue") oss << rang::fg::blue << text << rang::style::reset;
    else if (color_name == "yellow") oss << rang::fg::yellow << text << rang::style::reset;
    else oss << text;
    return oss.str();
}
