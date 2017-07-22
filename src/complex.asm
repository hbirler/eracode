global conj_asm
global norm_asm

section .data

section .text

;Note about calling conventions:
;From left to right, pass as many parameters as will fit in registers. The order in which registers are allocated, are:
;For integers and pointers, rdi, rsi, rdx, rcx, r8, r9.
;For floating-point (float, double), xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7.

conj_asm:
	;xmm0 for real/imaginary
	;xmm1 for sign bit
	
	movss	xmm0, DWORD [rdi]	;move real to reg
	movss	DWORD [rsi], xmm0	;move real to target
	movss	xmm0, DWORD [rdi+4]	;move imag to reg
	;set xmm1 to sign bit
	movss	xmm1, DWORD [.sign_bit]
	xorps	xmm0, xmm1			;negate imaginary
	movss	DWORD [rsi+4], xmm0	;move imaginary to target
	ret
.sign_bit:
	dd	2147483648	;2^31



norm_asm:
	;computes sqrt(a^2 + b^2)
	;xmm0 for a
	;xmm1 for b
	;xmm2 for .sign_bit_rev which is used to reverse sign bits
	;		  also used for swapping values
	;xmm3 for .inf and .zero (checking for corner cases)
	
	;move (a,b) from memory to registers (xmm0, xmm1)
	movss	xmm0, DWORD [rdi]
	movss	xmm1, DWORD [rdi+4]
	;load the reversed sign bit into register xmm2
	movss	xmm2, DWORD [.sign_bit_rev]
	;load infinity into register xmm3
	movss xmm3, DWORD [.inf]
	;check if any of the numbers are nan
	;go to is_nan if so
	ucomiss xmm0, xmm3	;is nan
	jp .is_nan
	ucomiss xmm1, xmm3
	jp .is_nan
	;get the absolute values of the numbers
	;by 'and'ing with the reversed sign bit number
	andps	xmm0, xmm2	;absolute value	(erase sign bit)
	andps	xmm1, xmm2	;absolute value	(erase sign bit)
	;check if any of the numbers are infinity
	;result is infinity if so
	ucomiss xmm0, xmm3	;is infinity
	jz .is_inf
	ucomiss xmm1, xmm3
	jz .is_inf
	;compare the two values
	;swap values if xmm0 > xmm1
	ucomiss xmm0, xmm1	;carry-flag set if xxm0 < xmm1
	jnc .swap_done
	movss   xmm3, xmm0  ;swap values
	movss   xmm0, xmm1
	movss   xmm1, xmm3
.swap_done:
	movss xmm3, DWORD [.zero]
	;check if xmm0 (a) is zero
	;if a is zero, result is xmm1 (b)
	ucomiss xmm0, xmm3
	jnz .not_zero	;a!=0
	movss xmm0, xmm1
	andps	xmm0, xmm2
	ret
.not_zero:
	divss xmm1, xmm0	;b /= a
	mulss xmm1, xmm1	;b := b*b
	addss xmm1, DWORD [.one]	;b += 1
	sqrtss xmm1, xmm1	;b := sqrt(b)
	mulss xmm0, xmm1	;a *= b
	ret
.is_nan:
	;return nan
	movss xmm0, DWORD [.nan]
	ret
.is_inf:
	;return infinity
	movss xmm0, DWORD [.inf]
	ret

.sign_bit_rev:		;all bits are 1 except the sign bit
	dd	2147483647	;2^31-1
.one:
	dd 1.0
.zero:
	dd 0.0
.nan:
	dd __NaN__
.inf:
	dd __Infinity__ 