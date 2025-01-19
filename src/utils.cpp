#include "utils.hpp"
#include "rang.hpp"

std::string color(const std::string& text, const std::string& color_name) {
    if (color_name == "red") {
        return rang::fg::red + text + rang::style::reset;
    } else if (color_name == "blue") {
        return rang::fg::blue + text + rang::style::reset;
    } else if (color_name == "yellow") {
        return rang::fg::yellow + text + rang::style::reset;
    } else if (color_name == "green") {
        return rang::fg::green + text + rang::style::reset;
    } else if (color_name == "cyan") {
        return rang::fg::cyan + text + rang::style::reset;
    }
    return text;
}

