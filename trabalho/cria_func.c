#include "cria_func.h"

/* opcodes para mov $constante, %reg (INT_PAR) */
static unsigned char mov_fix_int[] = {0xbf, 0xbe, 0xba};

void cria_func(void *f, DescParam params[], int n, unsigned char codigo[]) {
    int i = 0;
    int p;

    /* prólogo */
    codigo[i++] = 0x55;        /* push %rbp      */
    codigo[i++] = 0x48;        /* mov %rsp, %rbp */
    codigo[i++] = 0x89;
    codigo[i++] = 0xe5;

    /* gera código para cada parâmetro */
    for (p = 0; p < n; p++) {
        if (params[p].orig_val == FIX && params[p].tipo_val == INT_PAR) {
            int val = params[p].valor.v_int;
            codigo[i++] = mov_fix_int[p];   /* mov $val, %reg */
            codigo[i++] = (val      ) & 0xff;
            codigo[i++] = (val >>  8) & 0xff;
            codigo[i++] = (val >> 16) & 0xff;
            codigo[i++] = (val >> 24) & 0xff;
        }
        /* PARAM: registrador já tem o valor certo, não gera nada */
    }

    /* movabs $f, %rax */
    unsigned long addr = (unsigned long)f;
    codigo[i++] = 0x48;
    codigo[i++] = 0xb8;
    codigo[i++] = (addr      ) & 0xff;
    codigo[i++] = (addr >>  8) & 0xff;
    codigo[i++] = (addr >> 16) & 0xff;
    codigo[i++] = (addr >> 24) & 0xff;
    codigo[i++] = (addr >> 32) & 0xff;
    codigo[i++] = (addr >> 40) & 0xff;
    codigo[i++] = (addr >> 48) & 0xff;
    codigo[i++] = (addr >> 56) & 0xff;

    /* call *%rax */
    codigo[i++] = 0xff;
    codigo[i++] = 0xd0;

    /* epílogo */
    codigo[i++] = 0xc9;        /* leave */
    codigo[i++] = 0xc3;        /* ret   */
}