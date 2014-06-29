section .data
buff: dq 0x0

section .text

global __dadd
global __dsub
global __dmul
global __ddiv
global __opDrem
global __dneg

;		 -24   -20	-16   -12	 -8	   -4	  0	   +4
;	...[tipo][ val][tipo][ val][tipo][ val][tipo][ val]
;	   |operando1H||operando1L||operando2H||operando2L|

;		  0	   +4	
;	...[low ][high]...
;	   |valor64bit|

__dadd:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  eax, [ebp+8]	; [topo da pilha], 1ro param
	
	mov  ecx, [eax-20]	; high [buff] = high [op1]
	mov [buff+4], ecx
	mov  ecx, [eax-12]	; low [buff] = low [op1]
	mov [buff], ecx
	fld  qword [buff]	; op1 = [buff]
	
	mov  ecx, [eax-4]	; high [buff] = high [op2]
	mov [buff+4], ecx
	mov  ecx, [eax+4]	; low [buff] = low [op2]
	mov [buff], ecx
	fld  qword [buff]	; op2 = [buff]
	
	faddp				; op1 += op2
	fstp qword [buff]	; [buff] = op1
	
	mov  ecx, [buff+4]	; high [op1] = high [buff]
	mov [eax-20], ecx
	mov  ecx, [buff]	; low [op1] = low [buff]
	mov [eax-12], ecx
	
	;mov  eax, [eax-4]
	
	leave
	ret


__dsub:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  eax, [ebp+8]	; [topo da pilha], 1ro param
	
	mov  ecx, [eax-20]	; high [buff] = high [op1]
	mov [buff+4], ecx
	mov  ecx, [eax-12]	; low [buff] = low [op1]
	mov [buff], ecx
	fld  qword [buff]	; op1 = [buff]
	
	mov  ecx, [eax-4]	; high [buff] = high [op2]
	mov [buff+4], ecx
	mov  ecx, [eax+4]	; low [buff] = low [op2]
	mov [buff], ecx
	fld  qword [buff]	; op2 = [buff]
	
	fsubp				; op1 -= op2
	fstp qword [buff]	; [buff] = op1
	
	mov  ecx, [buff+4]	; high [op1] = high [buff]
	mov [eax-20], ecx
	mov  ecx, [buff]	; low [op1] = low [buff]
	mov [eax-12], ecx
	
	;mov  eax, [eax-4]
	
	leave
	ret


__dmul:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  ecx, [ebp+8]	; [topo da pilha], 1ro param
	
	mov  ecx, [eax-20]	; high [buff] = high [op1]
	mov [buff+4], ecx
	mov  ecx, [eax-12]	; low [buff] = low [op1]
	mov [buff], ecx
	fld  qword [buff]	; op1 = [buff]
	
	mov  ecx, [eax-4]	; high [buff] = high [op2]
	mov [buff+4], ecx
	mov  ecx, [eax+4]	; low [buff] = low [op2]
	mov [buff], ecx
	fld  qword [buff]	; op2 = [buff]
	
	fmulp				; op1 *= op2
	fstp qword [buff]	; [buff] = op1
	
	mov  ecx, [buff+4]	; high [op1] = high [buff]
	mov [eax-20], ecx
	mov  ecx, [buff]	; low [op1] = low [buff]
	mov [eax-12], ecx
	
	;mov  eax, [eax-4]
	
	leave
	ret


__ddiv:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  ecx, [ebp+8]	; [topo da pilha], 1ro param
	
	mov  ecx, [eax-20]	; high [buff] = high [op1]
	mov [buff+4], ecx
	mov  ecx, [eax-12]	; low [buff] = low [op1]
	mov [buff], ecx
	fld  qword [buff]	; op1 = [buff]
	
	mov  ecx, [eax-4]	; high [buff] = high [op2]
	mov [buff+4], ecx
	mov  ecx, [eax+4]	; low [buff] = low [op2]
	mov [buff], ecx
	fld  qword [buff]	; op2 = [buff]
	
	fdivp				; op1 /= op2
	fstp qword [buff]	; [buff] = op1
	
	mov  ecx, [buff+4]	; high [op1] = high [buff]
	mov [eax-20], ecx
	mov  ecx, [buff]	; low [op1] = low [buff]
	mov [eax-12], ecx
	
	;mov  eax, [eax-4]
	
	leave
	ret

__opDrem:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  ecx, [ebp+8]	; [topo da pilha], 1ro param
	
	mov  ecx, [eax-4]	; high [buff] = high [op2]
	mov [buff+4], ecx
	mov  ecx, [eax+4]	; low [buff] = low [op2]
	mov [buff], ecx
	fld  qword [buff]	; op2 = [buff]
	
	mov  ecx, [eax-20]	; high [buff] = high [op1]
	mov [buff+4], ecx
	mov  ecx, [eax-12]	; low [buff] = low [op1]
	mov [buff], ecx
	fld  qword [buff]	; op1 = [buff]
	
	fprem				; op1 %= op2
	fstp qword [buff]	; [buff] = op1
	
	mov  ecx, [buff+4]	; high [op1] = high [buff]
	mov [eax-20], ecx
	mov  ecx, [buff]	; low [op1] = low [buff]
	mov [eax-12], ecx
	
	mov  eax, [eax-4]
	
	leave
	ret


__dneg:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  eax, [ebp+8]	 ; [topo da pilha], 1ro param
	
	mov  ecx, [eax-4]	 ; op1 = [op1]
	xor  ecx, 0x80000000 ; inverte MSB
	mov  [eax-4], ecx	 ; [op1] = -op1
	
	;mov  eax, [eax-4]
	
	leave
	ret

	
