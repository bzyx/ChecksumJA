.486 
.model flat, stdcall 
 
.code 
 
MyProc1 proc x: DWORD, y: BYTE 
 
	xor eax, eax
	xor cl, cl
	mov eax, x 
	mov cl, y 
	shl eax, cl
    ret
       
MyProc1 endp 
 
DodawanieAsm proc x: DWORD, y: DWORD 
	xor eax, eax
	xor ecx, ecx
	mov eax, x
	mov ecx, y
	add eax, ecx
	ret
       
DodawanieAsm endp  

CRC32_MASM proc x: DWORD, y: DWORD, z: DWORD
	xor eax, eax
	mov eax, 10
	ret 
CRC32_MASM endp

ADLER32_MASM proc x: DWORD, y: DWORD, z: DWORD
	xor eax, eax
	mov eax, x
	add eax, 1
	ret 
ADLER32_MASM endp

end