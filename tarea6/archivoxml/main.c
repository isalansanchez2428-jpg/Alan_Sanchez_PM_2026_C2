#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición de la estructura
typedef struct {
    char nombre[50];
    char apellido[50];
    float promedio;
    char materia[50];
} Alumno;

// Prototipos de funciones para mantener el código organizado
void crearArchivoXML(const char *nombreArchivo);
void leerArchivoXML(const char *nombreArchivo);

int main() {
    const char *archivo = "alumnos.xml";

    printf("=== FASE 1: CREANDO Y ESCRIBIENDO EL ARCHIVO XML ===\n");
    crearArchivoXML(archivo);

    printf("\n=== FASE 2: ABRIENDO Y LEYENDO EL XML DE FORMA DINAMICA ===\n");
    leerArchivoXML(archivo);

    return 0;
}

// Función encargada de crear el archivo físico XML con 10 elementos
void crearArchivoXML(const char *nombreArchivo) {
    FILE *f = fopen(nombreArchivo, "w");
    if (f == NULL) {
        printf("Error crítico: No se pudo crear el archivo para escritura.\n");
        exit(1);
    }

    // Datos duros iniciales para la prueba
    Alumno baseDatos[10] = {
        {"Carlos", "Gomez", 8.5, "Matematicas"}, {"Ana", "Martinez", 9.2, "Historia"},
        {"Luis", "Rodriguez", 7.0, "Fisica"},  {"Sofia", "Lopez", 9.8, "Quimica"},
        {"Diego", "Perez", 6.5, "Literatura"},  {"Maria", "Garcia", 8.9, "Matematicas"},
        {"Juan", "Sanchez", 7.4, "Biologia"},   {"Laura", "Diaz", 9.5, "Historia"},
        {"Pedro", "Fernandez", 8.2, "Fisica"},  {"Elena", "Romero", 9.0, "Quimica"}
    };

    // Escritura de estructura XML estándar
    fprintf(f, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(f, "<alumnos>\n");
    for (int i = 0; i < 10; i++) {
        fprintf(f, "    <alumno>\n");
        fprintf(f, "        <nombre>%s</nombre>\n", baseDatos[i].nombre);
        fprintf(f, "        <apellido>%s</apellido>\n", baseDatos[i].apellido);
        fprintf(f, "        <promedio>%.1f</promedio>\n", baseDatos[i].promedio);
        fprintf(f, "        <materia>%s</materia>\n", baseDatos[i].materia);
        fprintf(f, "    </alumno>\n");
    }
    fprintf(f, "</alumnos>\n");
    fclose(f);
    printf("¡Éxito! Archivo '%s' guardado en la carpeta del proyecto.\n", nombreArchivo);
}

// Función encargada de abrir, calcular 'n', reservar memoria y parsear
void leerArchivoXML(const char *nombreArchivo) {
    char linea[256];
    int n = 0;

    FILE *f = fopen(nombreArchivo, "r");
    if (f == NULL) {
        printf("Error crítico: No se pudo abrir el archivo para lectura.\n");
        exit(1);
    }

    // 1. PASADA DE CONTEO: Contamos cuántas etiquetas <alumno> existen
    while (fgets(linea, sizeof(linea), f) != NULL) {
        if (strstr(linea, "<alumno>") != NULL) {
            n++;
        }
    }
    printf("-> Elementos detectados en el XML: n = %d\n", n);

    if (n == 0) {
        printf("El archivo XML está vacío o no es válido.\n");
        fclose(f);
        return;
    }

    // 2. ASIGNACIÓN DINÁMICA: Reservamos la RAM exacta basándonos en 'n'
    Alumno *arrayDinamico = (Alumno *) malloc(n * sizeof(Alumno));
    if (arrayDinamico == NULL) {
        printf("Error: Memoria insuficiente en el sistema.\n");
        fclose(f);
        exit(1);
    }

    // 3. SEGUNDA PASADA: Reposicionar el puntero del archivo al inicio para extraer datos
    rewind(f);
    int idx = -1;

    while (fgets(linea, sizeof(linea), f) != NULL) {
        if (strstr(linea, "<alumno>") != NULL) {
            idx++; // Cambiamos de Alumno al encontrar la etiqueta de apertura
            continue;
        }

        // Expresión de formato: ignora caracteres hasta el '>' y extrae el texto antes del '<'
        if (strstr(linea, "<nombre>") != NULL) {
            sscanf(linea, " %*[^>]><nombre>%[^<]</nombre>", arrayDinamico[idx].nombre);
        } else if (strstr(linea, "<apellido>") != NULL) {
            sscanf(linea, " %*[^>]><apellido>%[^<]</apellido>", arrayDinamico[idx].apellido);
        } else if (strstr(linea, "<promedio>") != NULL) {
            sscanf(linea, " %*[^>]><promedio>%f</promedio>", &arrayDinamico[idx].promedio);
        } else if (strstr(linea, "<materia>") != NULL) {
            sscanf(linea, " %*[^>]><materia>%[^<]</materia>", arrayDinamico[idx].materia);
        }
    }
    fclose(f); // Cerramos el archivo de forma segura

    // 4. IMPRESIÓN: Demostración de que los datos viven en el array de la RAM
    for (int i = 0; i < n; i++) {
        printf("[%02d] %s %s | Materia: %s | Promedio: %.1f\n",
               i + 1, arrayDinamico[i].nombre, arrayDinamico[i].apellido,
               arrayDinamico[i].materia, arrayDinamico[i].promedio);
    }

    // 5. LIBERACIÓN DE MEMORIA: Buenas prácticas obligatorias en C
    free(arrayDinamico);
    printf("-> Memoria dinámica del array liberada con éxito.\n");
}
