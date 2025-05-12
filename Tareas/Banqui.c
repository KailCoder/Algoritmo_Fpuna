#include <stdio.h>
#include <string.h>

// Definimos los límites máximos de clientes y movimientos por cuenta.
#define MAX_CLIENTES 10
#define MAX_MOVIMIENTOS 10

// Estructura para representar un movimiento en una cuenta bancaria.
typedef struct {
    char tipo[10]; // Tipo de movimiento: "Depósito" o "Extracción".
    double monto;  // Monto del movimiento.
    char fecha[11]; // Fecha del movimiento en formato "DD/MM/AAAA".
} Movimiento;

// Estructura para representar una cuenta bancaria.
typedef struct {
    int numero; // Número único de la cuenta.
    char denominacion[20]; // Tipo de cuenta: "Cuenta Corriente" o "Caja de Ahorro".
    double saldo; // Saldo actual de la cuenta.
    Movimiento movimientos[MAX_MOVIMIENTOS]; // Lista de movimientos realizados.
    int cantidadMovimientos; // Cantidad de movimientos registrados.
} Cuenta;

// Estructura para representar un cliente del banco.
typedef struct {
    char nombre[50]; // Nombre del cliente.
    char apellido[50]; // Apellido del cliente.
    char documento[20]; // Documento de identidad del cliente.
    char telefono[15]; // Teléfono del cliente.
    Cuenta cuenta; // Cuenta asociada al cliente.
    int tieneCuenta; // Indicador de si el cliente tiene una cuenta (1 = Sí, 0 = No).
} Cliente;

// Arreglo global para almacenar los clientes registrados.
Cliente clientes[MAX_CLIENTES];
int cantidadClientes = 0; // Contador de clientes registrados.

// Función para registrar un nuevo cliente.
void registrarCliente() {
    if (cantidadClientes >= MAX_CLIENTES) { // Verifica si se alcanzó el límite de clientes.
        printf("No se pueden registrar más clientes.\n");
        return;
    }
    Cliente nuevoCliente;
    printf("Ingrese el nombre: ");
    scanf("%s", nuevoCliente.nombre); // Solicita el nombre del cliente.
    printf("Ingrese el apellido: ");
    scanf("%s", nuevoCliente.apellido); // Solicita el apellido del cliente.
    printf("Ingrese el documento: ");
    scanf("%s", nuevoCliente.documento); // Solicita el documento del cliente.
    printf("Ingrese el teléfono: ");
    scanf("%s", nuevoCliente.telefono); // Solicita el teléfono del cliente.
    nuevoCliente.tieneCuenta = 0; // Inicializa sin cuenta asociada.
    clientes[cantidadClientes++] = nuevoCliente; // Agrega el cliente al arreglo.
    printf("Cliente registrado con éxito.\n");
}

// Función para registrar una cuenta para un cliente existente.
void registrarCuenta() {
    char documento[20];
    printf("Ingrese el documento del cliente: ");
    scanf("%s", documento); // Solicita el documento del cliente.
    for (int i = 0; i < cantidadClientes; i++) {
        if (strcmp(clientes[i].documento, documento) == 0) { // Busca al cliente por documento.
            if (clientes[i].tieneCuenta) { // Verifica si ya tiene una cuenta.
                printf("El cliente ya tiene una cuenta registrada.\n");
                return;
            }
            printf("Ingrese el número de cuenta: ");
            scanf("%d", &clientes[i].cuenta.numero); // Solicita el número de cuenta.
            printf("Ingrese la denominación (Cuenta Corriente/Caja de Ahorro): "); //Escribir el tipo de cuenta sin espacios.
            scanf("%s", clientes[i].cuenta.denominacion); // Solicita el tipo de cuenta.
            clientes[i].cuenta.saldo = 0; // Inicializa el saldo en 0.
            clientes[i].cuenta.cantidadMovimientos = 0; // Inicializa sin movimientos.
            clientes[i].tieneCuenta = 1; // Marca que el cliente tiene una cuenta.
            printf("Cuenta registrada con éxito.\n");
            return;
        }
    }
    printf("Cliente no encontrado.\n");
}

// Función para registrar un movimiento en la cuenta de un cliente.
void registrarMovimiento() {
    char documento[20];
    printf("Ingrese el documento del cliente: ");
    scanf("%s", documento); // Solicita el documento del cliente.
    for (int i = 0; i < cantidadClientes; i++) {
        if (strcmp(clientes[i].documento, documento) == 0) { // Busca al cliente por documento.
            if (!clientes[i].tieneCuenta) { // Verifica si tiene una cuenta.
                printf("El cliente no tiene una cuenta registrada.\n");
                return;
            }
            if (clientes[i].cuenta.cantidadMovimientos >= MAX_MOVIMIENTOS) { // Verifica el límite de movimientos.
                printf("La cuenta ha alcanzado el límite de movimientos.\n");
                return;
            }
            Movimiento nuevoMovimiento;
            printf("Ingrese el tipo de movimiento (Depósito/Extracción): ");
            scanf("%s", nuevoMovimiento.tipo); // Solicita el tipo de movimiento.
            printf("Ingrese el monto: ");
            scanf("%lf", &nuevoMovimiento.monto); // Solicita el monto del movimiento.
            printf("Ingrese la fecha (DD/MM/AAAA): ");
            scanf("%s", nuevoMovimiento.fecha); // Solicita la fecha del movimiento.

            if (strcmp(nuevoMovimiento.tipo, "Depósito") == 0) { // Si es un depósito.
                clientes[i].cuenta.saldo += nuevoMovimiento.monto; // Incrementa el saldo.
            } else if (strcmp(nuevoMovimiento.tipo, "Extracción") == 0) { // Si es una extracción.
                if (clientes[i].cuenta.saldo < nuevoMovimiento.monto) { // Verifica saldo suficiente.
                    printf("Saldo insuficiente.\n");
                    return;
                }
                clientes[i].cuenta.saldo -= nuevoMovimiento.monto; // Reduce el saldo.
            } else {
                printf("Tipo de movimiento inválido.\n");
                return;
            }

            // Agrega el movimiento a la lista de movimientos.
            clientes[i].cuenta.movimientos[clientes[i].cuenta.cantidadMovimientos++] = nuevoMovimiento;
            printf("Movimiento registrado con éxito.\n");
            return;
        }
    }
    printf("Cliente no encontrado.\n");
}

// Función para imprimir el saldo de la cuenta de un cliente.
void imprimirSaldo() {
    char documento[20];
    printf("Ingrese el documento del cliente: ");
    scanf("%s", documento); // Solicita el documento del cliente.
    for (int i = 0; i < cantidadClientes; i++) {
        if (strcmp(clientes[i].documento, documento) == 0) { // Busca al cliente por documento.
            if (!clientes[i].tieneCuenta) { // Verifica si tiene una cuenta.
                printf("El cliente no tiene una cuenta registrada.\n");
                return;
            }
            printf("Saldo actual: %.2f\n", clientes[i].cuenta.saldo); // Imprime el saldo actual.
            return;
        }
    }
    printf("Cliente no encontrado.\n");
}

// Función para imprimir el extracto de movimientos de la cuenta de un cliente.
void imprimirExtracto() {
    char documento[20];
    printf("Ingrese el documento del cliente: ");
    scanf("%s", documento); // Solicita el documento del cliente.
    for (int i = 0; i < cantidadClientes; i++) {
        if (strcmp(clientes[i].documento, documento) == 0) { // Busca al cliente por documento.
            if (!clientes[i].tieneCuenta) { // Verifica si tiene una cuenta.
                printf("El cliente no tiene una cuenta registrada.\n");
                return;
            }
            printf("Extracto de cuenta:\n");
            for (int j = 0; j < clientes[i].cuenta.cantidadMovimientos; j++) { // Recorre los movimientos.
                Movimiento m = clientes[i].cuenta.movimientos[j];
                printf("Tipo: %s, Monto: %.2f, Fecha: %s\n", m.tipo, m.monto, m.fecha); // Imprime cada movimiento.
            }
            return;
        }
    }
    printf("Cliente no encontrado.\n");
}

// Función principal que muestra el menú y permite interactuar con el sistema.
int main() {
    int opcion;
    do {
        printf("\n--- Menú ---\n");
        printf("1. Registrar cliente\n");
        printf("2. Registrar cuenta\n");
        printf("3. Registrar movimiento\n");
        printf("4. Imprimir saldo\n");
        printf("5. Imprimir extracto de cuenta\n");
        printf("6. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion); // Solicita la opción del usuario.

        switch (opcion) {
            case 1: registrarCliente(); break; // Llama a la función para registrar un cliente.
            case 2: registrarCuenta(); break; // Llama a la función para registrar una cuenta.
            case 3: registrarMovimiento(); break; // Llama a la función para registrar un movimiento.
            case 4: imprimirSaldo(); break; // Llama a la función para imprimir el saldo.
            case 5: imprimirExtracto(); break; // Llama a la función para imprimir el extracto.
            case 6: printf("Saliendo del programa.\n"); break; // Finaliza el programa.
            default: printf("Opción inválida.\n"); break; // Maneja opciones inválidas.
        }
    } while (opcion != 6); // Repite hasta que el usuario elija salir.
//Este trabajo fue realizado por: Julio Cesar Ojeda Martinez, CI:5297200.
    return 0;
}
