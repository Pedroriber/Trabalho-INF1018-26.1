/* teste.c */
#include <stdio.h>
#include "cria_func.h"

typedef int (*func_ptr)(int x);

int identidade(int x) {
    return x;
}

int main() {
    DescParam params[1];
    unsigned char codigo[500];

    params[0].tipo_val = INT_PAR;
    params[0].orig_val = PARAM;   /* repassa o argumento direto */

    cria_func(identidade, params, 1, codigo);

    func_ptr f = (func_ptr) codigo;
    printf("Resultado = %d\n", f(42));  /* esperado: 42 */

    return 0;
}