section .data

section .text

global __fadd
global __fsub
global __fmul
global __fdiv
global __frem
global __fneg

;		 -8	   -4	  0	   +4	
;	...[tipo][ val][tipo][ val]
;	   |operando 1||operando 2|

__fadd:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  eax, [ebp+8]	; [topo da pilha], 1ro param
	
	fld  dword [eax-4]	; op1 = [op1]
	fld  dword [eax+4]	; op2 = [op2]
	faddp				; op1 += op2
	fstp  dword [eax-4]	; [op1] = op1
	
	;mov  eax, [eax-4]
	
	leave
	ret


__fsub:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  eax, [ebp+8]	; [topo da pilha], 1ro param
	
	fld  dword [eax-4]	; op1 = [op1]
	fld  dword [eax+4]	; op2 = [op2]
	fsubp				; op1 -= op2
	fst  dword [eax-4]	; [op1] = op1
	
	;mov  eax, [eax-4]
	
	leave
	ret


__fmul:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  ecx, [ebp+8]	; [topo da pilha], 1ro param
	
	fld  dword [eax-4]	; op1 = [op1]
	fld  dword [eax+4]	; op2 = [op2]
	fmulp				; op1 *= op2
	fst  dword [eax-4]	; [op1] = op1
	
	;mov  eax, [eax-4]
	
	leave
	ret


__fdiv:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  ecx, [ebp+8]	; [topo da pilha], 1ro param
	
	fld  dword [eax-4]	; op1 = [op1]
	fld  dword [eax+4]	; op2 = [op2]
	fdivp				; op1 /= op2
	fst  dword [eax-4]	; [op1] = op1
	
	;mov  eax, [eax-4]
	
	leave
	ret

__frem:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  ecx, [ebp+8]	; [topo da pilha], 1ro param
	
	fld  dword [eax+4]	; op2 = [op2]
	fld  dword [eax-4]	; op1 = [op1]
	fprem				; op1 %= op2
	fst  dword [eax-4]	; [op1] = op1
	
	;mov  eax, [eax-4]
	
	leave
	ret


__fneg:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  eax, [ebp+8]	 ; [topo da pilha], 1ro param
	
	mov  ecx, [eax+4]	 ; op1 = [op1]
	xor  ecx, 0x80000000 ; inverte MSB
	mov  [eax+4], ecx	 ; [op1] = -op1
	
	;mov  eax, [eax+4]
	
	leave
	ret

	
