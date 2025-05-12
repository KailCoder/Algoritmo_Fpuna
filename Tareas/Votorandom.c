#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void calcularModa(int conteo[], int *moda, int *frecuenciaModa) {
    *moda = 1;
    *frecuenciaModa = conteo[0];
    for (int i = 1; i < 4; i++) {
        if (conteo[i] > *frecuenciaModa) {
            *frecuenciaModa = conteo[i];
            *moda = i + 1;
        }
    }
}

int main() {
    int n;
    printf("Ingrese la cantidad de numeros aleatorios a generar: ");
    scanf("%d", &n);

    // Inicializar el generador de números aleatorios
    srand(time(NULL));

    // Arreglo para contar las apariciones de los números 1, 2, 3 y 4
    int conteo[4] = {0, 0, 0, 0};

    // Generar números aleatorios y contar las apariciones
    printf("Numeros generados: ");
    for (int i = 0; i < n; i++) {
        int numero = (rand() % 4) + 1; // Genera un número entre 1 y 4
        printf("%d ", numero);
        conteo[numero - 1]++;
    }
    printf("\n");

    // Mostrar el conteo de cada número
    for (int i = 0; i < 4; i++) {
        printf("El numero %d aparece %d veces.\n", i + 1, conteo[i]);
    }

    // Calcular la moda
    int moda, frecuenciaModa;
    calcularModa(conteo, &moda, &frecuenciaModa);
    printf("La moda es el numero %d con %d apariciones.\n", moda, frecuenciaModa);

    return 0;
}