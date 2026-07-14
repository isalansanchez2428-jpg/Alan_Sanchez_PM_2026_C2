#include <stdio.h>
#include <string.h>

void intercambia(char fra[][30], int);
void main(void)
{
    int i, n;
    char fra[20][30];
    printf("\nIngrese el numero de filas del arreglo: ");
    scanf("%d", &n);
    getchar();
    for (i=0; i<n; i++)
    {
        printf("Ingrese la linea de texto numero %d: ", i+1);
        fflush(stdin);
        gets(fra[i]);
    }
    printf("\n\n");
    intercambia(fra, n);
    for (i=0; i<n; i++)
    {
        printf("Impresion de la linea de texto %d: ", i+1);
        puts(fra[i]);
    }
}

void intercambia(char fra[][30], int n)
{
    int i, j;
    j = n - 1;
    char cad[30];
    for (i=0; i < (n/2); i++)
    {
        strcpy(cad, fra[i]);
        strcpy(fra[i], fra[j]);
        strcpy(fra[j], cad);
        j--;
    }
}
