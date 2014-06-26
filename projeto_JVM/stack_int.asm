section .data

section .text

global __iadd
global __isub
global __imul
global __idiv
global __irem
global __ineg

;		 -8	   -4	  0	   +4	
;	...[tipo][ val][tipo][ val]
;	   |operando 1||operando 2|

__iadd:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  eax, [ebp+8]	; [topo da pilha], 1ro param
	
	mov  ebx, [eax-4]	; op1 = [op1]
	mov  ecx, [eax+4]	; op2 = [op2]
	add  ebx, ecx		; op1 += op2
	mov  [eax-4], ebx	; [op1] = op1
	
	;mov  eax, ebx
	
	leave
	ret


__isub:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  eax, [ebp+8]	; [topo da pilha], 1ro param
	
	mov  ebx, [eax-4]	; op1 = [op1]
	mov  ecx, [eax+4]	; op2 = [op2]
	sub  ebx, ecx		; op1 -= op2
	mov  [eax-4], ebx	; [op1] = op1
	
	;mov  eax, ebx
	
	leave
	ret


__imul:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  ecx, [ebp+8]	; [topo da pilha], 1ro param
	
	mov  eax, [ecx-4]	; op1 = [op1]
	mov  ebx, [ecx+4]	; op2 = [op2]
	imul ebx			; op1 *= op2	imul pega sempre eax como 1ro param
	mov  [ecx-4], eax	; [op1] = op1
	
	;mov  eax, ecx
	
	leave
	ret


__idiv:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  ecx, [ebp+8]	; [topo da pilha], 1ro param
DIVIDE:
	mov  eax, [ecx-4]	; op1 = [op1]
	mov  ebx, [ecx+4]	; op2 = [op2]
	mov  edx, 0			; high op1 = 0
	cmp  eax, 0			; verifica se op1 < 0
	jg   .L1  
	mov  edx, -1		; high op1 = -1
.L1:
	idiv ebx			; op1 /= op2	idiv pega (edx:eax) como  1ro param

	mov  [ecx-4], eax	; [op1] = op1
	
	;mov  eax, ecx
	
	leave
	ret

__irem:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  ecx, [ebp+8]	; [topo da pilha], 1ro param
REM:
	mov  eax, [ecx-4]	; op1 = [op1]
	mov  ebx, [ecx+4]	; op2 = [op2]
	mov  edx, 0			; high op1 = 0
	cmp  eax, 0			; verifica se op1 < 0
	jg   .L1  
	mov  edx, -1		; high op1 -1
.L1:
	idiv ebx			; op1 /= op2

	mov  [ecx-4], edx	; [op1] = resto		idiv armazena quociente no eax e resto no edx
	
	;mov  eax, ecx
	
	leave
	ret


__ineg:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  eax, [ebp+8]	 ; [topo da pilha], 1ro param
	
	mov  ecx, [eax+4]	 ; op1 = [op1]
	xor  ecx, 0xFFFFFFFF ; ~op1		1 xor1= 0, 0 xor1= 1
	add  ecx, 0x1		 ; ~op1+1	baseada em complemento de 2, -x = not(x)+1
	mov  [eax+4], ecx	 ; [op1] = -op1
	
	;mov  eax, ecx
	
	leave
	ret

	
