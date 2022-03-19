[org 0x7c00]

; Set stack safely away from us
mov bp, 0x9000
mov sp, bp

mov bx, MSG_REAL_MODE
call print
call print_nl

call switch_to_protected_mode

jmp $ ; Jump to start of this line, i.e. loop forever

%include "print.asm"
%include "print_protected_mode.asm"
%include "boot_disk.asm"
%include "gdt.asm"
%include "switch_to_protected_mode.asm"

[bits 32]
BEGIN_PM:
    mov ebx, MSG_PROT_MODE
    call print_pm

    jmp $

MSG_REAL_MODE: db "Started in 16-bit Real Mode",0
MSG_PROT_MODE: db "Successfully landed in 32-bit Protected Mode",0
BOOT_DRIVE: db 0

; Boot sector padding and magic number
times 510-($-$$) db 0
dw 0xaa55