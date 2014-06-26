section .data

section .text

global __ladd
global __lneg

;		 -24   -20	-16   -12	 -8	   -4	  0	   +4
;	...[tipo][ val][tipo][ val][tipo][ val][tipo][ val]
;	   |operando1H||operando1L||operando2H||operando2L|

__ladd:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  eax, [ebp+8]	; [topo da pilha], 1ro param
L_ADD:
	mov  ebx, [eax-20]	; high op1 = [high op1]
	mov  ecx, [eax-12]	; low op1  = [low op1]
	add  ebx, [eax-4]	; high op1 += high op2
	add  ecx, [eax+4]	; low op1  += low op2 
	jnc  .CARRY_0		; verifica se ouve carryout
	add  ebx, 0x1		; high op1 += carryin
.CARRY_0:
	mov [eax-20], ebx	; [high op1] = high op1
	mov [eax-12], ecx	; [low op1]  = low op1
	
	;mov  eax, ebx
	
	leave
	ret

__lneg:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  eax, [ebp+8] 	 ; [topo da pilha], 1ro param
L_NEG:
	mov  ebx, [eax-4]	 ; high op1 = [high op1]
	mov  ecx, [eax+4]	 ; low op1  = [low op1]
	xor  ebx, 0xFFFFFFFF ; high ~op1		1 xor1= 0, 0 xor1= 1
	xor  ecx, 0xFFFFFFFF ; low ~op1			baseada em complemento de 2, -x = not(x)+1
	add  ecx, 0x1		 ; low ~op1 + 1
	jnc  .CARRY_0		 ; verifica se ouve carryout
	add  ebx, 0x1		 ; high ~op1 += carryin		caryout tem que propagar ate parte high
.CARRY_0:
	mov  [eax-4], ebx	 ; [high op1] = high -op1
	mov  [eax+4], ecx	 ; [low op1]  = low -op1
	
	;mov  eax, ebx
	
	leave
	ret
