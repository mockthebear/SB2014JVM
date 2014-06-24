section .data

section .text

global __push
global __push_w
global __pop

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