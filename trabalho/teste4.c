#include <stdio.h>
#include <string.h>
#include "cria_func.h"

typedef int (*func_ptr)(void *candidata, size_t n);

char fixa[] = "quero saber se a outra string é um prefixo dessa";

int main() {
    DescParam params[3];
    unsigned char codigo[500];

    params[0].tipo_val = PTR_PAR;
    params[0].orig_val = FIX;
    params[0].valor.v_ptr = fixa;

    params[1].tipo_val = PTR_PAR;
    params[1].orig_val = PARAM;

    params[2].tipo_val = INT_PAR;
    params[2].orig_val = PARAM;

    cria_func(memcmp, params, 3, codigo);
    func_ptr mesmo_prefixo = (func_ptr) codigo;

    char s[] = "quero saber tudo";
    int tam;

    tam = 12;
    printf("'%s' tem mesmo prefixo-%d de '%s'? %s\n", s, tam, fixa, mesmo_prefixo(s, tam) ? "NAO" : "SIM");
    tam = strlen(s);
    printf("'%s' tem mesmo prefixo-%d de '%s'? %s\n", s, tam, fixa, mesmo_prefixo(s, tam) ? "NAO" : "SIM");

    return 0;
}