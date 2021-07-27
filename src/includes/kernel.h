#include <io.h>
#include <gdt.h>
#include <idt.h>
#include <sis.h>
#include <kbmap.h>
#include <keyboard.h>
#include <displayNormal.h>
#include <displayAlien.h>
#include <displayDigito.h>

typedef struct t
{
  unsigned int Hour;
  unsigned int Minute;
  unsigned int Second;
  char* ap;
}time;

typedef struct d
{
	unsigned int Year;
	unsigned int Month;
	char* Mth; 
	unsigned int Day;
	unsigned int Weekday;
	char* Wday;
}date;

void init(char* version);
void barraSuperior(char* version);
//typedef char digito[10][8];
extern void isr_schedule_int();
extern void updateClock();
extern time getTime();
extern date getDate();
extern void updateDate();
extern void dosPuntos();
extern void unPunto();
extern void hora(char **digito_0, char **digito_1);
extern void minutos(char **digito_0, char **digito_1);
extern void segundos(char **digito_0, char **digito_1);
extern void ampm(char digito_0[10][8], char digito_1[10][8]);
extern void setHora(char n0, char n1);
extern void setMinutos(char n0, char n1);
extern void setSegundos(char n0, char n1);
extern void setDisplayFot(char fnt);
extern void setShowRelojPanel();
extern void changeColorDisplay(char color);





