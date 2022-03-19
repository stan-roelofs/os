[org 0x7c00]

mov [BOOT_DRIVE], dl ; BIOS stores our boot drive in dl

; Set stack safely away from us
mov bp, 0x8000
mov sp, bp

mov bx, 0x9000
mov dh, 2
mov dl, [BOOT_DRIVE]
call disk_load

mov dx, [0x9000]
call print_hex

jmp $ ; Jump to start of this line, i.e. loop forever

%include "print.asm"
%include "boot_disk.asm"

; Global variables
BOOT_DRIVE: db 0

; Boot sector padding and magic number
times 510-($-$$) db 0
dw 0xaa55

; Sector 2
times 256 dw 0xdada
times 256 dw 0xface