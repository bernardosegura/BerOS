.extern isr_default_int

.macro	SAVE_REGS
	pushal 
	push %ds
	push %es
	push %fs
	push %gs 
	push %ebx
	movw $0x10,%bx
	movw %bx,%ds
	pop %ebx
.endm

.macro	RESTORE_REGS
	pop %gs
	pop %fs
	pop %es
	pop %ds
	popal
.endm

.macro	INTERRUPT int
.global _asm_int_\int
_asm_int_\int:
	SAVE_REGS
	push $\int
	call isr_default_int
	pop %eax
	movb $0x20,%al
	out %al,$0x20
	RESTORE_REGS
	iret
.endm

.global _asm_schedule
_asm_schedule:
	SAVE_REGS
	call isr_schedule_int
	movb $0x20,%al
	out %al,$0x20
	RESTORE_REGS
	iret

INTERRUPT 1
INTERRUPT 2
