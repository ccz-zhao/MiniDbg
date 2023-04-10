#ifndef MINIDBG_UTILS_H
#define MINIDBG_UTILS_H

#include <string>
#include <sstream>
#include <vector>

namespace minidbg {

std::vector<std::string> split(const std::string &s, char delimiter); 

bool is_prefix(const std::string& s, const std::string& of);

void execute_debugee (const std::string& prog_name);

};  // namespace minidbg

#endif