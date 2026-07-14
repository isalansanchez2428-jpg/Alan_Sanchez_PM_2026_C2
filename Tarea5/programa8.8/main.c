#include <stdio.h>
#include <string.h>

typedef struct
{
    char cal[20];  /* calle. */
    int num;  /* numero. */
    char col[20];  /* colonia. */
    char cp[5];   /* codigo postal. */
    char ciu[20];     /* Ciudad. */
} domicilio;

typedef struct
{
    char nom[20];
    int edad;
    char sexo;
    int con;
    domicilio dom;

    char tel[10];
} paciente;


void lectura(paciente *, int);
void f1(paciente *, int);
void f2(paciente *, int);
void f3(paciente *, int);

void main(void)
{
    paciente hospital[100];
    int tam;
    do
    {
        printf("Ingrese el numero de pacientes: ");
        scanf("%d", &tam);
    }
    while (tam > 50 || tam < 1);

    lectura(hospital, tam);
    f1(hospital, tam);
    f2(hospital, tam);
    f3(hospital, tam);
}

void lectura(paciente a[], int t)
{
    int i;
    for (i=0; i<t; i++)
    {
        printf("\n\t\tpaciente %d", i+1);
        getchar();
        printf("\nnombre: ");
        gets(a[i].nom);
        printf("edad: ");
        scanf("%d", &a[i].sexo);
        getchar();
        printf("sexo (f-m): ");
        scanf("%c", &a[i].sexo);
        printf("condicion (1..5): ");
        scanf("%d", &a[i].con);
        getchar();
        printf("\tcalle: ");
        gets(a[i].dom.cal);
        printf("\tnumero: ");
        scanf("%d", &a[i].dom.num);
        getchar();
        printf("\tcolonia: ");
        gets(a[i].dom.col);
        printf("\tcodigo postal: ");
        gets(a[i].dom.cp);
        printf("\tciudad: ");
        gets(a[i].dom.ciu);
        printf("telefono: ");
        gets(a[i].tel);
    }
}

void f1(paciente a[], int t)
{
    int i, fem = 0, mas = 0, tot;
    for (i=0; i<t; i++)
        switch(a[i].sexo)
    {
        case 'f': fem++;
        break;
        case 'm': mas++;
        break;
    }
    tot = fem + mas;
    printf("\nporcentaje de hombres: %.2f", (float)mas / tot * 100);
    printf("\nporcentaje de mujeres: %.2f", (float)fem / tot * 100);
}

void f2(paciente a[], int t)
        {
            int i, c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0;
            for (i=0; i<t; i++)
            switch(a[i].con)
            {
                case 1: c1++;
                break;
                case 2: c2++;
                break;
                case 3: c3++;
                break;
                case 4: c4++;
                break;
                case 5: c5++;
                break;
            }
            printf("\nnumero pacientes en condicion 1: %d", c1);
            printf("\nnumero pacientes en condicion 2: %d", c2);
            printf("\nnumero pacientes en condicion 3: %d", c3);
            printf("\nnumero pacientes en condicion 4: %d", c4);
            printf("\nnumero pacientes en condicion 5: %d", c5);
        }

        void f3(paciente a[], int t)
        {
            int i;
            printf("\npacientes ingresador en estado de gravedad");
            for (i=0; i<t; i++)
                if (a[i].con == 5)
                printf("\nnombre: %s\telefono: %s", a[i].nom, a[i].tel);
        }

