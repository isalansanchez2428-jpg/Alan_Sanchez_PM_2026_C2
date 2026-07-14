#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char material[20];
    int calificacion;
} matcal;

typedef struct
{
    int matricula;
    char nombre[20];
    matcal cal[5];
} alumno;


void f1(FILE *);
void f2(FILE *);
float f3(FILE *);

void main(void)
{
    float pro;
    FILE *ap;
    if ((ap = fopen("esc.dat", "r")) != NULL)
    {
        f1(ap);
        f2(ap);
        pro = f3(ap);
        printf("\n\nPromedio general materia 4. %f", pro);
    }
    else
        printf("\nEl archivo no se puede abrir");
    fclose(ap);
}
