#include <stdio.h>
#include <stdlib.h>

// Definimos la estructura Alumno
typedef struct {
    char nombre[50];
    char apellido[50];
    float promedio;
    char materia[50];
} Alumno;

int main() {
    // 1. Abrir el archivo en modo escritura ("w")
    FILE *archivo = fopen("C:\\Users\\centr\\Downloads\\alumnos.xml", "w");

    if (archivo == NULL) {
        printf("Error: No se pudo crear el archivo json.\n");
        return 1;
    }

    // 2. Crear una lista (arreglo) con los 10 alumnos
    Alumno listaAlumnos[10] = {
        {"Carlos", "Gomez", 8.5, "Matematicas"},
        {"Ana", "Martinez", 9.2, "Historia"},
        {"Luis", "Rodriguez", 7.0, "Fisica"},
        {"Sofia", "Lopez", 9.8, "Quimica"},
        {"Diego", "Perez", 6.5, "Literatura"},
        {"Maria", "Garcia", 8.9, "Matematicas"},
        {"Juan", "Sanchez", 7.4, "Biologia"},
        {"Laura", "Diaz", 9.5, "Historia"},
        {"Pedro", "Fernandez", 8.2, "Fisica"},
        {"Elena", "Romero", 9.0, "Quimica"}
    };


    fprintf(archivo, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(archivo, "<alumnos>\n");


    for (int i = 0; i < 10; i++) {
        fprintf(archivo, "    <alumno id=\"%d\">\n", i + 1);
        fprintf(archivo, "        <nombre>%s</nombre>\n", listaAlumnos[i].nombre);
        fprintf(archivo, "        <apellido>%s</apellido>\n", listaAlumnos[i].apellido);

        fprintf(archivo, "        <promedio>%.1f</promedio>\n", listaAlumnos[i].promedio);
        fprintf(archivo, "        <materia>%s</materia>\n", listaAlumnos[i].materia);
        fprintf(archivo, "    </alumno>\n");
    }


    fprintf(archivo, "</alumnos>\n");
    fclose(archivo);

    printf("Se ha creado exitosamente el archivo 'alumnos.xml' con 10 registros.\n");
    return 0;
}
