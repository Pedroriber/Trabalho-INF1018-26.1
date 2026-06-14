.globl nova_func
nova_func:
    push %rbp
    mov %rsp, %rbp
    movabs $0, %rax
    mov (%rax), %rdi    # IND ponteiro → 1º parâmetro
    movabs $0, %rax
    mov (%rax), %rsi    # IND ponteiro → 2º parâmetro
    movabs $0, %rax
    mov (%rax), %rdx    # IND ponteiro → 3º parâmetro
    movabs $0, %rax
    call *%rax
    leave
    ret