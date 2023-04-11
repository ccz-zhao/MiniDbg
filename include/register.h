#ifndef MINIDBG_REGISTERS_H
#define MINIDBG_REGISTERS_H

#include <sys/user.h>
#include <sys/ptrace.h>
#include <array>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace minidbg {
enum class reg {
    r15=0, r14, r13, r12,
    rbp, rbx, r11, r10,
    r9, r8, rax, rcx,
    rdx, rsi, rdi, orig_rax,
    rip, cs, eflags, rsp,
    ss, fs_base, gs_base,
    ds, es, fs, gs, REG_NUMS
};

static const std::size_t n_registers = static_cast<int>(reg::REG_NUMS);

struct reg_descriptor {
    reg r;
    int dwarf_r;
    std::string name;
};

//have a look in /usr/include/sys/user.h for how to lay this out
static const std::array<reg_descriptor, n_registers> g_register_descriptors {{
        { reg::r15, 15, "r15" },
        { reg::r14, 14, "r14" },
        { reg::r13, 13, "r13" },
        { reg::r12, 12, "r12" },
        { reg::rbp, 6, "rbp" },
        { reg::rbx, 3, "rbx" },
        { reg::r11, 11, "r11" },
        { reg::r10, 10, "r10" },
        { reg::r9, 9, "r9" },
        { reg::r8, 8, "r8" },
        { reg::rax, 0, "rax" },
        { reg::rcx, 2, "rcx" },
        { reg::rdx, 1, "rdx" },
        { reg::rsi, 4, "rsi" },
        { reg::rdi, 5, "rdi" },
        { reg::orig_rax, -1, "orig_rax" },
        { reg::rip, -1, "rip" },
        { reg::cs, 51, "cs" },
        { reg::eflags, 49, "eflags" },
        { reg::rsp, 7, "rsp" },
        { reg::ss, 52, "ss" },
        { reg::fs_base, 58, "fs_base" },
        { reg::gs_base, 59, "gs_base" },
        { reg::ds, 53, "ds" },
        { reg::es, 50, "es" },
        { reg::fs, 54, "fs" },
        { reg::gs, 55, "gs" },
}};

uint64_t get_register_value(pid_t pid, reg r) {
    user_regs_struct regs;
    ptrace(PTRACE_GETREGS, pid, nullptr, &regs);
    return *(reinterpret_cast<uint64_t*>(&regs) + (static_cast<int>(r)));
}

void set_register_value(pid_t pid, reg r, uint64_t value) {
    user_regs_struct regs;
    ptrace(PTRACE_GETREGS, pid, nullptr, &regs);
    *(reinterpret_cast<uint64_t*>(&regs) + (static_cast<int>(r))) = value;
    ptrace(PTRACE_SETREGS, pid, nullptr, &regs);
}

uint64_t get_register_value_from_dwarf_register (pid_t pid, unsigned regnum) {
    auto it = std::find_if(begin(g_register_descriptors), end(g_register_descriptors),
                            [regnum](auto&& rd) { return rd.dwarf_r == regnum; });
    if (it == end(g_register_descriptors)) {
        throw std::out_of_range{"Unknown dwarf register"};
    }
    return get_register_value(pid, it->r);
}

std::string get_register_name(reg r) {
    int reg_i = static_cast<int>(r);
    return g_register_descriptors[reg_i].name;
}

reg get_register_from_name(const std::string& name) {
    auto it = std::find_if(begin(g_register_descriptors), end(g_register_descriptors),
                            [name](auto&& rd) { return rd.name == name; });
    if (it == end(g_register_descriptors)) {
        throw std::out_of_range{"Unknown register name"};
    }
    return it->r;
}

};  // namespace minidbg

#endif