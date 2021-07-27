#include <io.h>
#include <keyboard.h>
#include <keymap.h>

char* kbdmap = kbdmap_eu;

void isr_kbd_int(void)
{
    
  unsigned char i;
  static int lshift_enable;
  static int rshift_enable;
  static int alt_enable;
  static int ctrl_enable;
  do {
    i = inb(0x64);
  } while ((i & 0x01) == 0);
  

  i = inb(0x60);
  i--;


  if (i < 0x80) {   /* touche enfoncee */
    switch (i) {
    case 0x29:
      lshift_enable = 1;
      break;
    case 0x35:
      rshift_enable = 1;
      break;
    case 0x1C:
      ctrl_enable = 1;
      break;
    case 0x37:
      alt_enable = 1;
      break;
    default:
    
        if(alt_enable==1)
        {
          //keysSetting(i);
          break;
          //putc(kbdmap[i * 4 + 2]);
          //io.putctty(kbdmap[i * 4 + 2]);
          /*if (&io != io.current_io)
          io.current_io->putctty(kbdmap[i * 4 + 2]);*/
     
        }
        else if(lshift_enable == 1 || rshift_enable == 1)
        {
     
           //putc(kbdmap[i * 4 + 1]);
          //keysSetting(i);
          break;
           /*if (&io != io.current_io)
            io.current_io->putctty(kbdmap[i * 4 + 1]);*/
     
        }
        else
        { 
           if(ctrl_enable == 1)
           {
              //putc(kbdmap[i * 4]);
              keysSetting(i);

           }
            else
              //putc(kbdmap[i * 4]);
              //keysSetting(i);
              break;
           /*if (&io != io.current_io)
           io.current_io->putctty(kbdmap[i * 4]);*/
            //print("%d",i);
     
        }
               break;

      //io.print("sancode: %x \n",i * 4 + (lshift_enable || rshift_enable));
      /*io.putctty(kbdmap[i * 4 + (lshift_enable || rshift_enable)]); //replacé depuis la 10.4.6
      if (&io != io.current_io)
        io.current_io->putctty(kbdmap[i * 4 + (lshift_enable || rshift_enable)]);*/
      break;
    }
  } else {    /* touche relachee */
    i -= 0x80;
    switch (i) {
    case 0x29:
      lshift_enable = 0;
      break;
    case 0x35:
      rshift_enable = 0;
      break;
    case 0x1C:
      ctrl_enable = 0;
      break;
    case 0x37:
      alt_enable = 0;
      break;
    }
  }

    outb(0x20,0x20);
    outb(0xA0,0x20); 
}

void isr_default_int(int id)
{
  //static int tic = 0;
  //static int sec = 0;

  switch (id){
    case 1:
        isr_kbd_int();
      break; 
      
    default:
      return;
    
  }
  
  outb(0x20,0x20);
  outb(0xA0,0x20);
}

void change_kbmap(char* map)
{
   kbdmap = map;  
}

void keysSetting(unsigned char i)
{ 
  if(kbdmap[i * 4] == 'n')
    setDisplayFot(0);
  if(kbdmap[i * 4] == 'a')
    setDisplayFot(1);
  if(kbdmap[i * 4] == 'd')
    setDisplayFot(2);
  if(kbdmap[i * 4] == 'r')
    setShowRelojPanel();
  if(kbdmap[i * 4] == 'q')
    reboot();

  if(kbdmap[i * 4] == '1')
    changeColorDisplay(1);
  if(kbdmap[i * 4] == '2')
    changeColorDisplay(2);
  if(kbdmap[i * 4] == '3')
    changeColorDisplay(3);
  if(kbdmap[i * 4] == '4')
    changeColorDisplay(4);
  if(kbdmap[i * 4] == '5')
    changeColorDisplay(5);
  if(kbdmap[i * 4] == '6')
    changeColorDisplay(6);
  if(kbdmap[i * 4] == '7')
    changeColorDisplay(7);

}