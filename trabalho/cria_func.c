/*Pedro Ribeiro Fernande do Rosário  2510753  3WA*/
/*
0000000000000000 <nova_func>:
   0:   55                      push   %rbp
   1:   48 89 e5                mov    %rsp,%rbp
   4:   48 83 e4 f0             and    $0xfffffffffffffff0,%rsp
   8:   57                      push   %rdi
   9:   56                      push   %rsi
   a:   52                      push   %rdx
   b:   bf 00 00 00 00          mov    $0x0,%edi
  10:   be 00 00 00 00          mov    $0x0,%esi
  15:   ba 00 00 00 00          mov    $0x0,%edx
  1a:   48 bf 00 00 00 00 00    movabs $0x0,%rdi
  21:   00 00 00 
  24:   48 be 00 00 00 00 00    movabs $0x0,%rsi
  2b:   00 00 00 
  2e:   48 ba 00 00 00 00 00    movabs $0x0,%rdx
  35:   00 00 00 
  38:   48 b8 00 00 00 00 00    movabs $0x0,%rax
  3f:   00 00 00 
  42:   8b 38                   mov    (%rax),%edi
  44:   48 b8 00 00 00 00 00    movabs $0x0,%rax
  4b:   00 00 00 
  4e:   8b 30                   mov    (%rax),%esi
  50:   48 b8 00 00 00 00 00    movabs $0x0,%rax
  57:   00 00 00 
  5a:   8b 10                   mov    (%rax),%edx
  5c:   48 b8 00 00 00 00 00    movabs $0x0,%rax
  63:   00 00 00 
  66:   48 8b 38                mov    (%rax),%rdi
  69:   48 b8 00 00 00 00 00    movabs $0x0,%rax
  70:   00 00 00 
  73:   48 8b 30                mov    (%rax),%rsi
  76:   48 b8 00 00 00 00 00    movabs $0x0,%rax
  7d:   00 00 00 
  80:   48 8b 10                mov    (%rax),%rdx
  83:   5a                      pop    %rdx
  84:   5e                      pop    %rsi
  85:   5f                      pop    %rdi
  86:   48 b8 00 00 00 00 00    movabs $0x0,%rax
  8d:   00 00 00 
  90:   ff d0                   call   *%rax
  92:   c9                      leave
  93:   c3                      ret
*/
#include "cria_func.h"

static unsigned char push_param[] = {0x57, 0x56, 0x52}; /* pushq %rdi/rsi/rdx */
static unsigned char pop_param[]  = {0x5f, 0x5e, 0x5a}; /* pop  %rdi/rsi/rdx */
static unsigned char mov_fix_int[] = {0xbf, 0xbe, 0xba}; /* movl $val, %edi/esi/edx */
static unsigned char mov_fix_ptr[] = {0xbf, 0xbe, 0xba}; /* movabs $ptr, %rdi/rsi/rdx */
static unsigned char mov_ind_int[] = {0x38, 0x30, 0x10}; /* movl (%rax), %edi/esi/edx */
static unsigned char mov_ind_ptr[] = {0x38, 0x30, 0x10}; /* movq (%rax), %rdi/rsi/rdx */

static void escreve_endereco(unsigned char *codigo, int *i, void *addr) { /* escreve endereço da funçaõ */
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
    int param_count = 0; /* quantos PARAM existem */

    /* prólogo */
    codigo[i++] = 0x55;
    codigo[i++] = 0x48;
    codigo[i++] = 0x89;
    codigo[i++] = 0xe5;
    codigo[i++] = 0x48;
    codigo[i++] = 0x83;
    codigo[i++] = 0xec;
    codigo[i++] = 0x10;

    /* salva os PARAM na pilha na ordem que chegaram (rdi, rsi, rdx) */
    for (p = 0; p < n; p++) {
        if (params[p].orig_val == PARAM) {
            codigo[i++] = push_param[param_count];
            param_count++;
        }
    }

    /* agora popula os registradores na ordem correta */
    int param_idx = param_count - 1; /* índice do último PARAM empilhado */

    for (p = n - 1; p >= 0; p--) {
        if (params[p].orig_val == PARAM) {
            codigo[i++] = pop_param[p];
            param_idx--;
        } else if (params[p].orig_val == FIX) {
            if (params[p].tipo_val == INT_PAR) {
                int val = params[p].valor.v_int;
                codigo[i++] = mov_fix_int[p];
                codigo[i++] = (val      ) & 0xff;
                codigo[i++] = (val >>  8) & 0xff;
                codigo[i++] = (val >> 16) & 0xff;
                codigo[i++] = (val >> 24) & 0xff;
            } else {
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
            escreve_endereco(codigo, &i, params[p].valor.v_ptr);
            if (params[p].tipo_val == INT_PAR) {
                codigo[i++] = 0x8b;
                codigo[i++] = mov_ind_int[p];
            } else {
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