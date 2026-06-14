.globl nova_func
nova_func:
    push %rbp
    mov %rsp, %rbp
    movabs $0, %rdi    # FIX ponteiro → 1º parâmetro
    movabs $0, %rsi    # FIX ponteiro → 2º parâmetro
    movabs $0, %rdx    # FIX ponteiro → 3º parâmetro
    movabs $0, %rax
    call *%rax
    leave
    ret