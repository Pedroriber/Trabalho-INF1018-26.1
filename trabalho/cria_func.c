#include "cria_func.h"

/* mov $val, %edi/esi/edx (INT_PAR FIX) */
static unsigned char mov_fix_int[] = {0xbf, 0xbe, 0xba};

/* segundo byte de movabs $ptr, %rdi/rsi/rdx (PTR_PAR FIX) */
static unsigned char mov_fix_ptr[] = {0xbf, 0xbe, 0xba};

/* segundo e terceiro bytes de mov (%rax), %reg */
static unsigned char mov_ind_int[] = {0x38, 0x30, 0x10};  /* 8b XX       */
static unsigned char mov_ind_ptr[] = {0x38, 0x30, 0x10};  /* 48 8b XX    */

static void escreve_endereco(unsigned char *codigo, int *i, void *addr) {
    unsigned long a = (unsigned long)addr;
    codigo[(*i)++] = 0x48;
    codigo[(*i)++] = 0xb8;
    codigo[(*i)++] = (a      ) & 0xff;
    codigo[(*i)++] = (a >>  8) & 0xff;
    codigo[(*i)++] = (a >> 16) & 0xff;
    codigo[(*i)++] = (a >> 24) & 0xff;
    codigo[(*i)++] = (a >> 32) & 0xff;
    codigo[(*i)++] = (a >> 40) & 0xff;
    codigo[(*i)++] = (a >> 48) & 0xff;
    codigo[(*i)++] = (a >> 56) & 0xff;
}

void cria_func(void *f, DescParam params[], int n, unsigned char codigo[]) {
    int i = 0;
    int p;

    /* prólogo */
    codigo[i++] = 0x55;
    codigo[i++] = 0x48;
    codigo[i++] = 0x89;
    codigo[i++] = 0xe5;

    for (p = 0; p < n; p++) {
        if (params[p].orig_val == PARAM) {
            /* não gera nada */

        } else if (params[p].orig_val == FIX) {
            if (params[p].tipo_val == INT_PAR) {
                /* mov $val, %edi/esi/edx */
                int val = params[p].valor.v_int;
                codigo[i++] = mov_fix_int[p];
                codigo[i++] = (val      ) & 0xff;
                codigo[i++] = (val >>  8) & 0xff;
                codigo[i++] = (val >> 16) & 0xff;
                codigo[i++] = (val >> 24) & 0xff;
            } else {
                /* PTR_PAR: movabs $ptr, %rdi/rsi/rdx */
                unsigned long val = (unsigned long)params[p].valor.v_ptr;
                codigo[i++] = 0x48;
                codigo[i++] = mov_fix_ptr[p];
                codigo[i++] = (val      ) & 0xff;
                codigo[i++] = (val >>  8) & 0xff;
                codigo[i++] = (val >> 16) & 0xff;
                codigo[i++] = (val >> 24) & 0xff;
                codigo[i++] = (val >> 32) & 0xff;
                codigo[i++] = (val >> 40) & 0xff;
                codigo[i++] = (val >> 48) & 0xff;
                codigo[i++] = (val >> 56) & 0xff;
            }

        } else if (params[p].orig_val == IND) {
            /* movabs $endereço_var, %rax */
            escreve_endereco(codigo, &i, params[p].valor.v_ptr);
            if (params[p].tipo_val == INT_PAR) {
                /* mov (%rax), %edi/esi/edx */
                codigo[i++] = 0x8b;
                codigo[i++] = mov_ind_int[p];
            } else {
                /* mov (%rax), %rdi/rsi/rdx */
                codigo[i++] = 0x48;
                codigo[i++] = 0x8b;
                codigo[i++] = mov_ind_ptr[p];
            }
        }
    }

    /* movabs $f, %rax */
    escreve_endereco(codigo, &i, f);

    /* call *%rax */
    codigo[i++] = 0xff;
    codigo[i++] = 0xd0;

    /* epílogo */
    codigo[i++] = 0xc9;
    codigo[i++] = 0xc3;
}