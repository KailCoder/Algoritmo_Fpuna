#include <stdio.h> // Incluyo la libreria stdio.h para poder utilizar las funciones de entrada y salida
#include <stdlib.h> // Incluyo la libreria stdlib.h para poder utilizar las funciones de generacion de numeros aleatorios
#include <time.h> // Incluyo la libreria time.h para poder utilizar la funcion time
// Este programa genera un numero aleatorio entre 0 y un limite, y le pide al usuario que adivine el numero secreto
// El usuario tiene un numero limitado de intentos para adivinar el numero secreto
// El programa le indica si el numero ingresado es mayor o menor al numero secreto
// Utilice las librerías stdlin.h y time.h para generar el numero aleatorio
int main () {
    int seleccion, intentos; // Variables para el nivel de dificultad y la cantidad de intentos
    int limit, win_number, guess; // Variables para el limite, el numero secreto y el numero ingresado por el usuario
    printf("Bienvenido al juego de adivinar el numero secreto\n");
    // Solicitar al usuario que elija el nivel de dificultad
    printf("Elige el nivel de dificultad\n");
    printf("1. Facil\n");
    printf("2. Medio\n");
    printf("3. Dificil\n");
    scanf("%d", &seleccion);
    // Dependiendo del nivel de dificultad, se establece el limite y la cantidad de intentos
    switch(seleccion) {
        case 1:
            limit=10;
            intentos=3;
            printf("Se ha seleccionado el nivel Facil\n");
            break;
        case 2:
            limit=50;
            intentos=5;
            printf("Se ha seleccionado el nivel Medio\n");
            break;
        case 3:
            limit=100;
            intentos=5;
            printf("Se ha seleccionado el nivel Dificil\n");
            break;
        default:
            printf("Opcion no valida\n");
            return 1;
    }
    // Generar un numero aleatorio entre 0 y el limite
    srand(time(NULL));
    win_number=rand()%(limit+1);
    // Se especifica el rango de numeros y la cantidad de intentos
    printf("Se ha generado un numero entre 0 y %d\n", limit);
    printf("Tienes %d intentos para adivinarlo\n", intentos);
    // Se le pide al usuario que adivine el numero secreto
    // Se le indica si el numero ingresado es mayor o menor al numero secreto
    while(intentos>0) {
    // A pesar de que aun no tocamos el tema de funciones repetitivas, me tome el atrevimiento de utilizar un bucle while 
    // para que el usuario pueda ingresar un numero hasta que adivine el numero secreto o se quede sin intentos.
        printf("Ingrese un numero: ");
        scanf("%d", &guess);
        if(guess==win_number) {
            printf("Felicidades, has adivinado el numero secreto\n");
            return 0;
        } else {
            printf("Numero incorrecto\n");
            if (guess<win_number) {
                printf("El numero secreto es mayor\n");
            } else {
                printf("El numero secreto es menor\n");
            }
            intentos--;
            printf("Te quedan %d intentos\n", intentos);
        }
    }
    // Los integrantes del grupo para el trabajo practico son:
    // - Julio Cesar Ojeda Martinez
// Este programa calcula la cantidad de baldes de pintura que se deben comprar para pintar una superficie rectangular
// Solicita al usuario que ingrese el ancho y alto de la superficie, y muestra la cantidad de baldes necesarios de entre 4 tipos de baldes
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
