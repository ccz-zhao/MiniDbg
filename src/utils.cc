#include "utils.h"

#include <sys/ptrace.h>
#include <unistd.h>

#include <algorithm>
#include <iostream>

namespace minidbg {

std::vector<std::string> split(const std::string &s, char delimiter) { 
    std::vector<std::string> out;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delimiter)) {
        out.emplace_back(item);
    }
    return std::move(out);
}

bool is_prefix(const std::string& s, const std::string& of) {
    if (s.empty()) return false;
    if (s.size() > of.size()) return false;
    return std::equal(s.begin(), s.end(), of.begin());
}

void execute_debugee (const std::string& prog_name) {
    if (ptrace(PTRACE_TRACEME, 0, 0, 0) < 0) {
        std::cerr << "Error in ptrace\n";
        return;
    }
    execl(prog_name.c_str(), prog_name.c_str(), nullptr);
}

};  // namespace minidbg
