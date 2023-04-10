#include "debugger.h"
#include "utils.h"
#include "linenoise.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <iostream>

namespace minidbg {

void debugger::handle_command(const std::string& line) {
    auto args = split(line, ' ');
    auto command = args[0];
    if (is_prefix(command, "continue")) {
        continue_execution();
    } else {
        std::cerr << "unknow command\n";
    }
}

void debugger::run() {
    int wait_status;
    auto options = 0;
    waitpid(m_pid, &wait_status, options);

    char* line = nullptr;
    while((line = linenoise("minidbg> ")) != nullptr) {
        if (line[0] == '\0') continue;
        handle_command(line);
        linenoiseHistoryAdd(line);
        linenoiseFree(line);
    }
}

void debugger::continue_execution() {
    ptrace(PTRACE_CONT, m_pid, nullptr, nullptr);
    int wait_status;
    auto options = 0;
    waitpid(m_pid, &wait_status, options);
}

};  // namespace minidbg