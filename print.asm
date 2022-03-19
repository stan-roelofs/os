print:
    pusha

start:
    mov ah, 0x0e
    mov al, [bx]
    cmp al, 0
    je done
    inc bx
    int 0x10
    jmp print

done:
    popa
    ret