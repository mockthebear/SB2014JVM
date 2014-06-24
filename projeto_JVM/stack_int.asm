section .data

section .text

global __iadd
global __isub
global __imul
global __idiv
global __irem
global __ineg

__iadd:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  eax, [ebp+8]
	
	mov  ebx, [eax-4]	;penultimo valor
	mov  ecx, [eax+4]	;ulimo  valor
	add  ebx, ecx;
	mov  [eax-4], ebx	;penultimo valor
	
	;mov  eax, ebx
	
	leave
	ret


__isub:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  eax, [ebp+8]
	
	mov  ebx, [eax-4]	;penultimo valor
	mov  ecx, [eax+4]	;ulimo  valor
	sub  ebx, ecx
	mov  [eax-4], ebx	;penultimo valor
	
	;mov  eax, ebx
	
	leave
	ret


__imul:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  ecx, [ebp+8]
	
	mov  eax, [ecx-4]	;penultimo valor
	mov  ebx, [ecx+4]	;ulimo  valor
	imul ebx
	mov  [ecx-4], eax	;penultimo valor
	
	;mov  eax, ecx
	
	leave
	ret


__idiv:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  ecx, [ebp+8]
DIVIDE:
	mov  eax, [ecx-4]	;penultimo valor
	mov  ebx, [ecx+4]	;ulimo  valor
	mov  edx, 0			;parte alta 0
	cmp  eax, 0			;verifica se eax < 0
	jg   .L1  
	mov  edx, -1		;parte alta -1
.L1:
	idiv ebx

	mov  [ecx-4], eax	;penultimo valor
	
	;mov  eax, ecx
	
	leave
	ret

__irem:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  ecx, [ebp+8]
REM:
	mov  eax, [ecx-4]	;penultimo valor
	mov  ebx, [ecx+4]	;ulimo  valor
	mov  edx, 0			;parte alta 0
	cmp  eax, 0			;verifica se eax < 0
	jg   .L1  
	mov  edx, -1		;parte alta -1
.L1:
	idiv ebx

	mov  [ecx-4], edx	;penultimo valor
	
	;mov  eax, ecx
	
	leave
	ret


__ineg:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  eax, [ebp+8]
	
	mov  ecx, [eax+4]	;ulimo  valor
	xor  ebx, ebx
	sub  ebx, ecx
	mov  [eax+4], ebx	;ulimo  valor
	
	;mov  eax, ebx
	
	leave
	ret

