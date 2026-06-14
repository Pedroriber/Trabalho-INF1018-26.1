.globl nova_func
nova_func:
    push %rbp
    mov %rsp, %rbp
    movabs $0, %rax        # endereço da variável
    mov (%rax), %edi       # lê o valor no endereço → 1º parâmetro
    movabs $0, %rax        # endereço da variável
    mov (%rax), %esi       # lê o valor no endereço → 2º parâmetro
    movabs $0, %rax        # endereço da variável
    mov (%rax), %edx       # lê o valor no endereço → 3º parâmetro
    movabs $0, %rax
    call *%rax
    leave
    ret