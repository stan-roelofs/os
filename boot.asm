[org 0x7c00]

mov bx, hello_world
call print

jmp $ ; Jump to start of this line, i.e. loop forever

%include "print.asm"

hello_world:
    db "Hello, world!",0


; Padding and magic number
times 510-($-$$) db 0
dw 0xaa55