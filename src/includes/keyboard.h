#include <sis.h>

extern void isr_kbd_int(void);
extern void isr_default_int(int id);
extern void change_kbmap(char* map);
extern void setDisplayFot(char fnt);
extern void setShowRelojPanel();
extern void keysSetting(unsigned char i);
extern void changeColorDisplay(char color);