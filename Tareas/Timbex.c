#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definiciones de constantes
// Se utiliza #define para definir constantes porque:
// 1. Permite asignar valores que no cambian durante la ejecución del programa.
// 2. Mejora la legibilidad del código al usar nombres descriptivos en lugar de valores "mágicos".
// 3. Facilita el mantenimiento, ya que cambiar el valor de una constante solo requiere modificarlo aquí.
#define SALDO_INICIAL 100000 // Saldo inicial de cada jugador
#define MONTO_APUESTA 10000  // Monto fijo de cada apuesta
#define NUM_JUGADORES 3      // Número de jugadores
#define NUM_ALEATORIOS 10    // Cantidad de números aleatorios generados por ronda

// Función para generar números aleatorios entre 1 y 10
void generar_numeros_aleatorios(int numeros_aleatorios[]) {
    for (int i = 0; i < NUM_ALEATORIOS; i++) {
        numeros_aleatorios[i] = (rand() % 10) + 1; // Genera un número entre 1 y 10
    }
}

// Función para encontrar la posición de un número en el arreglo de números aleatorios
int encontrar_posicion(int numero, int numeros_aleatorios[]) {
    for (int i = 0; i < NUM_ALEATORIOS; i++) {
        if (numeros_aleatorios[i] == numero) {
            return i + 1; // Retorna la posición (base 1)
        }
    }
    return -1; // Retorna -1 si el número no se encuentra
}

int main() {
    // Inicialización de saldos de los jugadores
    int saldos[NUM_JUGADORES] = {SALDO_INICIAL, SALDO_INICIAL, SALDO_INICIAL};
    int apuestas[NUM_JUGADORES]; // Arreglo para almacenar las apuestas de los jugadores
    int numeros_aleatorios[NUM_ALEATORIOS]; // Arreglo para almacenar los números aleatorios generados
    int ganador_ronda = -1; // Variable para almacenar el ganador de la ronda (si aplica)

    srand(time(NULL)); // Inicializa la semilla para la generación de números aleatorios

    while (1) {
        printf("\n--- Nueva Ronda ---\n");

        // Verificar si algún jugador se quedó sin saldo
        for (int i = 0; i < NUM_JUGADORES; i++) {
            if (saldos[i] <= 0) {
                printf("Jugador %d se quedó sin saldo. Fin del juego.\n", i + 1);
                return 0; // Termina el programa
            }
        }

        // Los jugadores realizan sus apuestas
        for (int i = 0; i < NUM_JUGADORES; i++) {
            do {
                printf("Jugador %d, ingrese un número entre 1 y 10: ", i + 1);
                scanf("%d", &apuestas[i]); // Lee la apuesta del jugador
            } while (apuestas[i] < 1 || apuestas[i] > 10); // Valida que la apuesta esté en el rango permitido
        }

        // Generar números aleatorios para la ronda
        generar_numeros_aleatorios(numeros_aleatorios);
        printf("Números aleatorios: ");
        for (int i = 0; i < NUM_ALEATORIOS; i++) {
            printf("%d ", numeros_aleatorios[i]); // Muestra los números generados
        }
        printf("\n");

        // Determinar las posiciones de las apuestas en los números aleatorios
        int posiciones[NUM_JUGADORES];
        for (int i = 0; i < NUM_JUGADORES; i++) {
            posiciones[i] = encontrar_posicion(apuestas[i], numeros_aleatorios);
        }

        // Determinar la posición mínima (ganador de la ronda)
        int posicion_minima = NUM_ALEATORIOS + 1; // Inicializa con un valor mayor al máximo posible
        for (int i = 0; i < NUM_JUGADORES; i++) {
            if (posiciones[i] != -1 && posiciones[i] < posicion_minima) {
                posicion_minima = posiciones[i];
            }
        }

        // Contar el número de ganadores
        int ganadores = 0;
        for (int i = 0; i < NUM_JUGADORES; i++) {
            if (posiciones[i] == posicion_minima) {
                ganadores++;
            }
        }

        // Actualizar los saldos de los jugadores
        if (ganadores == 0 || ganadores == NUM_JUGADORES) {
            // Si todos pierden o todos ganan, no hay cambios en los saldos
            printf("No hay cambios en los saldos esta ronda.\n");
        } else {
            // Si hay ganadores, se actualizan los saldos
            for (int i = 0; i < NUM_JUGADORES; i++) {
                if (posiciones[i] == posicion_minima) {
                    // Los ganadores reciben una parte proporcional del monto total apostado
                    saldos[i] += (MONTO_APUESTA * (NUM_JUGADORES - ganadores)) / ganadores;
                } else {
                    // Los perdedores pierden el monto de la apuesta
                    saldos[i] -= MONTO_APUESTA;
                }
            }
        }

        // Mostrar los ganadores de la ronda
        if (ganadores > 0 && ganadores < NUM_JUGADORES) {
            printf("Ganadores de la ronda: ");
            for (int i = 0; i < NUM_JUGADORES; i++) {
                if (posiciones[i] == posicion_minima) {
                    printf("Jugador %d ", i + 1);
                }
            }
            printf("\n");
        }

        // Mostrar los saldos actualizados de los jugadores
        for (int i = 0; i < NUM_JUGADORES; i++) {
            printf("Saldo del Jugador %d: Gs. %d\n", i + 1, saldos[i]);
        }
    }

    return 0;
}
