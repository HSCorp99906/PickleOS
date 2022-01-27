bits 16
org 0x7C00

xor ax, ax
mov ds, ax
mov es, ax
mov ss, ax

mov bp, 0x9C00
mov sp, bp


_start:
    mov [BOOT_DRIVE], dl

    mov ah, 0x0
    mov al, 0x2
    int 0x10

    mov si, start_msg
    call puts

    mov si, welcome
    call puts

    mov si, boot_option
    call puts

    mov si, reboot_option
    call puts

    call read_keys

    mov dl, [BOOT_DRIVE]
    call disk_load

    mov ah, 0x0
    mov al, 0x2
    int 0x10

    ; We are gonna enter 32-bit protected mode.

    cli                 ; Disable interrupts.
    lgdt [gdt_desc]     ; Tell CPU about our GDT.

    mov eax, cr0
    or eax, 0x1         ; Set the special bit.
    mov cr0, eax

    ; YAY! We are in protected mode.

    ; Flush CPU pipeline to prevent 16-bit processes
    ; from operating in 32-bit mode.
    ; This will also change CS to our new code selector.
    jmp CODE_SEG:init_pm

BOOT_DRIVE: db 0

puts:
    mov ah, 0x0E    ; BIOS printchar function.
    lodsb           ; Load byte from SI into AL and increment SI. (*al = *si++)
    or al, al       ; If AL is zero, then the zero flag will be set.
    jz rm_ret
    int 0x10
    jmp puts


rm_ret: ret


read_keys:
    mov ah, 0x00
    int 0x16
    cmp al, 'r'
    je reboot
    cmp al, 'b'
    je rm_ret
    jmp read_keys


disk_load:
    mov ah, 0x42
    mov si, dap
    int 0x13
    jc disk_err
    ret

disk_err:
    mov si, disk_error_msg
    call puts
    cli             ; Disable interrupts.
    hlt             ; Halt CPU.


reboot: jmp 0xFFFF:0x0

dap:
    db 0x10     ; Size of DAP.
    db 0x0      ; Unused.
    dw 0xA      ; Number of sectors to read.
    dw 0x1000   ; Dest offset.
    dw 0x0      ; Dest segment.
    dq 0x1      ; Sector to start reading at.


start_msg: db "KessBoot 1.0", 0x0D, 0x0A, 0
welcome: db "Welcome to PickleOS! Please choose an option.", 0x0D, 0x0A, 0x0D, 0x0A, 0
boot_option: db "[B]oot", 0x0D, 0x0A, 0
reboot_option: db "[R]eboot", 0x0D, 0x0A, 0
disk_error_msg: db "FATAL: Failed to read from disk.", 0x0D, 0x0A, 0


; GDT: It defines what 
; memory can be executed (The Code Descriptor), 
; and what area contains data (Data Descriptor). 

; This is used because everything about memory
; has changed in protected mode.


gdt_start:
    gdt_null:
        dd 0x0
        dd 0x0
    gdt_code:
        ; Type flags:
        ; Present: 1 since we are using code.
        ; Privilege: 00 higest privilige.
        ; Descriptor type: 1 for code/data.
        ; Code: 1.
        ; Conforming: 0 so segments with a lower privilege may not call code in this segment.
        ; Readable: 1.
        ; Accessed: 0.

        ; Other flags:
        ; Granularity: 1 so we can reach father into memory.
        ; 32-bit default: 1 since our segment will have 32-bit code.
        ; 64-bit code segment: 0.
        ; AVL 0.
        ; Limit: 1111.

        dw 0xFFFF       ; Limit.
        dw 0x0          ; Base.
        db 0x0          ; Base.
        db 10011010b    ; 1st flags, type flags.
        db 11001111b    ; 2nd flags, type flags.
        db 0x0
    gdt_data:
        ; Type flags: 
        ; Code: 0.
        ; Expand down: 0.
        ; Writable: 0.
        ; Accessed: 0.

        dw 0xFFFF       ; Limit.
        dw 0x0          ; Base.
        db 0x0          ; Base.
        db 10010010b    ; 1st flags, type flags.
        db 11001111b    ; 2nd flags, type flags.
        db 0x0
gdt_end:


gdt_desc:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start


bits 32
init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov fs, ax
    mov gs, ax

    jmp _PM

_PM:
    call 0x1000

; Sector padding to fill 512 bytes with the last
; two bytes being the magic number.
times 510-($-$$) db 0
dw 0xAA55
