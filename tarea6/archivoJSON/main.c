#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char nombre[50];
    char apellido[50];
    float promedio;
    char materia[50];
} Alumno;


void crearArchivoJSON(const char *nombreArchivo);
void leerArchivoJSON(const char *nombreArchivo);

int main() {
    const char *archivo = "alumnos.json";

    printf("=== FASE 1: CREANDO Y ESCRIBIENDO EL ARCHIVO JSON ===\n");
    crearArchivoJSON(archivo);

    printf("\n=== FASE 2: ABRIENDO Y LEYENDO EL JSON DE FORMA DINAMICA ===\n");
    leerArchivoJSON(archivo);

    return 0;
}

void crearArchivoJSON(const char *nombreArchivo) {
    FILE *f = fopen(nombreArchivo, "w");
    if (f == NULL) {
        printf("Error critico: No se pudo crear el archivo JSON.\n");
        exit(1);
    }

    Alumno baseDatos[10] = {
        {"Carlos", "Gomez", 8.5, "Matematicas"}, {"Ana", "Martinez", 9.2, "Historia"},
        {"Luis", "Rodriguez", 7.0, "Fisica"},  {"Sofia", "Lopez", 9.8, "Quimica"},
        {"Diego", "Perez", 6.5, "Literatura"},  {"Maria", "Garcia", 8.9, "Matematicas"},
        {"Juan", "Sanchez", 7.4, "Biologia"},   {"Laura", "Diaz", 9.5, "Historia"},
        {"Pedro", "Fernandez", 8.2, "Fisica"},  {"Elena", "Romero", 9.0, "Quimica"}
    };

    fprintf(f, "[\n");
    for (int i = 0; i < 10; i++) {
        fprintf(f, "  {\n");
        fprintf(f, "    \"nombre\": \"%s\",\n", baseDatos[i].nombre);
        fprintf(f, "    \"apellido\": \"%s\",\n", baseDatos[i].apellido);
        fprintf(f, "    \"promedio\": %.1f,\n", baseDatos[i].promedio);
        fprintf(f, "    \"materia\": \"%s\"\n", baseDatos[i].materia);


        if (i < 9) {
            fprintf(f, "  },\n");
        } else {
            fprintf(f, "  }\n");
        }
    }
    fprintf(f, "]\n");

    fclose(f);
    printf("¡Exito! Archivo '%s' guardado en la carpeta del proyecto.\n", nombreArchivo);
}

void leerArchivoJSON(const char *nombreArchivo) {
    char linea[256];
    int n = 0;

    FILE *f = fopen(nombreArchivo, "r");
    if (f == NULL) {
        printf("Error critico: No se pudo abrir el archivo JSON para lectura.\n");
        exit(1);
    }

    while (fgets(linea, sizeof(linea), f) != NULL) {
        if (strstr(linea, "{") != NULL) {
            n++;
        }
    }
    printf("-> Elementos detectados en el JSON: n = %d\n", n);

    if (n == 0) {
        printf("El archivo JSON esta vacio o no es valido.\n");
        fclose(f);
        return;
    }

    Alumno *arrayDinamico = (Alumno *) malloc(n * sizeof(Alumno));
    if (arrayDinamico == NULL) {
        printf("Error: Memoria RAM insuficiente.\n");
        fclose(f);
        exit(1);
    }

    rewind(f);
    int idx = -1;

    while (fgets(linea, sizeof(linea), f) != NULL) {
        if (strstr(linea, "{") != NULL) {
            idx++;
            continue;
        }


        if (strstr(linea, "\"nombre\"") != NULL) {

            sscanf(linea, " %*[^:]: \"%[^\"]\"", arrayDinamico[idx].nombre);
        }
        else if (strstr(linea, "\"apellido\"") != NULL) {
            sscanf(linea, " %*[^:]: \"%[^\"]\"", arrayDinamico[idx].apellido);
        }
        else if (strstr(linea, "\"promedio\"") != NULL) {

            sscanf(linea, " %*[^:]: %f", &arrayDinamico[idx].promedio);
        }
        else if (strstr(linea, "\"materia\"") != NULL) {
            sscanf(linea, " %*[^:]: \"%[^\"]\"", arrayDinamico[idx].materia);
        }
    }
    fclose(f);

    printf("\n--- ALUMNOS CARGADOS EN MEMORIA DINAMICA ---\n");
    for (int i = 0; i < n; i++) {
        printf("[%02d] %s %s | Materia: %s | Promedio: %.1f\n",
               i + 1, arrayDinamico[i].nombre, arrayDinamico[i].apellido,
               arrayDinamico[i].materia, arrayDinamico[i].promedio);
    }

    free(arrayDinamico);
    printf("-> Memoria dinamica del array liberada con exito.\n");
}
