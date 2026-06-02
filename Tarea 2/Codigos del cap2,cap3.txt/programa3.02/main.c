#include <stdio.h>


/*Suma positivos.
El programa, al recibir como datos N numero enteros, obtiene la suma de los
eternos positivos.

I, N, NUM, SUM: variables de tipo entero. */

void main(void)
{
    int I, N, NUM, SUM;
    SUM = 0;
    printf("ingrese el numero de datos:\t");
    scanf("%d", &N);
    for (I=1; I<=N; I++)
    {
        printf("Ingrese el dato numero %d:\t", I);
        scanf("%d", &NUM);
        if (NUM > 0)
            SUM = SUM + NUM;
    }
    printf("\nLa suma de los numeros positivos es: %d", SUM);
}
