section .data

section .text

global __byte_copy
global __byte_copy_w
global __to_value64

__byte_copy:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  eax, [ebp+8]	;fonte
	mov  ecx, [ebp+12]	;bytes

	mov  ebx, [eax]
	mov  [ecx], ebx
	
	mov eax, ebx
	
	leave
	ret

__byte_copy_w:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  eax, [ebp+8]	;fonte
	mov  ecx, [ebp+12]	;bytes
	
	mov  ebx, [eax]
	mov  [ecx], ebx
	mov  ebx, [eax+4]
	mov  [ecx+4], ebx
	
	mov eax, ebx
	
	leave
	ret

__to_value64:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  eax, [ebp+8]
	mov  ecx, [ebp+12]
	mov  edx, [ebp+16]
	
	mov  [eax], ecx
	mov  [eax+4], edx
	
	leave
	ret
