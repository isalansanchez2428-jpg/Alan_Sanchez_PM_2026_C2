#include <stdio.h>
#include <string.h>

typedef struct
{
    int clave;
    char nombre[15];
    float precio;
    int existencia;
} producto;

void lectura(producto *, int);
void ventas(producto *, int);
void reabastecimiento(producto *, int);
void nuevosproductos(producto *, int *);
void inventario(producto *, int);

void main(void)
{
    producto inv[100];
    int tam, ope;
    do
    {
        printf("Ingrese el numero de productos: ");
        scanf("%d", &tam);
    }
    while (tam > 100 || tam < 1);
    lectura(inv, tam);
    printf("\nIngrese operacion a realizar. \n\t\t1 - ventas n\t\t 2 - reabastecimiento n\t\t 3- nuevos productos \n\t\t 4- inventario \n\n\t  0- salir: ");
    scanf("%d", &ope);
    while (ope)
    {
        switch(ope)
        {
            case 1: ventas(inv, tam);
            break;
            case 2: reabastecimiento(inv, tam);
            break;
            case 3: nuevosproductos(inv, &tam);
            break;
            case 4: inventario(inv, tam);
            break;
        };
        printf("\nIngrese operacion a realizar. \n\t\t 1- ventas \n\t\t 2- reabastecimiento \n\t\t 3- nuevos productos \n\t\t 4- inventario \n\t\t 0- salir: ");
        scanf("%d", &ope);
    }
}
void lectura(producto a[], int t)
{
    int i;
    for (i=0; i<t; i++)
    {
        printf("\nIngrese informacion del producto %d", i+1);
        printf("\n\tclave: ");
        scanf("%d", &a[i].clave);
        getchar();
        printf("\tnombre: ");
        gets(a[i].nombre);
        printf("\ntprecio: ");
        scanf("%f", &a[i].precio);
        printf("\texistencia: ");
        scanf("%d", &a[i]. existencia);
    }
}

void ventas(producto a[], int t)
{
    int cla, can, i, res;
    float tot, par;
    printf("\nIngrese clave del producto -0 para salir-: ");
    scanf("%d", &cla);
    tot = 0.0;
    while (cla)
    {
        printf("\tcantidad: ");
        scanf("%d", &can);
        i = 0;
        while ((i < t) && (a[i].clave < cla))
            i++;
        if ((i == t) || (a[i].clave > cla))
            printf("\nLa clave del producto es incorrecta");
        else
            if (a[i].existencia >= can)
        {
            a[i].existencia -= can;
            par = a[i].precio *can;
            tot += par;
        }
        else
        {
            printf("\nno existe en inventario la cantidad solicitada. solo hay %d", a[i].existencia);
            printf("\nlos lleva 1 - si 0 - no?: ");
            scanf("%d", &res);
            if (res)
            {
                par = a[i].precio *a[i].existencia;
                a[i].existencia = 0;
                tot += par;
            }
        }
        printf("\nIngrese la siguiente clave del producto -0 para salir-:");
        scanf("%d", &cla);
    }
    printf("\ntotal de la venta: %f", tot);
}

void reabastecimiento(producto a[], int t)
{
    int cla, can, i;
    printf("\nIngrese clave del producto -0 para salir-: ");
    scanf("%d", &cla);
    while (cla)
    {
        i = 0;
        while ((i < t) && (a[i].clave < cla))
            i++;
        if ((i==t) || (a[i].clave > cla))
            printf("\nla clave del producto ingresada es incorrecta");
        else
        {
            printf("\tcantidad: ");
            scanf("%d", &can);
            a[i].existencia += can;
        }
        printf("\nIngrese otra clave del producto -0 para salir-: ");
        scanf("%d", &cla);
    }
}

void nuevosproductos(producto a[], int *t)
{
    int cla, i, j;
    printf("\nIngrese clave del producto -0 para salir-: ");
    scanf("%d", &cla);
    while ((*t < 30) && (cla))
    {
        i=0;
        while ((i < *t) && (a[i].clave <cla))
            i++;
        if (i == *t)
        {
            a[i].clave = cla;
            printf("\tnombre:"),
            getchar();
            gets(a[i].nombre);
            printf("\tprecio:");
            scanf("%f", &a[i].precio);
            printf("\tcantidad: ");
            scanf("%d", &a[i].existencia);
            *t = *t + 1;
        }
        else
            if(a[i].clave == cla)
            printf("\nel producto ya se encuentra en el inventario");
        else
        {
            for (j=*t; j>i; j--)
                a[j] = a[j-1];
            a[i].clave = cla;
            printf("\tnombre:");
            getchar();
            gets(a[i].nombre);
            printf("\tprecio:");
            scanf("%f", &a[i].precio);
            printf("\tcantidad: ");
            scanf("%d", &a[i].existencia);
            *t = *t + 1;
        }
        printf("\nIngrese otra clave de producto -0 para salir-: ");
        scanf("%d", &cla);
    }
    if (*t == 30)
        printf("\nya nno hay espacio para incorporar nuevos productos");
}

void inventario(producto a[], int t)
{
    int i;
    for (i=0; i<t; i++)
    {
        printf("\nclave: %d", a[i].clave);
         printf("\tnombre: %s", a[i].nombre);
          printf("\tprecio: %.2f", a[i].precio);
           printf("\texiste: %d \n", a[i].existencia);

    }
}
