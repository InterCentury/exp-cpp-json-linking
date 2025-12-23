// dummy_main.cpp (EXPERIMENTAL)

#include <iostream>
#include <sstream>
#include <string>

// Dummy ANSI colors (temporary)
namespace Color {
    const std::string RESET = "\033[0m";
    const std::string CYAN = "\033[36m";
    const std::string YELLOW = "\033[33m";
    const std::string GREEN = "\033[32m";
    const std::string MAGENTA = "\033[35m";
}

// Dummy CompactOS replacement
struct DummyOS {
    std::string getOSName() { return "Windows"; }
    std::string getOSBuild() { return " 10.0.22631"; }
    std::string getArchitecture() { return "x64"; }
    std::string getUptime() { return "2h 13m"; }
};

// Dummy LivePrinter
struct LivePrinter {
    void push(const std::string& s) {
        std::cout << s << std::endl;
    }
};

int main() {

    LivePrinter lp;
    DummyOS c_os;

    // Header
    {
        std::ostringstream ss;
        ss << Color::MAGENTA
            << "~>> BinaryFetch__________________________________________"
            << Color::RESET;
        lp.push(ss.str());
    }

    // Minimal OS (color per section)
    {
        std::ostringstream ss;
        ss << Color::CYAN << "[OS]" << Color::RESET << "  -> "
            << Color::GREEN
            << c_os.getOSName()
            << c_os.getOSBuild()
            << " (" << c_os.getArchitecture() << ")"
            << " (uptime: " << c_os.getUptime() << ")"
            << Color::RESET;

        lp.push(ss.str());
    }

    // Dummy CPU
    {
        std::ostringstream ss;
        ss << Color::YELLOW << "[CPU]" << Color::RESET
            << " -> Ryzen 5 5600G (6C/12T @ 3.90GHz)";
        lp.push(ss.str());
    }

    // Dummy Display
    {
        std::ostringstream ss;
        ss << Color::MAGENTA << "[Display 1]" << Color::RESET
            << " -> LG (1920x1080) @144Hz";
        lp.push(ss.str());
    }

    return 0;
}
