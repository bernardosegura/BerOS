#include <mem.h>
#include <idt.h>

void init_idt_desc(unsigned short select, unsigned int offset, unsigned short type, struct idtdesc *desc)
{
  desc->offset0_15 = (offset & 0xffff);
  desc->select = select;
  desc->type = type;
  desc->offset16_31 = (offset & 0xffff0000) >> 16;
  return;
}


/*
 * Init IDT after kernel is loaded
 */
void init_idt(void)
{
  /* Init irq */
  int i;
  for (i = 0; i < IDTSIZE; i++) 
      init_idt_desc(0x08, (unsigned int)_asm_schedule, INTGATE, &kidt[i]); // */
  
    init_idt_desc(0x08, (unsigned int) _asm_int_1, INTGATE, &kidt[33]); // aqui se ejecuta isr_default_int
   
  kidtr.limite = IDTSIZE * 8;
  kidtr.base = IDTBASE;
    
  /* Copy the IDT to the memory */
  memcpy((char *) kidtr.base, (char *) kidt, kidtr.limite);

  /* Load the IDTR registry */
  asm("lidtl (kidtr)");
}
