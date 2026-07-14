#include <stdio.h>
#include <string.h>

typedef struct
{
    char mat[20];
    int pro;
} matpro;

typedef struct
{
    int matri;
    char nom[20];
    matpro cal[5];

} alumno;

void lectura(alumno *, int);
void f1(alumno *, int);
void f2(alumno *, int);
void f3(alumno *, int);

void main(void)
{
    alumno alu[50];
    int tam;
    do
    {
        printf("Ingrese el tamaño del arreglo: ");
        scanf("%d", &tam);
    }
    while (tam > 50 || tam < 1);

    lectura(alu, tam);
    f1(alu, tam);
    f2(alu, tam);
    f3(alu, tam);
}

void lectura(alumno a[], int t)
{
    int i, j;
    for(i=0; i<t; i++)
    {
        printf("\nIngrese los datos del alumno %d", i+1);
        printf("\nIngrese la matricula del alumno: ");
        scanf("%d", &a[i].matri);
        getchar();
        printf("Ingrese el nombre del alumno: ");
        gets(a[i].nom);
        for (j=0; j<5; j++)
        {
            printf("\tmateria %d: ", j+1);
            gets(a[i].cal[j].mat);
            printf("\tpromedio %d: ", j+1);
            scanf("%d", &a[i].cal[j].pro);
            getchar();
        }
    }
}

void f1(alumno a[], int t)
{
    int i, j;
    float sum;
    for (i=0; i<t; i++)
    {
        printf("\nmatricula del alumno: %d", a[i].matri);
        sum = 0.0;
        for (j=0; j<5; j++)
            sum = sum + a[i].cal[j].pro;
            sum = sum / 5;
            printf("\tpromedio: %.2f", sum);
        }
}

void f2(alumno a[], int t)
{
    int i;
    printf("\nalumnos con calificacion mayor a 9 en la tercera materia");
    for (i=0; i<t; i++)
        if (a[i].cal[2].pro > 9)
        printf("\nmatricula del alumno: %d", a[i].matri);
}

void f3(alumno a[], int t)
{
    int i;
    float sum = 0.0;
    for (i=0; i<t; i++)
        sum = sum + a[i].cal[3].pro;
    sum = sum / t;
    printf("\n\nPromedio de la cuarta materia: %.2f", sum);
}
