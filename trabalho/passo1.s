.globl nova_func
nova_func:
    push %rbp
    mov %rsp, %rbp
    movabs $0, %rax        # movabs aceita endereço de 64 bits!
    call *%rax
    leave
    ret