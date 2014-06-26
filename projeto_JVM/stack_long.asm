section .data

section .text

global __ladd
global __lneg

;		 -24   -20	-16   -12	 -8	   -4	  0	   +4
;	...[tipo][ val][tipo][ val][tipo][ val][tipo][ val]
;	...|operando1H||operando1L||operando2H||operando2L|

__ladd:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  eax, [ebp+8]
L_ADD:
	xor  ecx, ecx
	mov  ebx, [eax-12]	;penultimo valor L
	add  ebx, [eax+4]	;ultimo  valor L
	jnc  .CARRY_0
	add  ecx, 0x1
.CARRY_0:
	mov [eax-12], ebx
	
	mov  ebx, [eax-20]
	add  ebx, [eax-4]
	add  ebx, ecx
	mov [eax-20], ebx
	
	;mov  eax, ebx
	
	leave
	ret

__lneg:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  eax, [ebp+8]
L_NEG:
	mov  ebx, [eax-4]	;penultimo valor
	mov  ecx, [eax+4]	;ultimo  valor
	xor  ebx, 0xFFFFFFFF
	xor  ecx, 0xFFFFFFFF
	add  ecx, 0x1
	jnc  .CARRY_0
	add  ebx, 0x1
.CARRY_0:
	mov  [eax-4], ebx	;penultimo valor
	mov  [eax+4], ecx	;ultimo  valor
	
	;mov  eax, ebx
	
	leave
	ret
