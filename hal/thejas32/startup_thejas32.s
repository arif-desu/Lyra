	.section .init
	.global _start
	.type _start,@function

_start:
# Set up stack pointer
	la  tp, _gp
	la sp, _estack

/* Load data section */
	la a0, _data_lma
	la a1, _data
	la a2, _edata
	bgeu a1, a2, 2f
1:
	lw t0, (a0)
	sw t0, (a1)
	addi a0, a0, 4
	addi a1, a1, 4
	bltu a1, a2, 1b
2:
	/* Clear bss section */
	la a0, __bss_start
	la a1, _end
	bgeu a0, a1, 2f
1:
	sw zero, (a0)
	addi a0, a0, 4
	bltu a0, a1, 1b
2:

	/* Call global constructors */
	la a0, __libc_fini_array
	call atexit
	call __libc_init_array

	/* Set trap entry */
	la t0, _trap_entry # 
	csrw mtvec, t0

	/* Set external interrupt enable (EIE) bit in mie register */
	li t0, 0x00000800			
	csrrs x0, mie, t0

	/* Set interrupt enable bit in mstatus register */
	li t0, 0x00000008
	csrrs x0, mstatus, t0

	/* argc = 0, argv = 0 */
	li a0, 0
	li a1, 0
	call main

LoopForever:
	j LoopForever

.size _start, .-_start

/*----------------------------------------------------------*/
.align 2

	.section .text._trap_entry,"ax",@progbits
	.global _trap_entry

_trap_entry:
	addi sp, sp, -31*4

	# Save register context
	sw x1, 4(sp) 
	sw x2, 8(sp)
	sw x3, 12(sp)
	sw x4, 16(sp)
	sw x5, 20(sp)
	sw x6, 24(sp)
	sw x7, 28(sp)
	sw x8, 32(sp)
	sw x9, 36(sp)
	sw x10, 40(sp)
	sw x11, 44(sp)
	sw x12, 48(sp)
	sw x13, 52(sp)
	sw x14, 56(sp)
	sw x15, 60(sp)
	sw x16, 64(sp)
	sw x17, 68(sp)
	sw x18, 72(sp)
	sw x19, 76(sp)
	sw x20, 80(sp)
	sw x21, 84(sp)
	sw x22, 88(sp)
	sw x23, 92(sp)
	sw x24, 96(sp)
	sw x25, 100(sp)
	sw x26, 104(sp)
	sw x27, 108(sp)
	sw x28, 112(sp)
	sw x29, 116(sp)
	sw x30, 120(sp)
	sw x31, 124(sp)

	# Jump to trap handler
	jal _trap_handler

	# Restore register context on return
	lw x1, 4(sp) 
	lw x2, 8(sp)
	lw x3, 12(sp)
	lw x4, 16(sp)
	lw x5, 20(sp)
	lw x6, 24(sp)
	lw x7, 28(sp)
	lw x8, 32(sp)
	lw x9, 36(sp)
	lw x10, 40(sp)
	lw x11, 44(sp)
	lw x12, 48(sp)
	lw x13, 52(sp)
	lw x14, 56(sp)
	lw x15, 60(sp)
	lw x16, 64(sp)
	lw x17, 68(sp)
	lw x18, 72(sp)
	lw x19, 76(sp)
	lw x20, 80(sp)
	lw x21, 84(sp)
	lw x22, 88(sp)
	lw x23, 92(sp)
	lw x24, 96(sp)
	lw x25, 100(sp)
	lw x26, 104(sp)
	lw x27, 108(sp)
	lw x28, 112(sp)
	lw x29, 116(sp)
	lw x30, 120(sp)
	lw x31, 124(sp)

	addi sp, sp, 31*4
	mret					/* Set PC to mepc */

.size _trap_entry, .-_trap_entry