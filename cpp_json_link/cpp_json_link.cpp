#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// pretend JSON lib
#include "third_party/nlohmann/json.hpp"
using json = nlohmann::json;

/* ---------------- Dummy OS class ---------------- */
struct OSInfo {
    std::string getOSName() const { return "Windows"; }
    std::string getOSBuild() const { return " 10 22H2"; }
    std::string getArchitecture() const { return "x64"; }
    std::string getUptime() const { return "3h 21m"; }
};

/* ---------------- Color helper ---------------- */
std::string colorize(const std::string& text, const std::string& color) {
    if (color == "red")     return "\033[31m" + text + "\033[0m";
    if (color == "green")   return "\033[32m" + text + "\033[0m";
    if (color == "yellow")  return "\033[33m" + text + "\033[0m";
    if (color == "blue")    return "\033[34m" + text + "\033[0m";
    if (color == "magenta") return "\033[35m" + text + "\033[0m";
    if (color == "cyan")    return "\033[36m" + text + "\033[0m";
    return text;
}

int main() {
    // Load config
    std::ifstream f("config.json");
    json cfg;
    f >> cfg;

    OSInfo c_os;

    const auto& os = cfg["modules"]["os"];
    if (!os["enabled"]) return 0;

    std::ostringstream ss;

    // [OS] label
    ss << colorize(
        "[" + os["label"]["text"].get<std::string>() + "]",
        os["label"]["color"]
    )
        << " -> ";

    // OS name
    if (os["fields"]["name"]["enabled"]) {
        ss << colorize(
            c_os.getOSName(),
            os["fields"]["name"]["color"]
        );
    }

    // Build
    if (os["fields"]["build"]["enabled"]) {
        ss << colorize(
            c_os.getOSBuild(),
            os["fields"]["build"]["color"]
        );
    }

    // Architecture
    if (os["fields"]["arch"]["enabled"]) {
        ss << " ("
            << colorize(
                c_os.getArchitecture(),
                os["fields"]["arch"]["color"]
            )
            << ")";
    }

    // Uptime
    if (os["fields"]["uptime"]["enabled"]) {
        ss << " (uptime: "
            << colorize(
                c_os.getUptime(),
                os["fields"]["uptime"]["color"]
            )
            << ")";
    }

    // Output
    std::cout << ss.str() << std::endl;
    return 0;
}
