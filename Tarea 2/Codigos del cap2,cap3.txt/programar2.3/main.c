#include <stdio.h>
#include <stdlib.h>

/* promedio de curso.
 El programa, al recibir como el dato el promedio de un alumno en un curso
universitario, escribe aprobado si su promedio es mayor o igual a 6 o
reprobado en ese caso.

PRO: variable en tiempo real. */

void main(void)
{
float PRO;
printf("ingrese promedio del alumno: ");
scanf("%f:", &PRO);
if (PRO >= 6.0)
printf("\nAprobado");
else
printf("\nReprobado");
}
