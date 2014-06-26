section .data

section .text

global __get_byte
global __to_value32
global __get_high
global __to_value64

__get_byte:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  eax, [ebp+8]	; [void], 1ro param recebe void * podendo ser int * ou float *

	mov  eax, [eax]		; bytes = [void]
						; return bytes			retorna valor que esta no eax
	;mov eax, ebx
	
	leave
	ret

; faz mesmo efeito que &var_i = (int *) &bytes ou &var_f = (float *) &bytes
__to_value32:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  eax, [ebp+8]	; [void], 1ro param recebe void * podendo ser int * ou float *
	mov  ecx, [ebp+12]	; bytes, 2do param

	mov  [eax], ecx		; [void] = bytes
	
	;mov eax, ebx
	
	leave
	ret

;		  0	   +4	
;	...[low ][high]...
;	   |valor64bit|

__get_high:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  eax, [ebp+8]	; [void], 1ro param recebe void * podendo ser long * ou double *

	mov  eax, [eax+4]	; high = high [void]
						; return high			retorna valor que esta no eax
	;mov eax, ebx
	
	leave
	ret
	
; faz mesmo efeito que &var_l = (long *) &(high:low) ou &var_d = (double *) &(high:low)
__to_value64:
	push ebp
	mov  ebp, esp
	sub  esp, 0x40
	
	mov  eax, [ebp+8]	; [void], 1ro param recebe void * podendo ser long * ou double *
	mov  ecx, [ebp+12]	; high bytes, 2do param
	mov  edx, [ebp+16]	; low bytes, 3ro param
	
	mov  [eax+4], ecx	; high [void] = high bytes
	mov  [eax], edx		; low  [void] = low bytes
	
	leave
	ret
