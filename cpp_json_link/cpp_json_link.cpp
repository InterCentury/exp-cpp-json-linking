#include <iostream>
#include <unordered_map>
#include <string>

// nlohmann json (single-header)
#include "third_party/nlohmann/json.hpp"

using json = nlohmann::json;

/* ================= COLOR SYSTEM (C++14 SAFE) ================= */

std::string getColorCode(const std::string& color) {
    static std::unordered_map<std::string, std::string> colors = {
        {"black",   "\033[30m"},
        {"red",     "\033[31m"},
        {"green",   "\033[32m"},
        {"yellow",  "\033[33m"},
        {"blue",    "\033[34m"},
        {"magenta", "\033[35m"},
        {"cyan",    "\033[36m"},
        {"white",   "\033[37m"},

        {"gray",           "\033[90m"},
        {"grey",           "\033[90m"},
        {"bright_red",     "\033[91m"},
        {"bright_green",   "\033[92m"},
        {"bright_yellow",  "\033[93m"},
        {"bright_blue",    "\033[94m"},
        {"bright_magenta", "\033[95m"},
        {"bright_cyan",    "\033[96m"},
        {"bright_white",   "\033[97m"},

        {"reset", "\033[0m"}
    };

    std::unordered_map<std::string, std::string>::iterator it = colors.find(color);
    if (it != colors.end())
        return it->second;

    return "\033[0m"; // reset fallback
}

std::string getStyleCode(const std::string& style) {
    if (style == "bold")       return "\033[1m";
    if (style == "dim")        return "\033[2m";
    if (style == "underline")  return "\033[4m";
    if (style == "blink")      return "\033[5m";
    if (style == "reverse")    return "\033[7m";
    return "";
}

/* ================= MAIN ================= */

int main() {

    // ---- JSON CONFIG (inline for now) ----
    json config;
    config["print_hello"] = true;
    config["hello_color"] = "bright_cyan";
    config["hello_style"] = "bold";

    // ---- LOGIC ----
    if (config["print_hello"].get<bool>()) {

        std::string color = config["hello_color"].get<std::string>();
        std::string style = config["hello_style"].get<std::string>();

        std::cout
            << getStyleCode(style)
            << getColorCode(color)
            << "Hello World"
            << getColorCode("reset")
            << std::endl;
    }

    return 0;
}
