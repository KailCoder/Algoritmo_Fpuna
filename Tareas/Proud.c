#include <stdio.h>
// Este programa calcula la cantidad de baldes de pintura que se deben comprar para pintar una superficie rectangular
// Solicita al usuario que ingrese el ancho y alto de la superficie, y muestra la cantidad de baldes necesarios de entre 4 tipos de baldes
int main() {
    float ancho, alto, area, litros_necesarios;
    int baldes_necesarios1;
    int baldes_necesarios2;
    int baldes_necesarios3;
    int baldes_necesarios4;
    const float rendimiento_por_litro = 12.0; // m2 por litro
    const float capacidad1 =18.0; // litros por balde
    const float capacidad2 =12.0; // litros por balde
    const float capacidad3 =3.6; // litros por balde
    const float capacidad4 =1.5; // litros por balde
    // Solicitar al usuario que ingrese el ancho y alto de la superficie a pintar
    printf("Ingrese el ancho de la superficie a pintar (en metros):  \n");
    scanf("%f", &ancho);
    printf("Ingrese el alto de la superficie a pintar (en metros): \n");
    scanf("%f", &alto);
    // Calcular el área de la superficie
    area = ancho * alto;
    // Calcular la cantidad de litros de pintura necesarios             
    litros_necesarios = area / rendimiento_por_litro;
    //Dado que existen baldes de 18, 12, 3.6 y 1.5 litros. Se debe calcular la cantidad de baldes necesarios, teniendo eso en cuenta.
    litros_necesarios -= (baldes_necesarios1 = (int) (litros_necesarios / capacidad1)) * capacidad1;
    litros_necesarios -= (baldes_necesarios2 = (int) (litros_necesarios / capacidad2)) * capacidad2; 
    litros_necesarios -= (baldes_necesarios3 = (int) (litros_necesarios / capacidad3)) * capacidad3;
    litros_necesarios -= (baldes_necesarios4 = (int) (litros_necesarios / capacidad4)) * capacidad4;
    //Si la cantidad restante de litros es mayor a 0, se debe agregar un balde más.
    if (litros_necesarios > 0) {
        baldes_necesarios4++;
    }
    printf("La cantidad de baldes de pintura que se debe comprar es: %d de 18 litros, %d de 12 litros, %d de 3.6 litros y %d de 1.5 litros\n", baldes_necesarios1, baldes_necesarios2, baldes_necesarios3, baldes_necesarios4);
    // Los integrantes del grupo para el trabajo practico son:
    // - Julio Cesar Ojeda Martinez
    return 0;
}   