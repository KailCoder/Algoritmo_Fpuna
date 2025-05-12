#include <stdio.h>

int main() {
    int cantidad_ingresos = 0, cantidad_egresos = 0;
    float dato, balance_anterior = 0.0, total_ingresos = 0.0, total_egresos = 0.0;
    char operacion='+'; // Initialize with a default operation
    // Se inicializa la variable operacion con un valor por defecto para evitar problemas en la primera iteracion.

    printf("Ingrese el balance anterior: ");
    scanf("%f", &balance_anterior);

    float balance_actual = balance_anterior;
    int es_primer_dato = 1; // Flag to ignore the first number

    do {
        printf("Ingrese una operacion (+ para ingreso, - para egreso, = para finalizar): ");
        scanf(" %c", &operacion);

        if (operacion == '=') {
            break;
        }

        printf("Ingrese el monto: ");
        scanf("%f", &dato);

        if (es_primer_dato) {
            es_primer_dato = 0; // Skip processing the first number
            continue;
        }

        if (operacion == '+') {
            balance_actual += dato;
            total_ingresos += dato;
            cantidad_ingresos++;
        } else if (operacion == '-') {
            balance_actual -= dato;
            total_egresos += dato;
            cantidad_egresos++;
        }
    } while (1);

    printf("\nBalance final: %.2f\n", balance_actual);
    printf("Total de ingresos: %.2f\n", total_ingresos);
    printf("Cantidad de ingresos: %d\n", cantidad_ingresos);
    printf("Promedio de ingresos: %.2f\n", cantidad_ingresos > 0 ? total_ingresos / cantidad_ingresos : 0.0);
    printf("Total de egresos: %.2f\n", total_egresos);
    printf("Cantidad de egresos: %d\n", cantidad_egresos);
    printf("Promedio de egresos: %.2f\n", cantidad_egresos > 0 ? total_egresos / cantidad_egresos : 0.0);

    return 0;
}
