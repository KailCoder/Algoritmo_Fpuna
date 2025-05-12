#include <stdio.h>
#include <limits.h>

#define VENDEDORES 10
#define MESES 12

// Estructura que representa un registro de ventas
typedef struct {
    int numero_vendedor; // Número del vendedor (1 a 10)
    int mes;             // Mes del año (1 a 12)
    int total_visitas;   // Total de visitas realizadas por el vendedor
    int total_ventas;    // Total de ventas realizadas por el vendedor
} Registro;

// Función que genera un resumen anual basado en los registros de ventas
void generarResumen(Registro registros[], int cantidad) {
    FILE *archivo = fopen("resumen_anual.txt", "w");

    if (archivo == NULL) {
        printf("Error al crear el archivo.\n");
        return;
    }

    // Variables para almacenar totales y máximos/mínimos
    int total_ventas_anual = 0, total_visitas_anual = 0;
    int max_ventas = INT_MIN, min_ventas = INT_MAX;
    int vendedor_max = 0, vendedor_min = 0;
    int mes_max = 0, mes_min = 0;

    // Arreglos para acumular ventas por vendedor y por mes
    int ventas_por_vendedor[VENDEDORES] = {0};
    int ventas_por_mes[MESES] = {0};

    // Acumular totales y clasificar ventas por vendedor y mes
    for (int i = 0; i < cantidad; i++) {
        total_ventas_anual += registros[i].total_ventas;
        total_visitas_anual += registros[i].total_visitas;

        ventas_por_vendedor[registros[i].numero_vendedor - 1] += registros[i].total_ventas;
        ventas_por_mes[registros[i].mes - 1] += registros[i].total_ventas;
    }

    // Determinar el vendedor con más y menos ventas
    for (int i = 0; i < VENDEDORES; i++) {
        if (ventas_por_vendedor[i] > max_ventas) {
            max_ventas = ventas_por_vendedor[i];
            vendedor_max = i + 1;
        }
        if (ventas_por_vendedor[i] < min_ventas) {
            min_ventas = ventas_por_vendedor[i];
            vendedor_min = i + 1;
        }
    }

    // Determinar el mes con más y menos ventas
    max_ventas = INT_MIN;
    min_ventas = INT_MAX;
    for (int i = 0; i < MESES; i++) {
        if (ventas_por_mes[i] > max_ventas) {
            max_ventas = ventas_por_mes[i];
            mes_max = i + 1;
        }
        if (ventas_por_mes[i] < min_ventas) {
            min_ventas = ventas_por_mes[i];
            mes_min = i + 1;
        }
    }

    // Escribir el resumen en el archivo
    fprintf(archivo, "Resumen Anual\n");
    fprintf(archivo, "Total de ventas en el año: %d\n", total_ventas_anual);
    fprintf(archivo, "Total de visitas en el año: %d\n", total_visitas_anual);
    fprintf(archivo, "Porcentaje de ventas respecto a visitas: %.2f%%\n", (total_visitas_anual == 0) ? 0 : ((float)total_ventas_anual / total_visitas_anual) * 100);
    fprintf(archivo, "Vendedor con más ventas: %d\n", vendedor_max);
    fprintf(archivo, "Vendedor con menos ventas: %d\n", vendedor_min);
    fprintf(archivo, "Mes con más ventas: %d\n", mes_max);
    fprintf(archivo, "Mes con menos ventas: %d\n", mes_min);

    fclose(archivo);
    printf("Archivo 'resumen_anual.txt' generado correctamente.\n");
}

// Función principal
int main() {
    // Datos de ejemplo para probar la funcionalidad
    Registro registros[] = {
        {1, 1, 100, 50},
        {2, 1, 80, 40},
        {3, 2, 150, 70},
        {1, 2, 120, 60},
        {2, 3, 90, 45},
        {3, 3, 200, 100}
    };

    // Calcular la cantidad de registros
    int cantidad = sizeof(registros) / sizeof(registros[0]);

    // Generar el resumen anual
    generarResumen(registros, cantidad);

    return 0;
}
