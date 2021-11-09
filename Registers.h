#include <stdint.h>
#include <stddef.h>
#include "libc/string.h"
#ifndef REGISTERS_H
#define REGISTERS_H

#define PACKED __attribute__((packed))

struct Registers
{
	uint64_t r15;
	uint64_t r14;
	uint64_t r13;
	uint64_t r12;
	uint64_t r11;
	uint64_t r10;
	uint64_t r9;
	uint64_t r8;
	uint64_t rbp;
	uint64_t rdi;
	uint64_t rsi;
	uint64_t rdx;
	uint64_t rcx;
	uint64_t rbx;
	uint64_t rax;

	uint64_t exception_num;

	uint64_t error;
	uint64_t rip;
	uint64_t cs;
	uint64_t flags;
	uint64_t rsp;
	uint64_t ss;
} PACKED;

struct Registers GetRegisters();
#endif