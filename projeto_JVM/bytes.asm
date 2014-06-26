section .data

section .text

global __to_byte
global __get_high
global __to_value32
global __to_value64

__to_byte:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  eax, [ebp+8]	;fonte

	mov  eax, [eax]
	
	;mov eax, ebx
	
	leave
	ret

__get_high:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  eax, [ebp+8]	;fonte

	mov  eax, [eax+4]
	
	;mov eax, ebx
	
	leave
	ret

__to_value32:
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

__to_value64:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  eax, [ebp+8]
	mov  ecx, [ebp+12]
	mov  edx, [ebp+16]
	
	mov  [eax+4], ecx
	mov  [eax], edx
	
	leave
	ret
