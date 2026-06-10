/* teste.c */
#include <stdio.h>
#include "cria_func.h"

typedef int (*func_ptr)(int x);

int mult(int x, int y) {
    return x * y;
}

int main() {
    DescParam params[2];
    unsigned char codigo[500];

    params[0].tipo_val = INT_PAR;
    params[0].orig_val = PARAM;       /* repassa o argumento */

    params[1].tipo_val = INT_PAR;
    params[1].orig_val = FIX;         /* sempre passa 10 */
    params[1].valor.v_int = 10;

    cria_func(mult, params, 2, codigo);
    func_ptr f_mult = (func_ptr) codigo;

    int i;
    for (i = 1; i <= 10; i++)
        printf("%d\n", f_mult(i));    /* esperado: 10, 20, ..., 100 */

    return 0;
}