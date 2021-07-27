//////////////////////////////////////////////GDT///////////////////////////////////////////////////
#define GDTSIZE   0xFF  /* nombre max. de descripteurs dans la table */
#define GDTBASE   0x00000800  /* addr. physique ou doit resider la gdt */

/* Descripteur de segment */
struct gdtdesc {
  unsigned short lim0_15;
  unsigned short base0_15;
  unsigned char base16_23;
  unsigned char acces;
  unsigned char lim16_19:4;
  unsigned char other:4;
  unsigned char base24_31;
} __attribute__ ((packed));

/* Registre GDTR */
struct gdtr {
  unsigned short limite;
  unsigned int base;
} __attribute__ ((packed));

struct tss {
  unsigned short previous_task, __previous_task_unused;
  unsigned int esp0;
  unsigned short ss0, __ss0_unused;
  unsigned int esp1;
  unsigned short ss1, __ss1_unused;
  unsigned int esp2;
  unsigned short ss2, __ss2_unused;
  unsigned int cr3;
  unsigned int eip, eflags, eax, ecx, edx, ebx, esp, ebp, esi, edi;
  unsigned short es, __es_unused;
  unsigned short cs, __cs_unused;
  unsigned short ss, __ss_unused;
  unsigned short ds, __ds_unused;
  unsigned short fs, __fs_unused;
  unsigned short gs, __gs_unused;
  unsigned short ldt_selector, __ldt_sel_unused;
  unsigned short debug_flag, io_map;
} __attribute__ ((packed));

struct tss     default_tss;
struct gdtdesc   kgdt[GDTSIZE];    /* GDT */
struct gdtr    kgdtr;        /* GDTR */

void init_gdt_desc(unsigned int base, unsigned int limite, unsigned char acces, unsigned char other,struct gdtdesc *desc);

void init_gdt(void);