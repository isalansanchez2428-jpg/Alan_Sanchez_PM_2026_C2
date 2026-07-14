#include <stdio.h>
#include <string.h>

typedef struct
{
    char noba[30];
    char nucu[30];
} banco;

typedef union
{
    banco che;
    banco nomi;
    char venta;
} fpago;

typedef struct
{
    char cnu[20];
    char col[20];
    char cp[5];
    char ciu[15];
} domicilio;

typedef struct
{
    int num;
    char nom[20];
    float ven[12];
    domicilio domi;
    float sal;
    fpago pago;
    int cla;
} vendedor;

void lectura(vendedor *, int);
void f1(vendedor *, int);
void f2(vendedor *, int);
void f3(vendedor *, int);
void f4(vendedor *, int);

void main(void)
{
    vendedor vendedores[100];
    int tam;
    do
    {
        printf("Ingrese el numero de vendedores: ");
        scanf("%d", &tam);
    }
    while (tam > 100 || tam < 1);

    lectura(vendedores, tam);
    f1(vendedores, tam);
    f2(vendedores, tam);
    f4(vendedores, tam);
    f4(vendedores, tam);
    printf("\n\tfin del programa");
}

void lectura(vendedor a[], int t)
{
    int i, j;
    for (i=0; i<t; i++)
    {
        printf("\n\tingrese datos del vendedor %d", i+1);
        printf("\nnumero de vendedor: ");
        scanf("%d", &a[i].num);
        getchar();
        printf("nombre de; vendedor: ");
        gets(a[i].nom);
        printf("ventas del año: \n");
        for (j=0; j<12; j++)
        {
            printf("\tmes %d: ", j+1);
            scanf("%f", &a[i].ven[j]);
        }
        getchar();
        printf("domicilio del vendedor: \n");
        printf("\tcalle y numero: ");
        gets(a[i].domi.cnu);
        printf("\tcolonia: ");
        gets(a[i].domi.col);
        printf("\tcodigo postal: ");
        gets(a[i].domi.cp);
        printf("\tciudad: ");
        gets(a[i].domi.ciu);
        printf("salario del vendedor: ");
        scanf("%f", &a[i].sal);
        getchar();
        switch(a[i].cla)
        {
            case 1:{
                printf("\tnombre del banco: ");
                gets(a[i].pago.che.noba);
                printf("\tnumero de cuenta: ");
                gets(a[i].pago.che.nucu);
            }
            break;

            case 2:{
                printf("\tnombre del banco: ");
                gets(a[i].pago.nomi.noba);
                printf("\tnumero de cuenta: ");
                gets(a[i].pago.nomi.nucu);
            }
            break;

            case 3: a[i].pago.venta = 's';
            break;
        }
    }
}

void f1(vendedor a[], int t)
{
    int i, j;
    float sum;
    printf("\n\t\tventas totales de los vendedores");
    for (i=0; i<t; i++)
    {
        printf("\nvendedor: %d", a[i].num);
        sum = 0.0;
        for (j=0; j<12; j++)
            sum += a[i].ven[j];
        printf("\nventas: %.2f\n", sum);
    }
}

void f2(vendedor a[], int t)
{
    int i, j;
    float sum;
    printf("\n\t\tincremento a los vendedores con ventas > 1,500,000$");
    for (i=0; i<t; i++)
    {
        sum = 0.0;
        for (j=0; j<12; j++)
            sum += a[i].ven[j];
        if (sum > 1500000.00)
        {
            a[i].sal = a[i].sal * 1.05;
            printf("\nnumero de empleado: %d\nventas: %.2f\nnuevo salario: %.2f", a[i].num, sum, a[i].sal);
        }
    }
}

void f3(vendedor a[], int t)
{
    int i, j;
        float sum;
        printf("\n\t\tvendedores con ventas <300,000");
        for (i=0; i<t; i++)
        {
            sum = 0.0;
            for (j=0; j<12; j++)
                sum += a[i].ven[j];
            if (sum < 300000.00)
                printf("\nnumero de empleado: %d\nnombre: %s\nventas:  %.2f", a[i].num, a[i].nom, sum);
        }
}

void f4(vendedor a[], int t)
{
    int i;
    float sum;
    printf("\n\t\tvendedores con cuenta en el banco");
    for (i=0; i<t; i++)
        if (a[i].cla == 1)
        printf("\nnumero de vendedor: %d\n banco: %s\ncuenta: %s", a[i].num, a[i].pago.che.noba, a[i].pago.che.nucu);
}
