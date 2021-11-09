#pragma once

#include <stdint.h>
#include <stddef.h>
#include "libc/stdio.h"
#include "Registers.h"

#define ATTR_RING0   (0x00)
#define ATTR_RING3   ( (1 << 5) | (1 << 6) )
#define ATTR_TASK    (1 | (1 << 2))
#define ATTR_INTR    ( (1 << 1) | (1 << 2) | (1 << 3) )
#define ATTR_TRAP    ( (1) | (1 << 1) | (1 << 2) | (1 << 3) )
#define ATTR_PRESENT (1 << 7)

typedef struct IDTDescr{
	uint16_t    isr_low;  
	uint16_t    kernel_cs;    
	uint8_t	    ist;          
	uint8_t     attributes;  
	uint16_t    isr_mid;      
	uint32_t    isr_high;    
	uint32_t    reserved;     
} __attribute__((packed));

struct IDTPointer
{
    uint16_t base;
    uint64_t limit;
} __attribute__((packed));

static struct IDTDescr entries[256] = {0};
static struct IDTPointer idtptr = {0};

extern void* isr_stub_table[];
 
void idt_init() {
    idtptr.base = (uint16_t)sizeof(struct IDTDescr) * 256 - 1;
    idtptr.limit = (uintptr_t)&entries[0];
 
    for (uint8_t vector = 0; vector < 32; vector++) {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
    }
 
    asm volatile ("lidt %0" :: "m"(idtptr)); // load the new IDT
    asm volatile ("sti"); // set the interrupt flag
}

/*void ExceptionHandler(struct Registers registers)
{
    printf("Exception caught: Error: %d Exception Number: %d; Registers: r15: %d r14: %d r13: %d r12: %d r11: %d r10: %d r9: %d r8: %d\n rbp: %d rdi: %d rsi: %d rdx: %d rcx: %d rbx: %d rax: %d rip: %d cs: %d flags: %d rsp: %d ss: %d", 
    registers.error, 
    registers.exception_num,
    registers.r15,
    registers.r14,
    registers.r13,
    registers.r12,
    registers.r11,
    registers.r10,
    registers.r9,
    registers.r8,
    registers.rbp,
    registers.rdi,
    registers.rsi, registers.rdx, registers.rdx, registers.rcx, registers.rbx, registers.rax, registers.rip, registers.cs, registers.flags, registers.rsp, registers.ss);
    asm volatile("hlt");
}*/

//__attribute__((noreturn))
void exception_handler(void);
const char *exception_str[] = {
"Divide By Zero",
"Debug",
"Non-maskable Interrupt",
"Breakpoint",
"Overflow",
"Bound Range Exceeded",
"Invalid Opcode",
"Device Not Available",
"Double Fault",
"Coprocessor Segment Overrun",
"Invalid TSS",
"Segment Not Present",
"Stack-Segment Fault",
"General Protection Fault",
"Page Fault",
"RESERVED",
"x87 Floating-Point",
"Alignment Check",
"Machine Check",
"SIMD Floating-Point",
"Virtualization",
"Security Exception"
};
void exception_handler() {
    printf("Exception caught!");
    asm volatile ("cli; hlt");
}

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
    struct IDTDescr* descriptor = &entries[vector];
 
    descriptor->isr_low        = (uint64_t)isr & 0xFFFF;
    descriptor->kernel_cs      = 0x28;
    descriptor->ist            = 0;
    descriptor->attributes     = flags;
    descriptor->isr_mid        = ((uint64_t)isr >> 16) & 0xFFFF;
    descriptor->isr_high       = ((uint64_t)isr >> 32) & 0xFFFFFFFF;
    descriptor->reserved       = 0;
}

void idt_set_handler(uint8_t index, void(*handler)())
{
    idt_set_descriptor(index, handler, ATTR_INTR | ATTR_RING0 | ATTR_PRESENT);
}

void IDTCommonHandler0();
void IDTCommonHandler1();
void IDTCommonHandler2();
void IDTCommonHandler3();
void IDTCommonHandler4();
void IDTCommonHandler5();
void IDTCommonHandler6();
void IDTCommonHandler7();
void IDTCommonHandler8();
void IDTCommonHandler9();
void IDTCommonHandler10();
void IDTCommonHandler11();
void IDTCommonHandler12();
void IDTCommonHandler13();
void IDTCommonHandler14();
void IDTCommonHandler15();
void IDTCommonHandler16();
void IDTCommonHandler17();
void IDTCommonHandler18();
void IDTCommonHandler19();
void IDTCommonHandler20();
void IDTCommonHandler21();
void IDTCommonHandler22();
void IDTCommonHandler23();
void IDTCommonHandler24();
void IDTCommonHandler25();
void IDTCommonHandler26();
void IDTCommonHandler27();
void IDTCommonHandler28();
void IDTCommonHandler29();
void IDTCommonHandler30();
void IDTCommonHandler31();
void IDTCommonHandler32();
void IDTCommonHandler33();
void IDTCommonHandler34();
void IDTCommonHandler35();
void IDTCommonHandler36();
void IDTCommonHandler37();
void IDTCommonHandler38();
void IDTCommonHandler39();
void IDTCommonHandler40();
void IDTCommonHandler41();
void IDTCommonHandler42();
void IDTCommonHandler43();
void IDTCommonHandler44();
void IDTCommonHandler45();
void IDTCommonHandler46();
void IDTCommonHandler47();
void IDTCommonHandler48();
void IDTCommonHandler49();
void IDTCommonHandler50();
void IDTCommonHandler51();
void IDTCommonHandler52();
void IDTCommonHandler53();
void IDTCommonHandler54();
void IDTCommonHandler55();
void IDTCommonHandler56();
void IDTCommonHandler57();
void IDTCommonHandler58();
void IDTCommonHandler59();
void IDTCommonHandler60();
void IDTCommonHandler61();
void IDTCommonHandler62();
void IDTCommonHandler63();
void IDTCommonHandler64();
void IDTCommonHandler65();
void IDTCommonHandler66();
void IDTCommonHandler67();
void IDTCommonHandler68();
void IDTCommonHandler69();
void IDTCommonHandler70();
void IDTCommonHandler71();
void IDTCommonHandler72();
void IDTCommonHandler73();
void IDTCommonHandler74();
void IDTCommonHandler75();
void IDTCommonHandler76();
void IDTCommonHandler77();
void IDTCommonHandler78();
void IDTCommonHandler79();
void IDTCommonHandler80();
void IDTCommonHandler81();
void IDTCommonHandler82();
void IDTCommonHandler83();
void IDTCommonHandler84();
void IDTCommonHandler85();
void IDTCommonHandler86();
void IDTCommonHandler87();
void IDTCommonHandler88();
void IDTCommonHandler89();
void IDTCommonHandler90();
void IDTCommonHandler91();
void IDTCommonHandler92();
void IDTCommonHandler93();
void IDTCommonHandler94();
void IDTCommonHandler95();
void IDTCommonHandler96();
void IDTCommonHandler97();
void IDTCommonHandler98();
void IDTCommonHandler99();
void IDTCommonHandler100();
void IDTCommonHandler101();
void IDTCommonHandler102();
void IDTCommonHandler103();
void IDTCommonHandler104();
void IDTCommonHandler105();
void IDTCommonHandler106();
void IDTCommonHandler107();
void IDTCommonHandler108();
void IDTCommonHandler109();
void IDTCommonHandler110();
void IDTCommonHandler111();
void IDTCommonHandler112();
void IDTCommonHandler113();
void IDTCommonHandler114();
void IDTCommonHandler115();
void IDTCommonHandler116();
void IDTCommonHandler117();
void IDTCommonHandler118();
void IDTCommonHandler119();
void IDTCommonHandler120();
void IDTCommonHandler121();
void IDTCommonHandler122();
void IDTCommonHandler123();
void IDTCommonHandler124();
void IDTCommonHandler125();
void IDTCommonHandler126();
void IDTCommonHandler127();
void IDTCommonHandler128();
void IDTCommonHandler129();
void IDTCommonHandler130();
void IDTCommonHandler131();
void IDTCommonHandler132();
void IDTCommonHandler133();
void IDTCommonHandler134();
void IDTCommonHandler135();
void IDTCommonHandler136();
void IDTCommonHandler137();
void IDTCommonHandler138();
void IDTCommonHandler139();
void IDTCommonHandler140();
void IDTCommonHandler141();
void IDTCommonHandler142();
void IDTCommonHandler143();
void IDTCommonHandler144();
void IDTCommonHandler145();
void IDTCommonHandler146();
void IDTCommonHandler147();
void IDTCommonHandler148();
void IDTCommonHandler149();
void IDTCommonHandler150();
void IDTCommonHandler151();
void IDTCommonHandler152();
void IDTCommonHandler153();
void IDTCommonHandler154();
void IDTCommonHandler155();
void IDTCommonHandler156();
void IDTCommonHandler157();
void IDTCommonHandler158();
void IDTCommonHandler159();
void IDTCommonHandler160();
void IDTCommonHandler161();
void IDTCommonHandler162();
void IDTCommonHandler163();
void IDTCommonHandler164();
void IDTCommonHandler165();
void IDTCommonHandler166();
void IDTCommonHandler167();
void IDTCommonHandler168();
void IDTCommonHandler169();
void IDTCommonHandler170();
void IDTCommonHandler171();
void IDTCommonHandler172();
void IDTCommonHandler173();
void IDTCommonHandler174();
void IDTCommonHandler175();
void IDTCommonHandler176();
void IDTCommonHandler177();
void IDTCommonHandler178();
void IDTCommonHandler179();
void IDTCommonHandler180();
void IDTCommonHandler181();
void IDTCommonHandler182();
void IDTCommonHandler183();
void IDTCommonHandler184();
void IDTCommonHandler185();
void IDTCommonHandler186();
void IDTCommonHandler187();
void IDTCommonHandler188();
void IDTCommonHandler189();
void IDTCommonHandler190();
void IDTCommonHandler191();
void IDTCommonHandler192();
void IDTCommonHandler193();
void IDTCommonHandler194();
void IDTCommonHandler195();
void IDTCommonHandler196();
void IDTCommonHandler197();
void IDTCommonHandler198();
void IDTCommonHandler199();
void IDTCommonHandler200();
void IDTCommonHandler201();
void IDTCommonHandler202();
void IDTCommonHandler203();
void IDTCommonHandler204();
void IDTCommonHandler205();
void IDTCommonHandler206();
void IDTCommonHandler207();
void IDTCommonHandler208();
void IDTCommonHandler209();
void IDTCommonHandler210();
void IDTCommonHandler211();
void IDTCommonHandler212();
void IDTCommonHandler213();
void IDTCommonHandler214();
void IDTCommonHandler215();
void IDTCommonHandler216();
void IDTCommonHandler217();
void IDTCommonHandler218();
void IDTCommonHandler219();
void IDTCommonHandler220();
void IDTCommonHandler221();
void IDTCommonHandler222();
void IDTCommonHandler223();
void IDTCommonHandler224();
void IDTCommonHandler225();
void IDTCommonHandler226();
void IDTCommonHandler227();
void IDTCommonHandler228();
void IDTCommonHandler229();
void IDTCommonHandler230();
void IDTCommonHandler231();
void IDTCommonHandler232();
void IDTCommonHandler233();
void IDTCommonHandler234();
void IDTCommonHandler235();
void IDTCommonHandler236();
void IDTCommonHandler237();
void IDTCommonHandler238();
void IDTCommonHandler239();
void IDTCommonHandler240();
void IDTCommonHandler241();
void IDTCommonHandler242();
void IDTCommonHandler243();
void IDTCommonHandler244();
void IDTCommonHandler245();
void IDTCommonHandler246();
void IDTCommonHandler247();
void IDTCommonHandler248();
void IDTCommonHandler249();
void IDTCommonHandler250();
void IDTCommonHandler251();
void IDTCommonHandler252();
void IDTCommonHandler253();
void IDTCommonHandler254();
void IDTCommonHandler255();
