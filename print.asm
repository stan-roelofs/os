; Prints the string pointed to by bx
print:
    pusha ; Push registers to stack

start:
    mov ah, 0x0e ; Tells video interrupt that we want to write a character in TTY mode
    mov al, [bx] ; Move next character to al
    cmp al, 0
    je done
    inc bx
    int 0x10 ; Raise video interrupt to write character 
    jmp start

done:
    popa ; Pop registers from stack
    ret

; Prints new line
print_nl:
    pusha

    mov ah, 0x0e
    mov al, 0x0a ; newline
    int 0x10

    mov al, 0x0d ; carriage return
    int 0x10

    popa
    ret

; Prints a hexadecimal number stored in dx
print_hex:
    pusha

    mov cx, 0 ; index

hex_loop:
    cmp cx, 4
    je end

    ; Convert last character of dx to ascii
    mov ax, dx
    and ax, 0x000f
    add al, 0x30 ; Numbers start at 0x30 in ascii

    ; If al > 9, we add another offset to print A-F
    cmp al, 0x39
    jle store_character
    add al, 7

; Place the character at the right position
store_character:
    mov bx, HEX_OUT + 5
    sub bx, cx
    mov [bx], al
    shr dx, 4
    inc cx
    jmp hex_loop

end:
    mov bx, HEX_OUT
    call print

    popa
    ret

HEX_OUT:
    db "0x0000",0