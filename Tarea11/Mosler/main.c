#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h" // Librería externa para manejo de JSON

#define MAX_STR 128

// Estructura para almacenar los datos del Método Mosler
typedef struct {
    char nombre[MAX_STR];
    int F; // Función
    int S; // Sustitución
    int P; // Perturbación
    int E; // Extensión
    int A; // Agresión
    int V; // Vulnerabilidad

    // Calculados
    int I;  // Importancia del Perjuicio (F * S)
    int D;  // Daños Ocasionados (P * E)
    int C;  // Carácter del Riesgo (I + D)
    int PB; // Probabilidad (A * V)
    int ER; // Evaluación del Riesgo (C * PB)
} Riesgo;

// Nodo de lista enlazada dinámica
typedef struct Nodo {
    Riesgo dato;
    struct Nodo* siguiente;
} Nodo;

// --- FUNCIONES DEL MÉTODO MOSLER ---

void calcularParametros(Riesgo* r) {
    r->I = r->F * r->S;
    r->D = r->P * r->E;
    r->C = r->I + r->D;
    r->PB = r->A * r->V;
    r->ER = r->C * r->PB;
}

const char* obtenerClasificacion(int er) {
    if (er <= 250) return "Muy Bajo";
    if (er <= 500) return "Bajo";
    if (er <= 750) return "Medio";
    if (er <= 1000) return "Elevado";
    return "Muy Elevado";
}

// --- GESTIÓN DE MEMORIA DINÁMICA ---

void agregarRiesgoDinamico(Nodo** cabeza, Riesgo r) {
    calcularParametros(&r);
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (!nuevo) {
        printf("[!] Error: No se pudo asignar memoria dinamica.\n");
        return;
    }
    nuevo->dato = r;
    nuevo->siguiente = *cabeza;
    *cabeza = nuevo;
    printf("[+] Riesgo '%s' agregado a la memoria dinamica.\n", r.nombre);
}

void liberarMemoria(Nodo** cabeza) {
    Nodo* actual = *cabeza;
    Nodo* siguiente = NULL;
    while (actual != NULL) {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
    *cabeza = NULL;
}

// --- IMPRESIÓN Y EDICIÓN ---

void imprimirRiesgos(Nodo* cabeza) {
    if (!cabeza) {
        printf("\n[!] No hay riesgos cargados en memoria.\n");
        return;
    }

    printf("\n=================================== EVALUACION METODO MOSLER ===================================\n");
    printf("%-32s | F S P E A V |  I   D   C  PB |   ER   | Clasificacion\n", "Riesgo");
    printf("------------------------------------------------------------------------------------------------\n");

    Nodo* aux = cabeza;
    while (aux != NULL) {
        Riesgo r = aux->dato;
        printf("%-32s | %d %d %d %d %d %d | %2d %2d %3d %3d | %6d | %s\n",
               r.nombre, r.F, r.S, r.P, r.E, r.A, r.V,
               r.I, r.D, r.C, r.PB, r.ER, obtenerClasificacion(r.ER));
        aux = aux->siguiente;
    }
    printf("================================================================================================\n");
}

void modificarRiesgo(Nodo* cabeza) {
    if (!cabeza) {
        printf("\n[!] No hay riesgos para modificar.\n");
        return;
    }

    char nombre[MAX_STR];
    getchar();
    printf("\nIngrese el nombre del riesgo a modificar: ");
    fgets(nombre, MAX_STR, stdin);
    nombre[strcspn(nombre, "\n")] = 0;

    Nodo* aux = cabeza;
    while (aux != NULL) {
        if (strcasecmp(aux->dato.nombre, nombre) == 0) {
            printf("\n--- Modificando valores (1-5) para: %s ---\n", aux->dato.nombre);
            printf("F (Funcion): "); scanf("%d", &aux->dato.F);
            printf("S (Sustitucion): "); scanf("%d", &aux->dato.S);
            printf("P (Perturbacion): "); scanf("%d", &aux->dato.P);
            printf("E (Extension): "); scanf("%d", &aux->dato.E);
            printf("A (Agresion): "); scanf("%d", &aux->dato.A);
            printf("V (Vulnerabilidad): "); scanf("%d", &aux->dato.V);

            calcularParametros(&aux->dato);
            printf("[+] Riesgo recalculado exitosamente.\n");
            return;
        }
        aux = aux->siguiente;
    }
    printf("[!] Riesgo no encontrado.\n");
}

void borrarRiesgo(Nodo** cabeza) {
    if (!*cabeza) {
        printf("\n[!] Lista vacia.\n");
        return;
    }

    char nombre[MAX_STR];
    getchar();
    printf("\nIngrese el nombre del riesgo a eliminar: ");
    fgets(nombre, MAX_STR, stdin);
    nombre[strcspn(nombre, "\n")] = 0;

    Nodo* actual = *cabeza;
    Nodo* anterior = NULL;

    while (actual != NULL && strcasecmp(actual->dato.nombre, nombre) != 0) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (!actual) {
        printf("[!] Riesgo no encontrado.\n");
        return;
    }

    if (!anterior) {
        *cabeza = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    free(actual);
    printf("[+] Riesgo '%s' liberado de la memoria dinamica.\n", nombre);
}

// --- PERSISTENCIA: JSON (cJSON) ---

void guardarJSONLibreria(Nodo* cabeza, const char* nombreArchivo) {
    cJSON* jsonArray = cJSON_CreateArray();
    Nodo* aux = cabeza;

    while (aux != NULL) {
        cJSON* obj = cJSON_CreateObject();
        cJSON_AddStringToObject(obj, "nombre", aux->dato.nombre);
        cJSON_AddNumberToObject(obj, "F", aux->dato.F);
        cJSON_AddNumberToObject(obj, "S", aux->dato.S);
        cJSON_AddNumberToObject(obj, "P", aux->dato.P);
        cJSON_AddNumberToObject(obj, "E", aux->dato.E);
        cJSON_AddNumberToObject(obj, "A", aux->dato.A);
        cJSON_AddNumberToObject(obj, "V", aux->dato.V);
        cJSON_AddNumberToObject(obj, "I", aux->dato.I);
        cJSON_AddNumberToObject(obj, "D", aux->dato.D);
        cJSON_AddNumberToObject(obj, "C", aux->dato.C);
        cJSON_AddNumberToObject(obj, "PB", aux->dato.PB);
        cJSON_AddNumberToObject(obj, "ER", aux->dato.ER);

        cJSON_AddItemToArray(jsonArray, obj);
        aux = aux->siguiente;
    }

    char* stringJSON = cJSON_Print(jsonArray);
    FILE* file = fopen(nombreArchivo, "w");
    if (file) {
        fputs(stringJSON, file);
        fclose(file);
        printf("[+] Guardado exitoso con libreria cJSON en: '%s'\n", nombreArchivo);
    } else {
        printf("[!] Error al abrir el archivo JSON para escritura.\n");
    }

    cJSON_Delete(jsonArray);
    free(stringJSON);
}

void cargarJSONLibreria(Nodo** cabeza, const char* nombreArchivo) {
    FILE* file = fopen(nombreArchivo, "rb");
    if (!file) {
        printf("[!] No se pudo abrir el archivo JSON '%s'.\n", nombreArchivo);
        return;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(length + 1);
    if (!buffer) {
        fclose(file);
        return;
    }
    fread(buffer, 1, length, file);
    buffer[length] = '\0';
    fclose(file);

    cJSON* jsonArray = cJSON_Parse(buffer);
    free(buffer);

    if (!jsonArray) {
        printf("[!] Error al analizar la estructura JSON con la libreria.\n");
        return;
    }

    liberarMemoria(cabeza);

    int total = cJSON_GetArraySize(jsonArray);
    for (int i = 0; i < total; i++) {
        cJSON* item = cJSON_GetArrayItem(jsonArray, i);

        Riesgo r;
        strcpy(r.nombre, cJSON_GetObjectItemCaseSensitive(item, "nombre")->valuestring);
        r.F = cJSON_GetObjectItemCaseSensitive(item, "F")->valueint;
        r.S = cJSON_GetObjectItemCaseSensitive(item, "S")->valueint;
        r.P = cJSON_GetObjectItemCaseSensitive(item, "P")->valueint;
        r.E = cJSON_GetObjectItemCaseSensitive(item, "E")->valueint;
        r.A = cJSON_GetObjectItemCaseSensitive(item, "A")->valueint;
        r.V = cJSON_GetObjectItemCaseSensitive(item, "V")->valueint;

        agregarRiesgoDinamico(cabeza, r);
    }

    cJSON_Delete(jsonArray);
    printf("[+] Carga dinamica completada desde JSON usando cJSON.\n");
}

// --- PERSISTENCIA: CSV ---

void guardarCSV(Nodo* cabeza, const char* nombreArchivo) {
    FILE* file = fopen(nombreArchivo, "w");
    if (!file) return;

    fprintf(file, "Nombre,F,S,P,E,A,V,I,D,C,PB,ER\n");
    Nodo* aux = cabeza;
    while (aux != NULL) {
        Riesgo r = aux->dato;
        fprintf(file, "%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
                r.nombre, r.F, r.S, r.P, r.E, r.A, r.V,
                r.I, r.D, r.C, r.PB, r.ER);
        aux = aux->siguiente;
    }
    fclose(file);
    printf("[+] Guardado en texto plano CSV: '%s'\n", nombreArchivo);
}

// --- PERSISTENCIA: XML ---

void guardarXML(Nodo* cabeza, const char* nombreArchivo) {
    FILE* file = fopen(nombreArchivo, "w");
    if (!file) {
        printf("[!] Error al abrir el archivo XML para escritura.\n");
        return;
    }

    fprintf(file, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(file, "<matriz_riesgos>\n");

    Nodo* aux = cabeza;
    while (aux != NULL) {
        Riesgo r = aux->dato;
        fprintf(file, "  <riesgo>\n");
        fprintf(file, "    <nombre>%s</nombre>\n", r.nombre);
        fprintf(file, "    <F>%d</F>\n", r.F);
        fprintf(file, "    <S>%d</S>\n", r.S);
        fprintf(file, "    <P>%d</P>\n", r.P);
        fprintf(file, "    <E>%d</E>\n", r.E);
        fprintf(file, "    <A>%d</A>\n", r.A);
        fprintf(file, "    <V>%d</V>\n", r.V);
        fprintf(file, "    <I>%d</I>\n", r.I);
        fprintf(file, "    <D>%d</D>\n", r.D);
        fprintf(file, "    <C>%d</C>\n", r.C);
        fprintf(file, "    <PB>%d</PB>\n", r.PB);
        fprintf(file, "    <ER>%d</ER>\n", r.ER);
        fprintf(file, "  </riesgo>\n");
        aux = aux->siguiente;
    }

    fprintf(file, "</matriz_riesgos>\n");
    fclose(file);
    printf("[+] Guardado exitoso en texto plano XML: '%s'\n", nombreArchivo);
}

void cargarXML(Nodo** cabeza, const char* nombreArchivo) {
    FILE* file = fopen(nombreArchivo, "r");
    if (!file) {
        printf("[!] No se pudo abrir el archivo XML '%s'.\n", nombreArchivo);
        return;
    }

    liberarMemoria(cabeza);

    char linea[256];
    Riesgo r;
    int leyendoRiesgo = 0;

    while (fgets(linea, sizeof(linea), file)) {
        if (strstr(linea, "<riesgo>")) {
            leyendoRiesgo = 1;
            memset(&r, 0, sizeof(Riesgo));
        }

        if (leyendoRiesgo) {
            sscanf(linea, " <nombre>%99[^<]</nombre>", r.nombre);
            sscanf(linea, " <F>%d</F>", &r.F);
            sscanf(linea, " <S>%d</S>", &r.S);
            sscanf(linea, " <P>%d</P>", &r.P);
            sscanf(linea, " <E>%d</E>", &r.E);
            sscanf(linea, " <A>%d</A>", &r.A);
            sscanf(linea, " <V>%d</V>", &r.V);
        }

        if (strstr(linea, "</riesgo>")) {
            leyendoRiesgo = 0;
            agregarRiesgoDinamico(cabeza, r);
        }
    }

    fclose(file);
    printf("[+] Carga dinamica completada desde el archivo XML.\n");
}

// --- MENÚ PRINCIPAL ---

int main() {
    Nodo* listaRiesgos = NULL;
    char archivoJSON[MAX_STR] = "matriz_riesgos.json";
    char archivoCSV[MAX_STR]  = "matriz_riesgos.csv";
    char archivoXML[MAX_STR]  = "matriz_riesgos.xml";
    int opcion;

    // Crear el riesgo solicitado por defecto
    Riesgo espionaje = {"espionaje sobre proyectos claves", 4, 5, 4, 3, 4, 3, 0, 0, 0, 0, 0};
    agregarRiesgoDinamico(&listaRiesgos, espionaje);

    do {
        printf("\n================ METODO MOSLER (JSON / CSV / XML) ================\n");
        printf("1. Crear nuevo riesgo\n");
        printf("2. Modificar parametros de riesgo\n");
        printf("3. Calcular e imprimir riesgos\n");
        printf("4. Borrar riesgo\n");
        printf("5. Seleccionar / Crear nombres de archivo especificos\n");
        printf("6. Guardar registros en disco (JSON, CSV y XML)\n");
        printf("7. Cargar desde archivo JSON a memoria dinamica\n");
        printf("8. Cargar desde archivo XML a memoria dinamica\n");
        printf("9. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: {
                Riesgo r;
                getchar();
                printf("\nNombre del riesgo: ");
                fgets(r.nombre, MAX_STR, stdin);
                r.nombre[strcspn(r.nombre, "\n")] = 0;
                printf("F (1-5): "); scanf("%d", &r.F);
                printf("S (1-5): "); scanf("%d", &r.S);
                printf("P (1-5): "); scanf("%d", &r.P);
                printf("E (1-5): "); scanf("%d", &r.E);
                printf("A (1-5): "); scanf("%d", &r.A);
                printf("V (1-5): "); scanf("%d", &r.V);
                agregarRiesgoDinamico(&listaRiesgos, r);
                break;
            }
            case 2:
                modificarRiesgo(listaRiesgos);
                break;
            case 3:
                imprimirRiesgos(listaRiesgos);
                break;
            case 4:
                borrarRiesgo(&listaRiesgos);
                break;
            case 5:
                getchar();
                printf("\nNombre para el archivo JSON [%s]: ", archivoJSON);
                fgets(archivoJSON, MAX_STR, stdin);
                archivoJSON[strcspn(archivoJSON, "\n")] = 0;

                printf("Nombre para el archivo CSV [%s]: ", archivoCSV);
                fgets(archivoCSV, MAX_STR, stdin);
                archivoCSV[strcspn(archivoCSV, "\n")] = 0;

                printf("Nombre para el archivo XML [%s]: ", archivoXML);
                fgets(archivoXML, MAX_STR, stdin);
                archivoXML[strcspn(archivoXML, "\n")] = 0;

                printf("[+] Rutas y nombres de archivo actualizados.\n");
                break;
            case 6:
                guardarJSONLibreria(listaRiesgos, archivoJSON);
                guardarCSV(listaRiesgos, archivoCSV);
                guardarXML(listaRiesgos, archivoXML);
                break;
            case 7:
                cargarJSONLibreria(&listaRiesgos, archivoJSON);
                break;
            case 8:
                cargarXML(&listaRiesgos, archivoXML);
                break;
            case 9:
                liberarMemoria(&listaRiesgos);
                printf("\n[+] Memoria liberada correctamente. Saliendo...\n");
                break;
            default:
                printf("\n[!] Opcion invalida.\n");
        }
    } while (opcion != 9);

    return 0;
}
