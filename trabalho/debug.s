.globl nova_func
nova_func:
    push %rbp
    mov %rsp, %rbp
    and $-16, %rsp
    movabs $0, %rax
    call *%rax
    leave
    ret