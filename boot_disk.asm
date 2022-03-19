; dh = number of sectors, dl = disk number
; es:bx points to buffer
disk_load:
    pusha
    push dx

    ; Setup parameters
    mov ah, 0x02 ; BIOS read sector
    mov al, dh
    mov cl, 0x02 ; Use sector 2 since sector 1 is our boot sector
    mov ch, 0x00 ; Cylinder
    mov dh, 0x00 ; Head number
    
    int 0x13 ; BIOS interrupt to read disk
    jc disk_error ; BIOS sets carry bit if error

    pop dx
    cmp al, dh ; Check whether we read all sectors (interrupt stores the number of sectors read in al)
    jne sectors_error

    popa
    ret

disk_error:
    mov bx, DISK_ERROR
    call print
    call print_nl
    mov dh, ah ; ah = error code
    call print_hex
    jmp $

sectors_error:
    mov bx, SECTORS_ERROR
    call print
    jmp $

DISK_ERROR:
    db "Disk read error", 0

SECTORS_ERROR:
    db "Error: did not read all sectors", 0