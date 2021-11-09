#include "PIC.h"
#include "IDT.h"


void PIC_sendEOI(unsigned char irq)
{
	if(irq >= 8)
		outb(PIC2_COMMAND,PIC_EOI);
 
	outb(PIC1_COMMAND,PIC_EOI);
}

void PIC_remap(uint32_t offset1, uint32_t offset2)
{
	uint8_t a1, a2 = 0;
 
	a1 = inb(PIC1_DATA);                        // save masks
	a2 = inb(PIC2_DATA);
 
	outb(PIC1_COMMAND, 0x11);  // starts the initialization sequence (in cascade mode)

	outb(PIC2_COMMAND, 0x11);

	outb(PIC1_DATA, offset1);                 // ICW2: Master PIC vector offset

	outb(PIC2_DATA, offset2);                 // ICW2: Slave PIC vector offset

	outb(PIC1_DATA, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)

	outb(PIC2_DATA, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)

 
	outb(PIC1_DATA, ICW4_8086);

	outb(PIC2_DATA, ICW4_8086);
 
	outb(PIC1_DATA, a1);   // restore saved masks.
	outb(PIC2_DATA, a2);
}
/*void PIC_disable()
{
    asm volatile("mov al, 0xff");
    asm volatile("out 0xa1, al");
    asm volatile("out 0x21, al");
}*/

void PIC_SetHandlers()
{
    idt_set_handler(0x20, IRQ_HandleTimer);
}

void IRQ_maskall() {
  for (int i = 0; i < 16; i++) IRQ_clear_mask(i);
}

void IRQ_enable_masks()
{
    IRQ_maskall();
    IRQ_clear_mask(0);
    IRQ_clear_mask(2);
}
void PICInit()
{
    PIC_SetHandlers();
    PIC_remap(0x20,0x28);
    IRQ_enable_masks();
}
void IRQ_set_mask(uint8_t IRQline) {
    uint16_t port;
    uint8_t value;
 
    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = inb(port) | (1 << IRQline);
    outb(port, value);        
}
 
void IRQ_clear_mask(uint8_t IRQline) {
    uint16_t port;
    uint8_t value;
 
    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = inb(port) & ~(1 << IRQline);
    outb(port, value);        
}

static uint16_t __pic_get_irq_reg(int ocw3)
{
    /* OCW3 to PIC CMD to get the register values.  PIC2 is chained, and
     * represents IRQs 8-15.  PIC1 is IRQs 0-7, with 2 being the chain */
    outb(PIC1_CMD, ocw3);
    outb(PIC2_CMD, ocw3);
    return (inb(PIC2_CMD) << 8) | inb(PIC1_CMD);
}
 
/* Returns the combined value of the cascaded PICs irq request register */
uint16_t pic_get_irr(void)
{
    return __pic_get_irq_reg(PIC_READ_IRR);
}
 
/* Returns the combined value of the cascaded PICs in-service register */
uint16_t pic_get_isr(void)
{
    return __pic_get_irq_reg(PIC_READ_ISR);
}

