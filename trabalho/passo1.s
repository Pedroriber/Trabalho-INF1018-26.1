# passo1.s
.globl nova_func
nova_func:
    push %rbp
    mov %rsp, %rbp
    mov $0, %rax          # placeholder para endereço de f
    call *%rax
    leave
    ret