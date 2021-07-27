////////////////////////////////////////////////IDT///////////////////////////////////////////////////////////////
#define INTGATE  0x8E00   /* utilise pour gerer les interruptions */
#define IDTSIZE   0xFF  /* nombre max. de descripteurs dans la table */
#define IDTBASE   0x00000000  /* addr. physique ou doit resider la IDT */

/* Descripteur de segment */
struct idtdesc {
  unsigned short offset0_15;
  unsigned short select;
  unsigned short type;
  unsigned short offset16_31;
} __attribute__ ((packed));

/* Registre IDTR */
struct idtr {
  unsigned short limite;
  unsigned int base;
} __attribute__ ((packed));

struct idtdesc   kidt[IDTSIZE];     /* IDT table */
struct idtr    kidtr;        /* IDTR registry */

extern void _asm_int_1();
extern void _asm_schedule();

void init_idt_desc(unsigned short select, unsigned int offset, unsigned short type, struct idtdesc *desc);

void init_idt(void);
