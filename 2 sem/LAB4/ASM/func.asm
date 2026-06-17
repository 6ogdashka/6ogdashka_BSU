section .text
global calc_func

calc_func:
    push ebp
    mov ebp, esp

    fld qword [ebp+8]
    fsqrt
    
    fld st0
    fmul st0, st0
    fld1
    fsubrp st1, st0
    fsqrt
    
    fxch st1
    fpatan
    
    fld1
    fsub qword [ebp+8]
    fmul qword [ebp+8]
    fsqrt

    fdivp st1, st0
    
    pop ebp
    ret