#include <io.h>

    /** x86 private attributes **/
char* real_screen =  (char*)RAMSCREEN;
char  screen[SIZESCREEN];
char*  vidmem=(char*)RAMSCREEN; /* screen video memory */

char  fcolor=LightGrey;     /* console foreground color */
char  bcolor=Black;     /* console background color */    
char  x;        /* console x position */
char  y;        /* console y position */
char kattr;       /* console attribut */

char screenW = 80;
char screenH = 25;
char initX = 0;

unsigned int strlen( const char* s ) {
 unsigned int r = 0;

    for( ; *s++ != 0; r++ ) { }

    return r;
}

void itoa(char *buf, unsigned long int n, int base)
  {
    unsigned long int tmp;
    int i, j;

    tmp = n;
    i = 0;

    do {
      tmp = n % base;
      buf[i++] = (tmp < 10) ? (tmp + '0') : (tmp + 'a' - 10);
    } while (n /= base);
    buf[i--] = 0;

    for (j = 0; j < i; j++, i--) {
      tmp = buf[j];
      buf[j] = buf[i];
      buf[i] = tmp;
    }
  }
//////////////////////////////////////////////////////////////////////////////////    

void scrollup(unsigned int n)
{
    unsigned char *video, *tmp;
    unsigned char bfc = bcolor;
    bfc <<= 4;
    bfc |= fcolor;
    kattr = bfc;

    for (video = (unsigned char *) real_screen;
         video < (unsigned char *) SCREENLIM; video += 2) {
      tmp = (unsigned char *) (video + n * 160);

      if (tmp < (unsigned char *) SCREENLIM) {
        *video = *tmp;
        *(video + 1) = *(tmp + 1);
      } else {
        *video = 0;
        *(video + 1) = kattr;
      }
    }

    y -= n;
    if (y < 0)
      y = 0;
}

/* output byte */
void outb(unsigned int ad,unsigned char v){
  asm("outb %%al, %%dx" :: "d" (ad), "a" (v));
}

/* input byte */
unsigned char inb(unsigned int ad){
  unsigned char _v;
  asm("inb %%dx, %%al" : "=a" (_v) : "d" (ad));
  return _v;
}

void setPosCursor(char xx, char yy)
{
   unsigned short pos = yy * 80 + xx ;
 
  outb(0x3D4, 0x0F);
  outb(0x3D5, (unsigned char) (pos & 0xFF));
  outb(0x3D4, 0x0E);
  outb(0x3D5, (unsigned char) ((pos >> 8) & 0xFF));
}

/* put a byte on screen */
void putc(char c){
  unsigned char bfc = bcolor;
  bfc <<= 4;
  bfc |= fcolor;
  kattr = bfc;//0x07;
  unsigned char *video;
  //video = (unsigned char *) (real_screen+ 2 * x + 160 * y);
  if (c == 10) {      
    x = initX;
    y++;
  } else if (c == 8) {  
    if (x) {
        x--;
        video = (unsigned char *) (real_screen+ 2 * x + 160 * y);
        *video = 0x0;
        *(video + 1) = kattr;//0x0;
    }
  } else if (c == 9) {  
    x = x + 8 - (x % 8);
  } else if (c == 13) { 
    x = initX;
  } else {    
      video = (unsigned char *) (real_screen+ 2 * x + 160 * y);
      *video = c;
      *(video + 1) = kattr;
      x++;
    if (x > screenW - 1) {
      x = initX;
      y++;
    }
  }
      if (y > screenH - 1)
      {
          y = y - 1;
          x = x - 1;
      }
        //scrollup(y - screenH - 1);
  setPosCursor(x,y);    
}

void clear_vga()
{
  for(int h = 0; h < 25; h++)
  {
    for(int v = 0; v < 80; v++)
    {
      putc(' ');
    }
  }
  x = 0;
  y = 0;
}

/* put a string in screen */
void print(const char *s, ...){
  va_list ap;

  char buf[16];
  int i, j, size, buflen, neg;

  unsigned char c;
  int ival;
  unsigned int uival;

  va_start(ap, s);

  while ((c = *s++)) {
    size = 0;
    neg = 0;

    if (c == 0)
      break;
    else if (c == '%') {
      c = *s++;
      if (c >= '0' && c <= '9') {
        size = c - '0';
        c = *s++;
      }

      if (c == 'd') {
        ival = va_arg(ap, int);
        if (ival < 0) {
          uival = 0 - ival;
          neg++;
        } else
          uival = ival;
        itoa(buf, uival, 10);

        buflen = strlen(buf);
        if (buflen < size)
          for (i = size, j = buflen; i >= 0;
               i--, j--)
            buf[i] =
                (j >=
                 0) ? buf[j] : '0';

        if (neg)
          print("-%s", buf);
        else
          print(buf);
      }
       else if (c == 'u') {
        uival = va_arg(ap, int);
        itoa(buf, uival, 10);

        buflen = strlen(buf);
        if (buflen < size)
          for (i = size, j = buflen; i >= 0;
               i--, j--)
            buf[i] =
                (j >=
                 0) ? buf[j] : '0';

        print(buf);
      } else if (c == 'x' || c == 'X') {
        uival = va_arg(ap, int);
        itoa(buf, uival, 16);

        buflen = strlen(buf);
        if (buflen < size)
          for (i = size, j = buflen; i >= 0;
               i--, j--)
            buf[i] =
                (j >=
                 0) ? buf[j] : '0';

        print("0x%s", buf);
      } else if (c == 'p') {
        uival = va_arg(ap, int);
        itoa(buf, uival, 16);
        size = 8;

        buflen = strlen(buf);
        if (buflen < size)
          for (i = size, j = buflen; i >= 0;
               i--, j--)
            buf[i] =
                (j >=
                 0) ? buf[j] : '0';

        print("0x%s", buf);
      } else if (c == 's') {
        print((char *) va_arg(ap, int));
      } 
    } else
      putc(c);
  }

  return;
}

/* change cursor position */
void setXY(char xc,char yc){
  x=xc;
  y=yc;
  setPosCursor(x,y);    
}

void change_color(char fontColor, char backColor)
{
  fcolor = fontColor;
  bcolor = backColor;
}

void splash_BerOS(int x, int y, int w, int h,char * version)
{
  change_color(Black,Black);  
  clear_vga();
  /*change_color(LightGrey,LightGrey);   
  for (int ii = y; ii < (y + h); ++ii)
   {
    for (int i = x; i < (x + w); ++i)
     {
       setXY(i,ii);
       print(" ");
     }
   }*/

  setXY(x + ((w-11)/2),y + (h/2) - 1);
  change_color(Green,Black);
  print("Ber");
  change_color(Yellow,Black);
  print("OS"); 
  change_color(LightGrey,Black);
  print(" v%s",version);
  change_color(Black,LightGrey);
  setXY(x + ((w-11)/2),(y + (h/2)));
  print(">         |");
  change_color(Blue,Blue); 
  setXY((x + ((w-11)/2))+1,y + (h/2));
}

window CreateWnd(int x, int y, int w, int h,char * title)
{
  window wnd = {0};
  wnd.x = x;
  wnd.y = y;
  wnd.w = w;
  wnd.h = h;
  wnd.title = title;

  change_color(Black,Black);  
  clearWnd();
  change_color(Black,LightGrey);   
  for (int ii = wnd.y; ii < (wnd.y + wnd.h); ++ii)
   {
    for (int i = wnd.x; i < (wnd.x + wnd.w); ++i)
     {
       setXY(i,ii);
       print(" ");
     }
   }

  setXY(wnd.x,wnd.y);
  change_color(White,Orange);
  for (int iii = wnd.x; iii < (wnd.x + wnd.w); ++iii)
   {
      print(" ");
   }

   setXY(wnd.x + 1,wnd.y);
   print("%s",wnd.title);

   return wnd;
}

void setXYWnd(window* wnd, unsigned int X, unsigned int Y )
{
  screenW = ((wnd->x + wnd->w) - 1);
  screenH = (wnd->y + wnd ->h);
  change_color(Black,LightGrey);
  if(Y == 0) Y = 1;
  initX = (wnd->x + 1);
  setXY((initX + X),(wnd->y + Y));
}

void clearWnd()
{
  screenW = 80;
  screenH = 25;
  x = 0;
  y = 1;
  for(int h = y; h < screenH; h++)
  {
    for(int v = x; v < screenW; v++)
    {
      putc(' ');
    }
  }
  x = 0;
  y = 0;
  setXY(x,y);
}