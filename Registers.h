#include <stdint.h>
#include <stddef.h>
#include "libc/string.h"
#ifndef REGISTERS_H
#define REGISTERS_H

#define PACKED __attribute__((packed))
typedef struct
{
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
    uint64_t rbp, rdi, rsi, rdx, rcx, rbx, rax;
    uint64_t int_no, error_code, rip, cs, rflags, rsp, ss;
} interrupt_registers __attribute__((packed));

interrupt_registers GetRegs();
#endif