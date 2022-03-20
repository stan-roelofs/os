[org 0x7c00]
KERNEL_OFFSET equ 0x1000

mov [BOOT_DRIVE], dl

xor ax, ax
mov ds, ax
mov es, ax

; Set stack safely away from us
mov bp, 0x9000
mov sp, bp

mov bx, MSG_REAL_MODE
call print
call print_nl

call load_kernel
call switch_to_protected_mode

jmp $ ; Jump to start of this line, i.e. loop forever

%include "boot_disk.asm"
%include "print.asm"
%include "print_protected_mode.asm"
%include "gdt.asm"
%include "switch_to_protected_mode.asm"

[bits 16]
load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call print
    call print_nl

    mov bx, KERNEL_OFFSET
    mov dh, 2
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret

[bits 32]
BEGIN_PM:
    mov ebx, MSG_PROT_MODE
    call print_pm
    call KERNEL_OFFSET
    jmp $

MSG_LOAD_KERNEL: db "Loading kernel into memory.",0
MSG_REAL_MODE: db "Started in 16-bit Real Mode",0
MSG_PROT_MODE: db "Successfully landed in 32-bit Protected Mode",0
BOOT_DRIVE: db 0

; Boot sector padding and magic number
times 510-($-$$) db 0
dw 0xaa55