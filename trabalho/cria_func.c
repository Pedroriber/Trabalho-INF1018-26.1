#include "cria_func.h"


void cria_func(void *f, DescParam params[], int n, unsigned char codigo[]) {
    int i = 0;

    /* prólogo */
    codigo[i++] = 0x55;              /* push %rbp        */
    codigo[i++] = 0x48;              /* mov %rsp, %rbp   */
    codigo[i++] = 0x89;
    codigo[i++] = 0xe5;

    /* movabs $f, %rax  (endereço de 64 bits) */
    codigo[i++] = 0x48;
    codigo[i++] = 0xb8;
    /* escreve os 8 bytes do endereço de f em little-endian */
    unsigned long addr = (unsigned long)f;
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
    codigo[i++] = 0xc9;              /* leave */
    codigo[i++] = 0xc3;              /* ret   */
}