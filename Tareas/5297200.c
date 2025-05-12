#include <stdio.h>
// Este programa calcula la cantidad de baldes de pintura que se deben comprar para pintar una superficie rectangular
// Solicita al usuario que ingrese el ancho y alto de la superficie, y muestra la cantidad de baldes necesarios
int main() {
    float ancho, alto, area, litros_necesarios;
    int baldes_necesarios;
    const float rendimiento_por_litro = 12.0; // m2 por litro
    const float capacidad_balde = 18.0; // litros por balde

    // Solicitar al usuario que ingrese el ancho y alto de la superficie a pintar
    printf("Ingrese el ancho de la superficie a pintar (en metros):  \n");
    scanf("%f", &ancho);
    printf("Ingrese el alto de la superficie a pintar (en metros): \n");
    scanf("%f", &alto);

    // Calcular el área de la superficie
    area = ancho * alto;

    // Calcular la cantidad de litros de pintura necesarios
    litros_necesarios = area / rendimiento_por_litro;

    // Calcular la cantidad de baldes necesarios, redondeando hacia arriba
    baldes_necesarios = (int)(litros_necesarios / capacidad_balde);
    if ((litros_necesarios / capacidad_balde) > baldes_necesarios) {
        baldes_necesarios++;
    }

    printf("La cantidad de baldes de pintura que se debe comprar es: %d\n", baldes_necesarios);
    // Los integrantes del grupo para el trabajo practico son:
    // - Julio Cesar Ojeda Martinez
    return 0;
}