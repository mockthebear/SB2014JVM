section .data

section .text

global __push

__push:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  eax, [ebp+8]	;ponteiro para topo da pilha
	mov  ecx, [ebp+12]	;tipo de dado
	mov  edx, [ebp+16]	;ponteiro para dado
	
	mov  [eax], ecx
	mov  edx, [edx]
	mov  [eax+4], edx
	
	;mov  eax, eax
	
	leave
	ret

global __push_w

__push_w:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  eax, [ebp+8]	;ponteiro para topo da pilha
	mov  ecx, [ebp+12]	;tipo de dado
	mov  edx, [ebp+16]	;ponteiro para dado
	
	mov  [eax], ecx
	mov  [eax+8], ecx
	mov  ecx,[edx]
	mov  [eax+4], ecx
	mov  ecx,[edx+4]
	mov  [eax+12], ecx
	
	;mov  eax, edx
	
	leave
	ret

global __pop

__pop:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  eax, [ebp+8]	;ponteiro para topo da pilha
	mov  ecx, [ebp+12]	;ponteiro para dado
	
	mov  eax, [eax+4]	;pega campo bytes da pilha
	mov  [ecx], eax		;coloca campo bytes no valor
	
	leave
	ret

global __iadd

__iadd:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  eax, [ebp+8]
	
	mov  ebx, [eax-4]	;penultimo valor
	mov  ecx, [eax+4]	;ulimo  valor
	add  ebx, ecx;
	mov  [eax-4], ebx
	
	mov  eax, ebx
	
	leave
	ret

global __isub

__isub:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  eax, [ebp+8]
	
	mov  ebx, [eax-4]	;penultimo valor
	mov  ecx, [eax+4]	;ulimo  valor
	sub  ebx, ecx
	mov  [eax-4], ebx
	
	mov  eax, ebx
	
	leave
	ret

global __imul

__imul:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  ecx, [ebp+8]
	
	mov  eax, [ecx-4]	;penultimo valor
	mov  ebx, [ecx+4]	;ulimo  valor
	imul ebx
	mov  [ecx-4], eax
	
	;mov  eax, ecx
	
	leave
	ret

global __idiv

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

	mov  [ecx-4], eax
	
	;mov  eax, ecx
	
	leave
	ret


