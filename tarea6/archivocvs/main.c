#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nombre[50];
    char apellido[50];
    float promedio;
    char materia[50];
} Alumno;

int main() {
    const char *nombreArchivo = "alumnos.csv";
    char linea[256];
    int n = 0;

    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo '%s'. Asegurate de haberlo creado.\n", nombreArchivo);
        return 1;
    }

    while (fgets(linea, sizeof(linea), archivo) != NULL)
        {
        if (strlen(linea) > 1)
        {
            n++;
        }
    }

    printf("-> Se detectaron %d registros en el archivo CSV.\n", n);

    if (n == 0) {
        printf("El archivo CSV esta vacio.\n");
        fclose(archivo);
        return 0;
    }

    Alumno *listaAlumnos = (Alumno *) malloc(n * sizeof(Alumno));
    if (listaAlumnos == NULL) {
        printf("Error: Memoria RAM insuficiente.\n");
        fclose(archivo);
        return 1;
    }

    rewind(archivo);

    int i = 0;
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        if (strlen(linea) <= 1) continue;

        linea[strcspn(linea, "\n")] = '\0';


        int procesados = sscanf(linea, "%[^,],%[^,],%f,%[^,\n]",
                                listaAlumnos[i].nombre,
                                listaAlumnos[i].apellido,
                                &listaAlumnos[i].promedio,
                                listaAlumnos[i].materia);

        if (procesados == 4) {
            i++;
        }
    }

    fclose(archivo);

    printf("\n=== REGISTROS CARGADOS EN MEMORIA DINAMICA ===\n");
    for (int j = 0; j < n; j++) {
        printf("[%02d] Alumno: %s %s\n", j + 1, listaAlumnos[j].nombre, listaAlumnos[j].apellido);
        printf("     Materia: %s | Promedio: %.1f\n", listaAlumnos[j].materia, listaAlumnos[j].promedio);
        printf("---------------------------------------------\n");
    }


    free(listaAlumnos);
    printf("Memoria dinamica liberada con exito.\n");

    return 0;
}
