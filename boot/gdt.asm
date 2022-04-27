GDT_BEGIN: ; don't remove the labels, they're needed to compute sizes and jumps
    ; null descriptor
    dd 0x0 ; 4 byte
    dd 0x0 ; 4 byte

; GDT for code segment. base = 0x00000000, length = 0xfffff
; for flags, refer to os-dev.pdf document, page 36
GDT_CODE:
    dw 0xffff    ; segment length, bits 0-15
    dw 0x0       ; segment base, bits 0-15
    db 0x0       ; segment base, bits 16-23
    db 10011010b ; flags (8 bits)
    db 11001111b ; flags (4 bits) + segment length, bits 16-19
    db 0x0       ; segment base, bits 24-31

; GDT for data segment. base and length identical to code segment
; some flags changed, again, refer to os-dev.pdf
GDT_DATA:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0

GDT_END:

; GDT descriptor
GDT_DESC:
    dw GDT_END - GDT_BEGIN - 1 ; size (16 bit), always one less of its true size
    dd GDT_BEGIN ; address (32 bit)

; define some constants for later use
CODE_SEG equ GDT_CODE - GDT_BEGIN
DATA_SEG equ GDT_DATA - GDT_BEGIN
