.globl nova_func
nova_func:
    # prólogo
    push %rbp
    mov %rsp, %rbp
    and $-16, %rsp

    # salvar PARAMs recebidos (antes de sobrescrever registradores)
    push %rdi
    push %rsi
    push %rdx

    # FIX INT_PAR
    mov $val, %edi        # 1º parâmetro fixo inteiro
    mov $val, %esi        # 2º parâmetro fixo inteiro
    mov $val, %edx        # 3º parâmetro fixo inteiro

    # FIX PTR_PAR
    movabs $ptr, %rdi     # 1º parâmetro fixo ponteiro
    movabs $ptr, %rsi     # 2º parâmetro fixo ponteiro
    movabs $ptr, %rdx     # 3º parâmetro fixo ponteiro

    # IND INT_PAR
    movabs $end_var, %rax
    mov (%rax), %edi      # 1º parâmetro indireto inteiro
    movabs $end_var, %rax
    mov (%rax), %esi      # 2º parâmetro indireto inteiro
    movabs $end_var, %rax
    mov (%rax), %edx      # 3º parâmetro indireto inteiro

    # IND PTR_PAR
    movabs $end_var, %rax
    mov (%rax), %rdi      # 1º parâmetro indireto ponteiro
    movabs $end_var, %rax
    mov (%rax), %rsi      # 2º parâmetro indireto ponteiro
    movabs $end_var, %rax
    mov (%rax), %rdx      # 3º parâmetro indireto ponteiro

    # restaurar PARAMs (ordem inversa por causa do LIFO)
    pop %rdx
    pop %rsi
    pop %rdi

    # chamar f indiretamente
    movabs $f, %rax
    call *%rax

    # epílogo
    leave
    ret