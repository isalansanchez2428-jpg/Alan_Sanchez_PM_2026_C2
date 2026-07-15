#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

// Definición para que las librerías implementen las funciones en este archivo
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define MAX_ARCHIVOS 100
#define MAX_NOMBRE 256

// Función para verificar si la extensión coincide con lo que soportamos
int verificar_extension(const char *nombre_archivo) {
    const char *ext = strrchr(nombre_archivo, '.');
    if (!ext) return 0;

    if (strcasecmp(ext, ".png") == 0 ||
        strcasecmp(ext, ".jpg") == 0 ||
        strcasecmp(ext, ".jpeg") == 0 ||
        strcasecmp(ext, ".bmp") == 0) {
        return 1;
    }
    return 0;
}



// Función para convertir la imagen a Blanco y Negro (Escala de grises)
void convertir_a_blanco_y_negro(const char *entrada, const char *salida) {
    int ancho, alto, canales;

    // Forzamos la carga a 3 canales (RGB) para estandarizar el procesamiento
    unsigned char *pixeles = stbi_load(entrada, &ancho, &alto, &canales, 3);

    if (!pixeles) {
        printf("Error: No se pudo cargar el contenido de la imagen.\n");
        return;
    }

    printf("Procesando imagen de %dx%d pixeles...\n", ancho, alto);

    // El tamaño total del buffer de pixeles es ancho * alto * 3 canales
    size_t tamano_total = ancho * alto * 3;
    for (size_t i = 0; i < tamano_total; i += 3) {
        // Obtenemos los componentes R, G, B
        unsigned char r = pixeles[i];
        unsigned char g = pixeles[i + 1];
        unsigned char b = pixeles[i + 2];

        // Fórmula de luminancia estándar (ponderación del ojo humano)
        unsigned char gris = (unsigned char)(0.299f * r + 0.587f * g + 0.114f * b);

        // Asignamos el mismo valor a los tres canales para hacerla gris
        pixeles[i]     = gris;
        pixeles[i + 1] = gris;
        pixeles[i + 2] = gris;
    }

    // Identificar la extensión de salida para guardarlo en el formato correcto
    const char *ext = strrchr(entrada, '.');
    int resultado = 0;

    if (strcasecmp(ext, ".png") == 0) {
        resultado = stbi_write_png(salida, ancho, alto, 3, pixeles, ancho * 3);
    } else if (strcasecmp(ext, ".jpg") == 0 || strcasecmp(ext, ".jpeg") == 0) {
        resultado = stbi_write_jpg(salida, ancho, alto, 3, pixeles, 90); // 90% calidad
    } else if (strcasecmp(ext, ".bmp") == 0) {
        resultado = stbi_write_bmp(salida, ancho, alto, 3, pixeles);
    }

    if (resultado) {
        printf("¡Éxito! Imagen guardada como: %s\n", salida);
    } else {
        printf("Error al guardar la imagen convertida.\n");
    }

    // Liberar la memoria ocupada por los píxeles
    stbi_image_free(pixeles);
}

int main() {
    DIR *dir;
    struct dirent *entrada_dir;
    char lista_archivos[MAX_ARCHIVOS][MAX_NOMBRE];
    int contador_archivos = 0;
    int seleccion;

    // 1. Abrir la carpeta actual (.)
    dir = opendir(".");
    if (dir == NULL) {
        perror("No se pudo abrir la carpeta actual");
        return 1;
    }

    // 2. Leer archivos y filtrar por extensión preliminar
    while ((entrada_dir = readdir(dir)) != NULL && contador_archivos < MAX_ARCHIVOS) {
        if (verificar_extension(entrada_dir->d_name)) {
            strncpy(lista_archivos[contador_archivos], entrada_dir->d_name, MAX_NOMBRE);
            contador_archivos++;
        }
    }
    closedir(dir);

    // 3. Validar si se encontraron imágenes
    if (contador_archivos == 0) {
        printf("No se encontraron archivos con extensiones .png, .jpg o .bmp en esta carpeta.\n");
        return 0;
    }

    // 4. Mostrar el menú de selección
    printf("=== CONVERTIDOR DE IMÁGENES A BLANCO Y NEGRO ===\n");
    printf("Selecciona el archivo que deseas convertir:\n\n");
    for (int i = 0; i < contador_archivos; i++) {
        printf("[%d] %s\n", i + 1, lista_archivos[i]);
    }
    printf("[0] Salir\n\n");
    printf("Opción: ");

    if (scanf("%d", &seleccion) != 1 || seleccion < 0 || seleccion > contador_archivos) {
        printf("Selección inválida.\n");
        return 1;
    }

    if (seleccion == 0) {
        printf("Programa finalizado.\n");
        return 0;
    }

    // Ajustar el índice para el array (0-indexado)
    char *archivo_elegido = lista_archivos[seleccion - 1];


    // 6. Preparar nombre del archivo de salida
    char archivo_salida[MAX_NOMBRE + 10];
    // Separamos el nombre de la extensión para insertar "_bn"
    char nombre_base[MAX_NOMBRE];
    strncpy(nombre_base, archivo_elegido, MAX_NOMBRE);
    char *punto = strrchr(nombre_base, '.');
    char extension[10];
    strcpy(extension, punto); // Guardamos la extensión
    *punto = '\0';            // Cortamos el nombre base antes del punto

    snprintf(archivo_salida, sizeof(archivo_salida), "%s_bn%s", nombre_base, extension);

    // 7. Ejecutar conversión
    convertir_a_blanco_y_negro(archivo_elegido, archivo_salida);

    return 0;
}
