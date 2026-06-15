.globl nova_func
nova_func:
    push %rbp
    mov %rsp, %rbp
    subq $16, %rsp
    push %rdi
    push %rsi
    push %rdx
    pop %rdi     # recupera para 1º parâmetro
    pop %rsi     # recupera para 2º parâmetro
    pop %rdx     # recupera para 3º parâmetro
    movabs $0, %rax
    call *%rax
    leave
    ret