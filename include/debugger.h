#ifndef MINIDBG_DEBUGGER_H
#define MINIDBG_DEBUGGER_H

#include "breakpoint.h"

#include <utility>
#include <string>
#include <unordered_map>
#include <linux/types.h>

namespace minidbg {
    class debugger {
    public:
        debugger (std::string prog_name, pid_t pid)
            : m_pid{pid}, m_prog_name{std::move(prog_name)} {}

        void run();
        void set_breakpoint_at_address(std::intptr_t addr);

    private:
        pid_t m_pid;
        std::string m_prog_name;
        std::unordered_map<std::intptr_t, breakpoint::ptr> m_breakpoints;
        
        void handle_command(const std::string& line);
        void continue_execution();        
    };
}

#endif