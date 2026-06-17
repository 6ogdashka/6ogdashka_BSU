global ContainsSymbol

section .text

ContainsSymbol:
    
    test rsi, rsi       ; Проверка str на nullptr
    jz .not_found
    
    mov r8d, edi        ; Сохраняем искомый символ в R8

.loop:
    mov al, [rsi]       ; Читаем символ из строки
    test al, al         
    jz .not_found
    
    cmp al, r8b         ; Сравниваем
    je .found
    
    inc rsi             
    jmp .loop

.found:
    mov al, 1
    ret

.not_found:
    xor al, al
    ret