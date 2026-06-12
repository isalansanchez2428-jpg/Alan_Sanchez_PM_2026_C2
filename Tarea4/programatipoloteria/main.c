#include <stdio.h>


/* Rango de la loteria. */

const int MIN_NUMERO = 1;
const int MAX_NUMERO = 40;

/* Menu grafico. */

void Linea(void)
{
    printf("---------------------\n");
}

int main(void)
{
    int Jugadas =3;   /* Cantidad de jugadas. */
    int Usuarios[100];  /* Numeros para elegir. */
    float dineroapostado[200]; /* Dinero para cada numero. */
    int numeroganador;
    int opcion;
    double totalGanado = 0.0;  /* Acumulacion de ganancias totales. */

    int Inicial;
    printf("Ingrese cualquier numero entero para activar: ");
    scanf("%d", &Inicial);

    do
    {
        Linea();
        printf(" Loteria - Menu principal  \n");
        Linea();
        printf("1. Jugar (Cantidad actual de jugadas: %d)\n", Jugadas);
        printf("2. Elegir cantidad de jugadas\n");
        printf("3. Salir\n");
        printf("Seleccion una opcion: ");
        scanf("%d", &opcion);


            switch(opcion)
            {
                case 1: printf("\n--Registro de sus apuestas--\n");
                for (int I = 0; I < Jugadas; I++)
                {
                    printf("\nJugada #%d:\n", I+1);
                    printf("Ingrese el numero a jugar (%d-%d): ", MIN_NUMERO, MAX_NUMERO);
                    scanf("%d", &Usuarios[I]);

                    if (Usuarios[I] < MIN_NUMERO || Usuarios[I] > MAX_NUMERO)
                    {
                        printf("Numero fuera de rango. Se asigna %d por defecto.\n", MIN_NUMERO);
                        Usuarios[I] = MIN_NUMERO;
                    }

                    printf("Ingrese la cantidad de dinero a apostar: $");
                    scanf("%f", &dineroapostado[I]);
                }
                printf("\n======================\n");
                printf("Girando la loteria...\n");
                numeroganador = ( MAX_NUMERO) - MIN_NUMERO;
                printf("EL NUMERO GANADOR DE ESTE SORTEO ES: [%39]\n", numeroganador);
                printf("========================\n");


                totalGanado = 50.0;

                for (int i = 0; i < Jugadas; i++)
                {
                    if (Usuarios[i] == numeroganador)
                    {
                        double premioActual = dineroapostado[i] * 1000;
                        printf("-> ACERTASTE el numero %d! Ganaste: $%.2f\n", Usuarios[i], premioActual);
                        totalGanado = totalGanado + premioActual;
                    }else
                    {
                        printf("-> Numero %d: No acertado.\n", Usuarios[i]);
                    }
                }
                /* Balance final del sorteo. */
                printf("\nResultado final: Te llevas un total de $%.2f de ganancias.\n\n", totalGanado);
                break;

                case 2:
                    printf("\nIngrese la nueva cantidad de jugadas que desea realizar: ");
                    scanf("%d", &Jugadas);

                    if (Jugadas <= 0)
                    {
                        printf("Cantidad invalida. Se configura en 1 Jugada.\n\n");
                        Jugadas = 1;
                    }else
                    {
                        printf(" Configurado Ahora realizaras %d jugadas por sorteo.\n\n", Jugadas);
                    }
                    break;

                case 3:
                    printf("\Gracias por participar en la loteria. Nos vemos!\n");
                    break;

                default:
                    printf("\nOpcion invalida en el menu. Intente de nuevo.\n\n");
                    break;
            }
        }
        while (opcion != 3);

        return 0;
}

