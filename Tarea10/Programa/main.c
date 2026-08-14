#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARCHIVO "vehiculos.dat"
#define CONFIG_FILE "config.txt"

// Estructura para almacenar los datos técnicos del vehículo
typedef struct {
    int id;
    char marca_modelo[50];
    double costo_inicial;
    double valor_residual;
    int vida_util_anos;
    double km_anuales_estimados; // Nuevo parámetro guardado para precisión de costo/km
    double seguro_anual;
    double mantenimiento_anual;
    double costo_neumaticos_anual;

    // Métricas de consumo: Galones consumidos cada 100 km
    double galones_por_100km_ciudad;
    double galones_por_100km_autopista;

    int activo; // 1 = Activo, 0 = Borrado lógico
} Vehiculo;

// Funciones de gestión de vehículos
void crear_vehiculo();
void mostrar_vehiculos();
void modificar_vehiculo();
void borrar_vehiculo();

// Funciones de cálculo y configuración
void calcular_viaje();
void modificar_precio_combustible();
double obtener_precio_combustible();

int main() {
    int opcion;

    do {
        printf("\n=== GESTION DE COSTOS DE VEHICULOS ===\n");
        printf("Precio actual del combustible: $%.2f por Galon\n", obtener_precio_combustible());
        printf("1. Crear nuevo vehiculo y guardar en archivo\n");
        printf("2. Mostrar lista de vehiculos\n");
        printf("3. Cambiar parametros de un vehiculo\n");
        printf("4. Borrar vehiculo\n");
        printf("5. Calcular costo real de uso por km y costo de viaje\n");
        printf("6. Modificar precio global del combustible\n");
        printf("7. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar(); // Limpiar el buffer

        switch (opcion) {
            case 1: crear_vehiculo(); break;
            case 2: mostrar_vehiculos(); break;
            case 3: modificar_vehiculo(); break;
            case 4: borrar_vehiculo(); break;
            case 5: calcular_viaje(); break;
            case 6: modificar_precio_combustible(); break;
            case 7: printf("Saliendo del programa...\n"); break;
            default: printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 7);

    return 0;
}

// 1. CREAR VEHÍCULO Y GUARDAR EN ARCHIVO
void crear_vehiculo() {
    FILE *file = fopen(ARCHIVO, "ab+");
    if (!file) {
        printf("Error al abrir el archivo de datos.\n");
        return;
    }

    Vehiculo v;
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    v.id = (int)(size / sizeof(Vehiculo)) + 1;
    v.activo = 1;

    printf("\n--- Crear Nuevo Vehiculo (ID: %d) ---\n", v.id);
    printf("Marca y Modelo: ");
    fgets(v.marca_modelo, sizeof(v.marca_modelo), stdin);
    v.marca_modelo[strcspn(v.marca_modelo, "\n")] = 0;

    printf("Costo Inicial del vehiculo: $"); scanf("%lf", &v.costo_inicial);
    printf("Valor Residual (al terminar vida util): $"); scanf("%lf", &v.valor_residual);
    printf("Vida Util estimada (en anos): "); scanf("%d", &v.vida_util_anos);
    printf("Promedio de Kilometros recorridos AL ANO: "); scanf("%lf", &v.km_anuales_estimados);
    printf("Costo de Seguro Anual: $"); scanf("%lf", &v.seguro_anual);
    printf("Costo de Mantenimiento Anual: $"); scanf("%lf", &v.mantenimiento_anual);
    printf("Costo de Neumaticos Anual: $"); scanf("%lf", &v.costo_neumaticos_anual);

    printf("Consumo en Ciudad (Galones por cada 100 km): "); scanf("%lf", &v.galones_por_100km_ciudad);
    printf("Consumo en Autopista (Galones por cada 100 km): "); scanf("%lf", &v.galones_por_100km_autopista);

    fwrite(&v, sizeof(Vehiculo), 1, file);
    fclose(file);
    printf("Vehiculo guardado exitosamente en el archivo.\n");
}

// MOSTRAR VEHÍCULOS
void mostrar_vehiculos() {
    FILE *file = fopen(ARCHIVO, "rb");
    if (!file) {
        printf("\nNo hay vehiculos registrados todavia.\n");
        return;
    }

    Vehiculo v;
    printf("\n--- Lista de Vehiculos Disponibles ---\n");
    printf("ID\tMarca y Modelo\t\tKm/Ano\t\tConsumo Ciudad\tConsumo Autopista\n");
    printf("-----------------------------------------------------------------------------------\n");
    while (fread(&v, sizeof(Vehiculo), 1, file)) {
        if (v.activo) {
            printf("%d\t%-20s\t%.0f km\t\t%.1f G/100km\t%.1f G/100km\n",
                   v.id, v.marca_modelo, v.km_anuales_estimados, v.galones_por_100km_ciudad, v.galones_por_100km_autopista);
        }
    }
    fclose(file);
}

// 2. CAMBIAR PARÁMETROS DE UN VEHÍCULO
void modificar_vehiculo() {
    mostrar_vehiculos();
    int id_buscar;
    printf("\nIngrese el ID del vehiculo que desea modificar: ");
    scanf("%d", &id_buscar);
    getchar();

    FILE *file = fopen(ARCHIVO, "r+b");
    if (!file) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    Vehiculo v;
    int encontrado = 0;

    while (fread(&v, sizeof(Vehiculo), 1, file)) {
        if (v.id == id_buscar && v.activo) {
            encontrado = 1;
            printf("\n--- Modificando Parametros de: %s ---\n", v.marca_modelo);
            printf("Nuevo Promedio Km Anuales (Actual: %.0f km): ", v.km_anuales_estimados); scanf("%lf", &v.km_anuales_estimados);
            printf("Nuevo Seguro Anual (Actual: $%.2f): $", v.seguro_anual); scanf("%lf", &v.seguro_anual);
            printf("Nuevo Mantenimiento Anual (Actual: $%.2f): $", v.mantenimiento_anual); scanf("%lf", &v.mantenimiento_anual);
            printf("Nuevo Costo de Neumaticos Anual (Actual: $%.2f): $", v.costo_neumaticos_anual); scanf("%lf", &v.costo_neumaticos_anual);

            printf("Nuevo Consumo Ciudad (Actual: %.2f G/100km): ", v.galones_por_100km_ciudad); scanf("%lf", &v.galones_por_100km_ciudad);
            printf("Nuevo Consumo Autopista (Actual: %.2f G/100km): ", v.galones_por_100km_autopista); scanf("%lf", &v.galones_por_100km_autopista);

            fseek(file, -((long)sizeof(Vehiculo)), SEEK_CUR);
            fwrite(&v, sizeof(Vehiculo), 1, file);
            printf("Parametros actualizados correctamente.\n");
            break;
        }
    }

    if (!encontrado) printf("Vehiculo con ID %d no encontrado o no esta activo.\n", id_buscar);
    fclose(file);
}

// 3. BORRAR VEHÍCULO (Borrado lógico)
void borrar_vehiculo() {
    mostrar_vehiculos();
    int id_buscar;
    printf("\nIngrese el ID del vehiculo que desea borrar: ");
    scanf("%d", &id_buscar);

    FILE *file = fopen(ARCHIVO, "r+b");
    if (!file) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    Vehiculo v;
    int encontrado = 0;

    while (fread(&v, sizeof(Vehiculo), 1, file)) {
        if (v.id == id_buscar && v.activo) {
            encontrado = 1;
            v.activo = 0;

            fseek(file, -((long)sizeof(Vehiculo)), SEEK_CUR);
            fwrite(&v, sizeof(Vehiculo), 1, file);
            printf("Vehiculo '%s' eliminado con exito del registro.\n", v.marca_modelo);
            break;
        }
    }

    if (!encontrado) printf("Vehiculo con ID %d no encontrado.\n", id_buscar);
    fclose(file);
}

// 4. CALCULAR COSTO REAL POR KM Y COSTO DE VIAJE
void calcular_viaje() {
    mostrar_vehiculos();
    int id_buscar;
    printf("\nSeleccione el ID del vehiculo para el viaje: ");
    scanf("%d", &id_buscar);

    FILE *file = fopen(ARCHIVO, "rb");
    if (!file) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    Vehiculo v;
    int encontrado = 0;

    while (fread(&v, sizeof(Vehiculo), 1, file)) {
        if (v.id == id_buscar && v.activo) {
            encontrado = 1;
            double km_ciudad, km_autopista;
            double precio_galon = obtener_precio_combustible();

            if (v.km_anuales_estimados <= 0) {
                printf("Error: Los kilometros anuales del vehiculo deben ser mayores a 0 para calcular el desglose.\n");
                break;
            }

            printf("\n--- DATOS DEL VIAJE PARA: %s ---\n", v.marca_modelo);
            printf("Kilometros a recorrer en CIUDAD: "); scanf("%lf", &km_ciudad);
            printf("Kilometros a recorrer en AUTOPISTA: "); scanf("%lf", &km_autopista);

            // 1. CÁLCULO DE COSTOS FIJOS Y DE DESGASTE ANUALES
            double amortizacion_anual = (v.costo_inicial - v.valor_residual) / v.vida_util_anos;
            double gastos_fijos_y_mantenimiento_anual = amortizacion_anual
                                                       + v.seguro_anual
                                                       + v.mantenimiento_anual
                                                       + v.costo_neumaticos_anual;

            // Costo indirecto real por cada kilómetro recorrido basándose en el kilometraje anual registrado
            double costo_fijo_por_km = gastos_fijos_y_mantenimiento_anual / v.km_anuales_estimados;

            // 2. CÁLCULO DE COMBUSTIBLE PARA EL VIAJE
            double galones_ciudad = (km_ciudad / 100.0) * v.galones_por_100km_ciudad;
            double galones_autopista = (km_autopista / 100.0) * v.galones_por_100km_autopista;
            double galones_totales = galones_ciudad + galones_autopista;
            double costo_combustible_viaje = galones_totales * precio_galon;

            // Costo de combustible por km específico en esta ruta combinada
            double km_totales_viaje = km_ciudad + km_autopista;
            double costo_combustible_por_km = (km_totales_viaje > 0) ? (costo_combustible_viaje / km_totales_viaje) : 0;

            // 3. COSTO REAL TOTAL POR KILÓMETRO EN ESTA RUTA
            double costo_real_por_km = costo_fijo_por_km + costo_combustible_por_km;

            printf("\n======================================================\n");
            printf("               DESGLOSE DE COSTO REAL                 \n");
            printf("======================================================\n");
            printf("A. Costo Fijo/Desgaste por km (Amort.+Seguro+Mant.): $%.3f / km\n", costo_fijo_por_km);
            printf("B. Costo Combustible por km (En esta ruta)         : $%.3f / km\n", costo_combustible_por_km);
            printf("------------------------------------------------------\n");
            printf("--> COSTO REAL DE OPERAR EL VEHICULO: $%.3f por km <--\n", costo_real_por_km);
            printf("======================================================\n\n");

            printf("--- RESUMEN MONETARIO DEL VIAJE (%.1f km) ---\n", km_totales_viaje);
            printf("Galones consumidos en ciudad    : %.2f G ($%.2f)\n", galones_ciudad, galones_ciudad * precio_galon);
            printf("Galones consumidos en autopista : %.2f G ($%.2f)\n", galones_autopista, galones_autopista * precio_galon);
            printf("Total combustible               : %.2f G ($%.2f)\n", galones_totales, costo_combustible_viaje);
            printf("Costo por Desgaste : $%.2f\n", costo_fijo_por_km * km_totales_viaje);
            printf("------------------------------------------------------\n");
            printf("COSTO TOTAL DEL VIAJE           : $%.2f\n", costo_real_por_km * km_totales_viaje);
            break;
        }
    }

    if (!encontrado) printf("Vehiculo no encontrado.\n");
    fclose(file);
}

// 5. MODIFICAR PRECIO DE COMBUSTIBLE
void modificar_precio_combustible() {
    double nuevo_precio;
    printf("Ingrese el nuevo precio del combustible (por Galon): $");
    scanf("%lf", &nuevo_precio);

    FILE *config = fopen(CONFIG_FILE, "w");
    if (config) {
        fprintf(config, "%lf", nuevo_precio);
        fclose(config);
        printf("Precio del galon de combustible actualizado globalmente.\n");
    } else {
        printf("Error al guardar la configuracion.\n");
    }
}

// Función auxiliar para leer el precio actual del combustible
double obtener_precio_combustible() {
    double precio = 4.50; // Valor por defecto
    FILE *config = fopen(CONFIG_FILE, "r");
    if (config) {
        fscanf(config, "%lf", &precio);
        fclose(config);
    }
    return precio;
}
