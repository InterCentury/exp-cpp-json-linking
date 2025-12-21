#include <iostream>
#include <unordered_map>
#include <string>

// nlohmann::json single-header library
// This file should be placed inside your project, e.g.
// third_party/nlohmann/json.hpp
#include "third_party/nlohmann/json.hpp"

using json = nlohmann::json;

/* ============================================================
   COLOR & STYLE HANDLING
   ------------------------------------------------------------
   This section maps human-readable color/style names
   (from JSON config) to ANSI escape codes used by terminals.
   ============================================================ */

   /**
    * Converts a color name (string) into an ANSI color escape code.
    * If an unknown color is provided, it safely falls back to "reset".
    *
    * Example:
    *   getColorCode("red") -> "\033[31m"
    */
std::string getColorCode(const std::string& color) {

    // Static map so it is created only once
    static std::unordered_map<std::string, std::string> colors = {

        // Standard colors
        {"black",   "\033[30m"},
        {"red",     "\033[31m"},
        {"green",   "\033[32m"},
        {"yellow",  "\033[33m"},
        {"blue",    "\033[34m"},
        {"magenta", "\033[35m"},
        {"cyan",    "\033[36m"},
        {"white",   "\033[37m"},

        // Bright variants
        {"gray",           "\033[90m"},
        {"grey",           "\033[90m"},
        {"bright_red",     "\033[91m"},
        {"bright_green",   "\033[92m"},
        {"bright_yellow",  "\033[93m"},
        {"bright_blue",    "\033[94m"},
        {"bright_magenta", "\033[95m"},
        {"bright_cyan",    "\033[96m"},
        {"bright_white",   "\033[97m"},

        // Reset code (important to avoid color bleeding)
        {"reset", "\033[0m"}
    };

    // Look up the color name
    std::unordered_map<std::string, std::string>::iterator it = colors.find(color);

    // If found, return the ANSI code
    if (it != colors.end())
        return it->second;

    // Fallback: reset color if input is invalid
    return "\033[0m";
}

/**
 * Converts a text style name into an ANSI escape code.
 *
 * Supported styles:
 *  - bold
 *  - dim
 *  - underline
 *  - blink
 *  - reverse
 *
 * Unknown styles return an empty string (safe no-op).
 */
std::string getStyleCode(const std::string& style) {

    if (style == "bold")       return "\033[1m";
    if (style == "dim")        return "\033[2m";
    if (style == "underline")  return "\033[4m";
    if (style == "blink")      return "\033[5m";
    if (style == "reverse")    return "\033[7m";

    // No style applied
    return "";
}

/* ============================================================
   MAIN ENTRY POINT
   ============================================================ */

int main() {

    // --------------------------------------------------------
    // Configuration object
    // In BinaryFetch, this would usually be loaded from
    // an external config.json file.
    // --------------------------------------------------------
    json config;

    config["print_hello"] = true;          // Toggle output on/off
    config["hello_color"] = "bright_cyan"; // Text color
    config["hello_style"] = "bold";        // Text style

    // --------------------------------------------------------
    // Execute behavior based on configuration
    // --------------------------------------------------------
    if (config["print_hello"].get<bool>()) {

        // Read values safely from JSON
        std::string color = config["hello_color"].get<std::string>();
        std::string style = config["hello_style"].get<std::string>();

        // Apply style + color, print text, then reset formatting
        std::cout
            << getStyleCode(style)
            << getColorCode(color)
            << "Hello World"
            << getColorCode("reset")   // Always reset to avoid affecting next output
            << std::endl;
    }

    return 0;
}
