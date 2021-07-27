#define RAMSCREEN 0xB8000 /* debut de la memoire video */
#define SIZESCREEN 0xFA0  /* 4000, nombres d'octets d'une page texte */
#define SCREENLIM 0xB8FA0

/** standart io color **/
enum Color
{
      Black       =0,
      Blue        =1,
      Green       =2,
      Cyan        =3,
      Red         =4,
      Magenta     =5,
      Orange      =6,
      LightGrey   =7,
      DarkGrey    =8,
      LightBlue   =9,
      LightGreen  =10,
      LightCyan   =11,
      LightRed    =12,
      LightMagenta=13,
      Yellow      =14,
      White       =15
};

typedef struct wnd
{
      int x;
      int y;
      int w;
      int h;
      char* title;
}window;

typedef __builtin_va_list va_list;

#define va_start(a,b)  __builtin_va_start(a,b)
#define va_end(a)      __builtin_va_end(a)
#define va_arg(a,b)    __builtin_va_arg(a,b)
#define __va_copy(d,s) __builtin_va_copy((d),(s))

extern unsigned int strlen( const char* string);

extern void outb(unsigned int ad,unsigned char v);
extern unsigned char inb(unsigned int ad);

extern void setPosCursor(char xx, char yy);

extern void putc(char c);
extern void putcw(window* wnd,int x, int y,char c);
extern void scrollup(unsigned int n);
extern void itoa(char *buf, unsigned long int n, int base);
extern void print(const char *s, ...);
extern void setXY(char xc,char yc);

extern void clear_vga(void);
extern void change_color(char fontColor, char backColor);

extern void splash_BerOS(int x, int y, int w, int h, char * version);
extern window CreateWnd(int x, int y, int w, int h,char * title);   
extern void setXYWnd(window* wnd, unsigned int X, unsigned int Y );
extern void clearWnd();