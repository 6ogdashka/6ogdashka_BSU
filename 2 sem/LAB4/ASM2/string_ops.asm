section .text
global asm_compare
global asm_copy
global asm_replace

asm_compare:
    xor rax, rax
    xor rcx, rcx
.loop:
    mov al, [rdi]
    mov cl, [rsi]
    cmp al, cl
    jne .done
    test al, al
    jz .done
    inc rdi
    inc rsi
    jmp .loop
.done:
    sub eax, ecx
    ret

asm_copy:
.loop:
    mov al, [rsi]
    mov [rdi], al
    test al, al
    jz .done
    inc rdi
    inc rsi
    jmp .loop
.done:
    ret

asm_replace:
.loop:
    mov al, [rdi]
    test al, al
    jz .done
    cmp al, sil
    jne .next
    mov [rdi], dl
.next:
    inc rdi
    jmp .loop
.done:
    ret