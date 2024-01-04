	.section .init
	.global _start
	.type _start,@function

_start:
# Set up stack pointer
	la  tp, _end
  	add tp, tp, 1024
  	add sp, sp, tp
# Jump to main
	j main

	
	