#include <io.h>
#include <sis.h>

////////////////////////////////////////////////Init Pic///////////////////////////////////////////////////////////////
void init_pic(void)
{
  /* Initialization of ICW1 */
  outb(0x20, 0x11);
  outb(0xA0, 0x11);

  /* Initialization of ICW2 */
  outb(0x21, 0x20); /* start vector = 32 */
  outb(0xA1, 0x70); /* start vector = 96 */

  /* Initialization of ICW3 */
  outb(0x21, 0x04);
  outb(0xA1, 0x02);

  /* Initialization of ICW4 */
  outb(0x21, 0x01);
  outb(0xA1, 0x01);

  /* mask interrupts */
  outb(0x21, 0x0);
  outb(0xA1, 0x0);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Enable the interruption */
void enable_interrupt(){
  asm ("sti");
}

/* Enable the interruption */
void disable_interrupt()
{
	asm("cli");
}
/* Shutdown the computer */
void shutdown(){
  // todo meter
}

/* Reboot the computer */
void reboot(){
    unsigned char good = 0x02;
    while ((good & 0x02) != 0)
        good = inb(0x64);
    outb(0x64, 0xFE);
}
