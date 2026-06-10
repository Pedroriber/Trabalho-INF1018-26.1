.globl nova_func
nova_func:
    push %rbp
    mov %rsp, %rbp
    mov $10, %edi        # FIX inteiro no 1º parâmetro
    mov $10, %esi        # FIX inteiro no 2º parâmetro
    mov $10, %edx        # FIX inteiro no 3º parâmetro
    movabs $0, %rax
    call *%rax
    leave
    ret