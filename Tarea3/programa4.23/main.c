#include <stdio.h>



void trueque(int *x, int *y);
int Suma(int x);

int main(void)
{
    int a = 5, b =10;
    trueque(&a, &b);
    Suma(a);

    return 0;
}

void trueque(int *x, int *y)
{
    int tem;
    tem = *x;
    *x = *y;
    *y = tem;
}
int Suma(int x)
{
    return (x + x);
}

