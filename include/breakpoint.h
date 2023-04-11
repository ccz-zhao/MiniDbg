#ifndef MINIDBG_BREAKPOINT_H
#define MINIDBG_BREAKPOINT_H

#include <cstdint>
#include <sys/ptrace.h>
#include <unistd.h>
#include <memory>

namespace minidbg {
    class breakpoint {
    public:
        using ptr = std::shared_ptr<breakpoint>;
        breakpoint() = default;
        breakpoint(pid_t pid, std::intptr_t addr) : m_pid{pid}, m_addr{addr}, m_enabled{false}, m_saved_data{} {}

        void enable();

        void disable();

        bool is_enabled() const { return m_enabled; }

        auto get_address() const -> std::intptr_t { return m_addr; }
    private:
        pid_t m_pid;
        std::intptr_t m_addr;
        bool m_enabled;
        uint8_t m_saved_data; //data which used to be at the breakpoint address
    };
}

#endif
