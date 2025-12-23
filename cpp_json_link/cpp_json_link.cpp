#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

// pretend JSON lib
#include "third_party/nlohmann/json.hpp"
using json = nlohmann::json;
using namespace std;

// ---------------- Dummy OS class ----------------
class CompactOS {
public:
    string getOSName() { return "Windows"; }
    string getOSBuild() { return " 10.0.22631"; }
    string getArchitecture() { return "x64"; }
    string getUptime() { return "2h 31m"; }
};

// ---------------- Color helper ----------------
string colorize(const string& text, const string& color) {
    if (color == "red")    return "\033[31m" + text + "\033[0m";
    if (color == "green")  return "\033[32m" + text + "\033[0m";
    if (color == "cyan")   return "\033[36m" + text + "\033[0m";
    if (color == "yellow") return "\033[33m" + text + "\033[0m";
    return text; // default (no color)
}

int main() {
    // -------- Load config.json --------
    json cfg;
    ifstream f("config.json");
    cfg = json::parse(f);

    CompactOS c_os;

    // -------- Minimal OS section --------
    if (cfg["modules"]["os"]["enabled"]) {

        ostringstream ss;
        ss << "[OS]  -> " << c_os.getOSName()
            << c_os.getOSBuild()
            << " (" << c_os.getArchitecture() << ")"
            << " (uptime: " << c_os.getUptime() << ")";

        string color = cfg["modules"]["os"]["color"];
        cout << colorize(ss.str(), color) << endl;
    }

    return 0;
}
