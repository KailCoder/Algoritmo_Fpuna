// Este programa procesa datos de alumnos, exámenes y notas para generar estadísticas y calificaciones.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUMNOS 100 // Máximo número de alumnos
#define MAX_EXAMENES 10 // Máximo número de tipos de exámenes
#define MAX_NOTAS 1000  // Máximo número de notas

// Estructura para almacenar información de un alumno
typedef struct {
    int codigo; // Código único del alumno
    char nombre[100]; // Nombre del alumno
    char carrera[100]; // Carrera del alumno
} Alumno;

// Estructura para almacenar información de un examen
typedef struct {
    int codigo; // Código único del examen
    char descripcion[50]; // Descripción del examen
} Examen;

// Estructura para almacenar una nota específica
typedef struct {
    int codigoAlumno; // Código del alumno asociado
    int codigoExamen; // Código del examen asociado
    int puntaje; // Puntaje obtenido
} Nota;

// Estructura para almacenar resultados procesados de un alumno
typedef struct {
    int codigoAlumno; // Código del alumno
    float promedioPonderado; // Promedio ponderado de las notas
    int notaFinalRendida; // Nota del examen final rendido
    float notaFinal; // Nota final calculada
    int calificacion; // Calificación final (1 a 5)
    int aprobo; // Estado de aprobación (0=no, 1=primer final, 2=segundo final)
} ResultadoAlumno;

// Función para leer datos de alumnos desde un archivo
int leerAlumnos(const char *nombreArchivo, Alumno alumnos[], int *cantidad) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (!archivo) {
        printf("No se pudo abrir el archivo %s\n", nombreArchivo);
        return 0;
    }

    *cantidad = 0;
    while (fscanf(archivo, "%d,%[^,],%[^\n]",
                  &alumnos[*cantidad].codigo,
                  alumnos[*cantidad].nombre,
                  alumnos[*cantidad].carrera) == 3) {
        (*cantidad)++;
    }

    fclose(archivo);
    return 1;
}

// Función para leer datos de exámenes desde un archivo
int leerExamenes(const char *nombreArchivo, Examen examenes[], int *cantidad) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (!archivo) {
        printf("No se pudo abrir el archivo %s\n", nombreArchivo);
        return 0;
    }

    *cantidad = 0;
    while (fscanf(archivo, "%d,%[^\n]",
                  &examenes[*cantidad].codigo,
                  examenes[*cantidad].descripcion) == 2) {
        (*cantidad)++;
    }

    fclose(archivo);
    return 1;
}

// Función para leer datos de notas desde un archivo
int leerNotas(const char *nombreArchivo, Nota notas[], int *cantidad, int registrosInvalidos[], int *numInvalidos) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (!archivo) {
        printf("No se pudo abrir el archivo %s\n", nombreArchivo);
        return 0;
    }

    *cantidad = 0;
    *numInvalidos = 0;
    int linea = 1;
    while (fscanf(archivo, "%d,%d,%d",
                  &notas[*cantidad].codigoAlumno,
                  &notas[*cantidad].codigoExamen,
                  &notas[*cantidad].puntaje) == 3) {

        if (notas[*cantidad].puntaje < 0 || notas[*cantidad].puntaje > 100) {
            registrosInvalidos[*numInvalidos] = linea;
            (*numInvalidos)++;
        }
        (*cantidad)++;
        linea++;
    }

    fclose(archivo);
    return 1;
}

typedef struct {
    int codigoAlumno;
    int parcial1; // código 1
    int parcial2; // código 2
    int parcial3; // código 3 (opcional)
    int primerFinal;  // código 4
    int segundoFinal; // código 5
    int tieneParcial1;
    int tieneParcial2;
    int tieneParcial3;
    int tienePrimerFinal;
    int tieneSegundoFinal;
} NotasAlumno;

int buscarIndiceAlumno(NotasAlumno resumen[], int cantidad, int codigoAlumno) {
    for (int i = 0; i < cantidad; i++) {
        if (resumen[i].codigoAlumno == codigoAlumno) return i;
    }
    return -1;
}

float calcularPromedioPonderado(NotasAlumno n) {
    int notas[3];
    int cantidad = 0;

    if (n.tieneParcial1) notas[cantidad++] = n.parcial1;
    if (n.tieneParcial2) notas[cantidad++] = n.parcial2;
    if (n.tieneParcial3) notas[cantidad++] = n.parcial3;

    if (cantidad == 2) {
        return (notas[0] + notas[1]) / 2.0;
    } else if (cantidad == 3) {
        // Buscar las 2 más altas
        for (int i = 0; i < 2; i++) {
            for (int j = i + 1; j < 3; j++) {
                if (notas[i] < notas[j]) {
                    int aux = notas[i];
                    notas[i] = notas[j];
                    notas[j] = aux;
                }
            }
        }
        return (notas[0] + notas[1]) / 2.0;
    }
    return 0; // no tiene suficientes notas
}

int puedeRendirFinal(float promedioPonderado, NotasAlumno n) {
    if (promedioPonderado >= 60 && n.tienePrimerFinal) return 1;
    if (promedioPonderado >= 50 && n.tieneSegundoFinal) return 2;
    return 0; // no puede rendir finales
}

float calcularNotaFinal(float promedioPonderado, int notaFinal) {
    return 0.4 * promedioPonderado + 0.6 * notaFinal;
}

int calcularCalificacion(float notaFinal, int notaExamenFinal) {
    if (notaFinal < 60 || notaExamenFinal < 50) return 1;
    else if (notaFinal > 90) return 5;
    else if (notaFinal > 80) return 4;
    else if (notaFinal > 70) return 3;
    else return 2;
}

void generarArchivoCalificaciones(const char *nombreArchivo, ResultadoAlumno resultados[], int cantidad) {
    FILE *archivo = fopen(nombreArchivo, "w");
    if (!archivo) {
        printf("No se pudo crear el archivo %s\n", nombreArchivo);
        return;
    }

    fprintf(archivo, "codigoAlumno,promedioPonderado,notaFinalRendida,notaFinal,calificacion\n");

    for (int i = 0; i < cantidad; i++) {
        fprintf(archivo, "%d,%.2f,%d,%.2f,%d\n",
            resultados[i].codigoAlumno,
            resultados[i].promedioPonderado,
            resultados[i].notaFinalRendida,
            resultados[i].notaFinal,
            resultados[i].calificacion);
    }

    fclose(archivo);
}

void generarArchivoEstadisticas(const char *nombreArchivo, ResultadoAlumno resultados[], int cantidad) {
    int primerFinal = 0, segundoFinal = 0, noAprobados = 0;

    for (int i = 0; i < cantidad; i++) {
        if (resultados[i].aprobo == 1)
            primerFinal++;
        else if (resultados[i].aprobo == 2)
            segundoFinal++;
        else
            noAprobados++;
    }

    FILE *archivo = fopen(nombreArchivo, "w");
    if (!archivo) {
        printf("No se pudo crear el archivo %s\n", nombreArchivo);
        return;
    }

    fprintf(archivo, "Total alumnos: %d\n", cantidad);
    fprintf(archivo, "Aprobados por primer final: %d (%.2f%%)\n", primerFinal, primerFinal * 100.0 / cantidad);
    fprintf(archivo, "Aprobados por segundo final: %d (%.2f%%)\n", segundoFinal, segundoFinal * 100.0 / cantidad);
    fprintf(archivo, "No aprobados: %d (%.2f%%)\n", noAprobados, noAprobados * 100.0 / cantidad);

    fclose(archivo);
}

int main() {
    Alumno alumnos[MAX_ALUMNOS]; // Arreglo para almacenar alumnos
    Examen examenes[MAX_EXAMENES]; // Arreglo para almacenar exámenes
    Nota notas[MAX_NOTAS]; // Arreglo para almacenar notas
    int cantidadAlumnos, cantidadExamenes, cantidadNotas;

    int registrosInvalidos[MAX_NOTAS]; // Arreglo para almacenar líneas con errores
    int numInvalidos; // Contador de registros inválidos

    // Leer datos desde los archivos
    if (!leerAlumnos("alumnos.txt", alumnos, &cantidadAlumnos)) return 1;
    if (!leerExamenes("tipo_examen.txt", examenes, &cantidadExamenes)) return 1;
    if (!leerNotas("notas.txt", notas, &cantidadNotas, registrosInvalidos, &numInvalidos)) return 1;

    // Validar si hay registros inválidos
    if (numInvalidos > 0) {
        printf("Los registros ");
        for (int i = 0; i < numInvalidos; i++) {
            printf("%d", registrosInvalidos[i]);
            if (i < numInvalidos - 1) printf(", ");
        }
        printf(" tienen notas fuera de rango. No se puede procesar el archivo.\n");
        return 1;
    }

    // Procesar datos de alumnos y generar estadísticas
    printf("Archivos cargados correctamente. Se puede procesar el archivo.\n");
    NotasAlumno resumen[MAX_ALUMNOS]; // Resumen de notas por alumno
    int cantidadResumen = 0;

    for (int i = 0; i < cantidadNotas; i++) {
        int codigo = notas[i].codigoAlumno;
        int examen = notas[i].codigoExamen;
        int puntaje = notas[i].puntaje;

        int idx = buscarIndiceAlumno(resumen, cantidadResumen, codigo);
        if (idx == -1) {
        // Nuevo alumno
        idx = cantidadResumen++;
        resumen[idx].codigoAlumno = codigo;
        resumen[idx].parcial1 = resumen[idx].parcial2 = resumen[idx].parcial3 = -1;
        resumen[idx].primerFinal = resumen[idx].segundoFinal = -1;
        resumen[idx].tieneParcial1 = resumen[idx].tieneParcial2 = resumen[idx].tieneParcial3 = 0;
        resumen[idx].tienePrimerFinal = resumen[idx].tieneSegundoFinal = 0;
    }

    // Asignar el puntaje según el examen
    switch (examen) {
        case 1:
            resumen[idx].parcial1 = puntaje;
            resumen[idx].tieneParcial1 = 1;
            break;
        case 2:
            resumen[idx].parcial2 = puntaje;
            resumen[idx].tieneParcial2 = 1;
            break;
        case 3:
            resumen[idx].parcial3 = puntaje;
            resumen[idx].tieneParcial3 = 1;
            break;
        case 4:
            resumen[idx].primerFinal = puntaje;
            resumen[idx].tienePrimerFinal = 1;
            break;
        case 5:
            resumen[idx].segundoFinal = puntaje;
            resumen[idx].tieneSegundoFinal = 1;
            break;
    }
    }
    for (int i = 0; i < cantidadResumen; i++) {
    printf("Alumno %d: P1=%d, P2=%d, PF=%d, SF=%d\n",
        resumen[i].codigoAlumno,
        resumen[i].parcial1,
        resumen[i].parcial2,
        resumen[i].primerFinal,
        resumen[i].segundoFinal);
}
    ResultadoAlumno resultados[MAX_ALUMNOS];
    int cantidadResultados = 0;

    for (int i = 0; i < cantidadResumen; i++) {
    NotasAlumno n = resumen[i];
    ResultadoAlumno r;
    r.codigoAlumno = n.codigoAlumno;
    r.promedioPonderado = calcularPromedioPonderado(n);
    r.aprobo = 0;
    r.notaFinalRendida = -1;
    r.notaFinal = 0;
    r.calificacion = 1;

    int derecho = puedeRendirFinal(r.promedioPonderado, n);

    if (derecho == 1) {
        r.notaFinalRendida = n.primerFinal;
        r.notaFinal = calcularNotaFinal(r.promedioPonderado, n.primerFinal);
        r.calificacion = calcularCalificacion(r.notaFinal, n.primerFinal);
        if (r.calificacion > 1) r.aprobo = 1;
    } else if (derecho == 2) {
        r.notaFinalRendida = n.segundoFinal;
        r.notaFinal = calcularNotaFinal(r.promedioPonderado, n.segundoFinal);
        r.calificacion = calcularCalificacion(r.notaFinal, n.segundoFinal);
        if (r.calificacion > 1) r.aprobo = 2;
    }
    
    resultados[cantidadResultados++] = r;
    }
    generarArchivoCalificaciones("calificaciones.txt", resultados, cantidadResultados);
    generarArchivoEstadisticas("estadisticas.txt", resultados, cantidadResultados);

    return 0;
}

