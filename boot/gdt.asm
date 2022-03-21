gdt_start:

gdt_null:
    dd 0 x0
    dd 0 x0

gdt_code:
    dw 0 xffff ; Limit (bits 0-15)
    dw 0 x0 ; Base
    db 0 x0 ; Base
    db 0b10011010 ; flags
    db 0b11001111 ; flags, limit (bits 16-19)
    db 0 x0 ; Base (bits 24-31)

gdt_data:
    dw 0 xffff ; Limit (bits 0-15)
    dw 0 x0 ; Base
    db 0 x0 ; Base
    db 0b10010010; flags
    db 0b11001111; flags, limit (bits 16 -19)
    db 0 x0 ; Base (bits 24-31)

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; Size of our GDT
    dd gdt_start ; Start of the GDT

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start