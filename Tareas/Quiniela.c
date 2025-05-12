#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CANTIDAD_NUMEROS 10 // Número de dígitos que se generan y se ingresan

// Función para generar números aleatorios de 2 dígitos
void generarNumerosAleatorios(int numeros[]) {
    for (int i = 0; i < CANTIDAD_NUMEROS; i++) {
        numeros[i] = rand() % 90 + 10; // Generar números entre 10 y 99
    }
}

// Función para contar cuántos números del usuario coinciden con los generados
int contarAciertos(int numerosUsuario[], int numerosAleatorios[], int aciertos[]) {
    int cantidadAciertos = 0;
    for (int i = 0; i < CANTIDAD_NUMEROS; i++) {
        for (int j = 0; j < CANTIDAD_NUMEROS; j++) {
            if (numerosUsuario[i] == numerosAleatorios[j]) {
                aciertos[cantidadAciertos++] = numerosUsuario[i]; // Guardar el número acertado
                break;
            }
        }
    }
    return cantidadAciertos; // Retornar la cantidad de aciertos
}

// Función para calcular las ganancias según la cantidad de aciertos
double calcularGanancias(int cantidadAciertos, double montoApostado) {
    double multiplicador = 0;
    // Asignar el multiplicador según las reglas del juego
    switch (cantidadAciertos) {
        case 10: multiplicador = 50; break;
        case 9: multiplicador = 40; break;
        case 8: multiplicador = 30; break;
        case 7: multiplicador = 25; break;
        case 6: multiplicador = 20; break;
        case 5: multiplicador = 15; break;
        case 4: multiplicador = 10; break;
        case 3: multiplicador = 5; break;
        case 2: multiplicador = 2; break;
        case 1: multiplicador = 0.5; break;
        default: multiplicador = 0; break; // Sin aciertos, no hay ganancias
    }
    return montoApostado * multiplicador; // Calcular las ganancias
}

// Función para imprimir los resultados de la jugada
void imprimirResultados(int aciertos[], int cantidadAciertos, int numerosUsuario[], int numerosAleatorios[], double ganancias, double impuesto, double gananciasNetas) {
    printf("\n--- Resultados ---\n");
    printf("Números Aleatorios: ");
    for (int i = 0; i < CANTIDAD_NUMEROS; i++) {
        printf("%d ", numerosAleatorios[i]); // Mostrar los números generados
    }
    printf("\nTus Números: ");
    for (int i = 0; i < CANTIDAD_NUMEROS; i++) {
        printf("%d ", numerosUsuario[i]); // Mostrar los números ingresados por el usuario
    }
    printf("\nNúmeros Acertados: ");
    for (int i = 0; i < cantidadAciertos; i++) {
        printf("%d ", aciertos[i]); // Mostrar los números acertados
    }
    printf("\nGanancias: %.2f\n", ganancias); // Mostrar las ganancias brutas
    printf("Impuesto (10%%): %.2f\n", impuesto); // Mostrar el impuesto aplicado
    printf("Ganancias Netas: %.2f\n", gananciasNetas); // Mostrar las ganancias netas
}

int main() {
    srand(time(NULL)); // Inicializar la semilla para números aleatorios
    int numerosAleatorios[CANTIDAD_NUMEROS], numerosUsuario[CANTIDAD_NUMEROS], aciertos[CANTIDAD_NUMEROS];
    double totalApostado = 0, totalGanado = 0; // Variables para acumular totales

    char jugarDeNuevo;
    do {
        generarNumerosAleatorios(numerosAleatorios); // Generar los números aleatorios

        printf("Ingresa tus 10 números (2 dígitos cada uno):\n");
        for (int i = 0; i < CANTIDAD_NUMEROS; i++) {
            int validInput = 0;
            do {
                printf("Número %d: ", i + 1);
                if (scanf("%d", &numerosUsuario[i]) == 1 && numerosUsuario[i] >= 10 && numerosUsuario[i] <= 99) {
                    validInput = 1; // Entrada válida
                } else {
                    printf("Entrada inválida. Por favor, ingresa un número de 2 dígitos.\n");
                    while (getchar() != '\n'); // Limpiar el buffer de entrada
                }
            } while (!validInput); // Repetir hasta que la entrada sea válida
        }

        double montoApostado;
        do {
            printf("Ingresa el monto a apostar: ");
            if (scanf("%lf", &montoApostado) == 1 && montoApostado > 0) {
                break; // Entrada válida
            } else {
                printf("Entrada inválida. Por favor, ingresa un monto positivo.\n");
                while (getchar() != '\n'); // Limpiar el buffer de entrada
            }
        } while (1); // Repetir hasta que la entrada sea válida

        totalApostado += montoApostado; // Acumular el monto apostado

        int cantidadAciertos = contarAciertos(numerosUsuario, numerosAleatorios, aciertos); // Contar aciertos
        double ganancias = calcularGanancias(cantidadAciertos, montoApostado); // Calcular ganancias
        double impuesto = ganancias * 0.1; // Calcular impuesto
        double gananciasNetas = ganancias - impuesto; // Calcular ganancias netas

        totalGanado += gananciasNetas; // Acumular las ganancias netas

        imprimirResultados(aciertos, cantidadAciertos, numerosUsuario, numerosAleatorios, ganancias, impuesto, gananciasNetas); // Mostrar resultados

        printf("\n¿Quieres jugar de nuevo? (s/n): ");
        scanf(" %c", &jugarDeNuevo); // Preguntar si desea jugar de nuevo
    } while (jugarDeNuevo == 's' || jugarDeNuevo == 'S'); // Continuar si el usuario elige 's'

    printf("\n--- Resumen del Juego ---\n");
    printf("Total Apostado: %.2f\n", totalApostado); // Mostrar el total apostado
    printf("Total Ganado: %.2f\n", totalGanado); // Mostrar el total ganado
    printf("Resultado Neto: %.2f\n", totalGanado - totalApostado); // Mostrar el resultado neto

    return 0; // Finalizar el programa

//Este trabajo fue realizado por: Julio Cesar Ojeda Martinez y Manuel Ernesto Gonzalez Gonzalez
}
