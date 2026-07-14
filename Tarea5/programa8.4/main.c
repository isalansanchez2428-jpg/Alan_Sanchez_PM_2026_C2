#include <stdio.h>
#include <string.h>

typedef struct
{
    int matricula;
    char nombre[30];
    float cal[5];
} alumno;

void Lectura(alumno a[], int T);
void f1(alumno a[], int tam);
void f2(alumno a[], int tam);
void f3(alumno a[], int tam);

void main(void)
{
    alumno ARRE[50];
    int tam;
    do
    {
        printf("Ingrese el tamaño del arreglo: ");
        scanf("%d", &tam);
    }
    while (tam > 50 || tam < 1);

    Lectura(ARRE, tam);
    f1(ARRE, tam);
    f2(ARRE, tam);
    f3(ARRE, tam);
}

void Lectura(alumno a[], int t)
{
    int i, j;
    for (i=0; i<t; i++)
    {
        printf("\nIngrese los datos del alumno %d", i+1);
         printf("\nIngrese la matricula del alumno: ");
         scanf("%d", &a[i].matricula);
         getchar();
          printf("Ingrese el nombre del alumno: ");
          gets(a[i].nombre);
          for (j=0; j<5; j++)
          {
               printf("\tIngrese la calificacion %d del alumno %d: ", j+1, i+1);
               scanf("%f", &a[i].cal[j]);
          }
    }
}

void f1(alumno a[], int t)
{
    int i, j;
    float sum,pro;
    for (i=0; i<t; i++)
    {
        printf("\nMatricula del alumno: %d", a[i].matricula);
        sum = 0.0;
        for (j=0; j<5; j++)
            sum = sum + a[i].cal[j];
        pro = sum / 5,
        printf("\t\tPromedio: %.2f", pro);
    }
}

void f2(alumno a[], int t)
{
    int i;
    printf("\nAlumnos con calificacion en la tercera materia > 9");
    for (i=0; i<t; i++)
        if (a[i].cal[2] > 9)
        printf("\nMatricula del alumno: %d", a[i].matricula);
}

void f3(alumno a[], int t)
{
    int i;
    float pro, sum = 0.0;
    for (i=0; i<t; i++)
        sum = sum + a[i].cal[3];
    pro = sum / t;
    printf("\n\nPromedio de la materia 4: %.2f", pro);
}
