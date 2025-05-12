// Este programa procesa datos de alumnos, exámenes y notas para generar estadísticas y calificaciones detalladas.
// Se utilizan estructuras para organizar los datos y funciones para realizar operaciones específicas sobre ellos.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUMNOS 100 // Máximo número de alumnos
#define MAX_EXAMENES 10 // Máximo número de tipos de exámenes
#define MAX_NOTAS 1000  // Máximo número de notas

// Estructura para almacenar información de un alumno
// Incluye un código único, el nombre del alumno y la carrera que cursa.
// Esto permite identificar a cada alumno de manera única y asociar sus datos académicos.
typedef struct {
    int codigo; // Código único del alumno, utilizado como identificador principal.
    char nombre[100]; // Nombre completo del alumno.
    char carrera[100]; // Carrera que cursa el alumno.
} Alumno;

// Estructura para almacenar información de un examen
// Incluye un código único y una descripción del examen.
// Esto permite identificar los diferentes tipos de exámenes (parciales, finales, etc.).
typedef struct {
    int codigo; // Código único del examen, utilizado para asociar notas a un tipo de examen específico.
    char descripcion[50]; // Descripción breve del examen (por ejemplo, "Primer Parcial").
} Examen;

// Estructura para almacenar una nota específica
// Relaciona un alumno con un examen y el puntaje obtenido.
// Esto permite registrar y procesar las calificaciones de los alumnos.
typedef struct {
    int codigoAlumno; // Código del alumno asociado a esta nota.
    int codigoExamen; // Código del examen asociado a esta nota.
    int puntaje; // Puntaje obtenido en el examen (debe estar entre 0 y 100).
} Nota;

// Estructura para almacenar resultados procesados de un alumno
// Incluye información como el promedio ponderado, la nota final y el estado de aprobación.
// Esto permite generar reportes detallados sobre el desempeño de los alumnos.
typedef struct {
    int codigoAlumno; // Código del alumno.
    float promedioPonderado; // Promedio ponderado de las notas de los parciales.
    int notaFinalRendida; // Nota del examen final rendido (si aplica).
    float notaFinal; // Nota final calculada combinando el promedio y el examen final.
    int calificacion; // Calificación final en una escala de 1 a 5.
    int aprobo; // Estado de aprobación: 0 = no aprobó, 1 = aprobó en primer final, 2 = aprobó en segundo final.
} ResultadoAlumno;

// Función para leer datos de alumnos desde un archivo
// El archivo debe tener el formato: codigo,nombre,carrera (una línea por alumno).
// Los datos se almacenan en el arreglo 'alumnos' y se actualiza la cantidad de alumnos leídos.
int leerAlumnos(const char *nombreArchivo, Alumno alumnos[], int *cantidad) {
    FILE *archivo = fopen(nombreArchivo, "r"); // Abrir el archivo en modo lectura.
    if (!archivo) {
        // Si no se puede abrir el archivo, se muestra un mensaje de error y se retorna 0.
        printf("No se pudo abrir el archivo %s\n", nombreArchivo);
        return 0;
    }

    *cantidad = 0; // Inicializar la cantidad de alumnos leídos en 0.
    // Leer cada línea del archivo y extraer los datos del alumno.
    while (fscanf(archivo, "%d,%99[^,],%99[^\n]",
                  &alumnos[*cantidad].codigo,
                  alumnos[*cantidad].nombre,
                  alumnos[*cantidad].carrera) == 3) {
        (*cantidad)++; // Incrementar el contador de alumnos leídos.
    }
    printf("Se leyeron %d alumnos.\n", *cantidad); // Mostrar la cantidad de alumnos leídos.
    fclose(archivo); // Cerrar el archivo.
    return 1; // Retornar 1 para indicar éxito.
}

// Función para leer datos de exámenes desde un archivo
// El archivo debe tener el formato: codigo,descripcion (una línea por examen).
// Los datos se almacenan en el arreglo 'examenes' y se actualiza la cantidad de exámenes leídos.
int leerExamenes(const char *nombreArchivo, Examen examenes[], int *cantidad) {
    FILE *archivo = fopen(nombreArchivo, "r"); // Abrir el archivo en modo lectura.
    if (!archivo) {
        // Si no se puede abrir el archivo, se muestra un mensaje de error y se retorna 0.
        printf("No se pudo abrir el archivo %s\n", nombreArchivo);
        return 0;
    }

    *cantidad = 0; // Inicializar la cantidad de exámenes leídos en 0.
    // Leer cada línea del archivo y extraer los datos del examen.
    while (fscanf(archivo, "%d,%49[^\n]",
                  &examenes[*cantidad].codigo,
                  examenes[*cantidad].descripcion) == 2) {
        (*cantidad)++; // Incrementar el contador de exámenes leídos.
    }

    fclose(archivo); // Cerrar el archivo.
    return 1; // Retornar 1 para indicar éxito.
}

// Función para leer datos de notas desde un archivo
// El archivo debe tener el formato: codigoAlumno,codigoExamen,puntaje (una línea por nota).
// Los datos se almacenan en el arreglo 'notas' y se actualiza la cantidad de notas leídas.
// También se registran las líneas con errores (notas fuera de rango) en 'registrosInvalidos'.
int leerNotas(const char *nombreArchivo, Nota notas[], int *cantidad, int registrosInvalidos[], int *numInvalidos) {
    FILE *archivo = fopen(nombreArchivo, "r"); // Abrir el archivo en modo lectura.
    if (!archivo) {
        // Si no se puede abrir el archivo, se muestra un mensaje de error y se retorna 0.
        printf("No se pudo abrir el archivo %s\n", nombreArchivo);
        return 0;
    }

    *cantidad = 0; // Inicializar la cantidad de notas leídas en 0.
    *numInvalidos = 0; // Inicializar el contador de registros inválidos en 0.
    int linea = 1; // Contador de líneas para identificar errores.
    // Leer cada línea del archivo y extraer los datos de la nota.
    while (fscanf(archivo, "%d,%d,%d",
                  &notas[*cantidad].codigoAlumno,
                  &notas[*cantidad].codigoExamen,
                  &notas[*cantidad].puntaje) == 3) {

        if (notas[*cantidad].puntaje < 0 || notas[*cantidad].puntaje > 100) {
            // Si el puntaje está fuera del rango válido (0-100), se registra como inválido.
            registrosInvalidos[*numInvalidos] = linea;
            (*numInvalidos)++;
        }
        (*cantidad)++; // Incrementar el contador de notas leídas.
        linea++; // Incrementar el contador de líneas.
    }

    fclose(archivo); // Cerrar el archivo.
    return 1; // Retornar 1 para indicar éxito.
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
    if (notaFinal < 60 || notaExamenFinal < 50) return 1; // Si la nota final es menor a 60 o el examen final es menor a 50, se considera un aplazo.
    else if (notaFinal > 90) return 5;  
    else if (notaFinal > 80) return 4; 
    else if (notaFinal > 70) return 3; 
    else return 2; // Calificación mínima aprobatoria.
}

void generarArchivoCalificaciones(const char *nombreArchivo, ResultadoAlumno resultados[], int cantidad, Alumno alumnos[], int cantidadAlumnos, NotasAlumno resumen[]) {
    FILE *archivo = fopen(nombreArchivo, "w");

    if (archivo == NULL) {
        printf("Error al crear el archivo %s.\n", nombreArchivo);
        return;
    }

    // Encabezado principal
    fprintf(archivo, "Alumnos que aprobaron la materia:\n\n");

    // Primer Final
    fprintf(archivo, "Primer Final\n");
    fprintf(archivo, "Nombre Alumno    Prom Ponderado    Examen Final    Calificación\n");
    fprintf(archivo, "-----------------------------------------------------------\n");
    for (int i = 0; i < cantidad; i++) {
        if (resultados[i].aprobo == 1) {
            fprintf(archivo, "%-16s %-16.2f %-16d %-16d\n",
                    alumnos[i].nombre,
                    resultados[i].promedioPonderado,
                    resultados[i].notaFinalRendida,
                    resultados[i].calificacion);
        }
    }
    fprintf(archivo, "\n");

    // Segundo Final
    fprintf(archivo, "Segundo Final\n");
    fprintf(archivo, "Nombre Alumno    Prom Ponderado    Examen Final    Calificación\n");
    fprintf(archivo, "-----------------------------------------------------------\n");
    for (int i = 0; i < cantidad; i++) {
        if (resultados[i].aprobo == 2) {
            fprintf(archivo, "%-16s %-16.2f %-16d %-16d\n",
                    alumnos[i].nombre,
                    resultados[i].promedioPonderado,
                    resultados[i].notaFinalRendida,
                    resultados[i].calificacion);
        }
    }
    fprintf(archivo, "\n");

    // Alumnos que no aprobaron
    fprintf(archivo, "Alumnos que no aprobaron la materia:\n\n");
    fprintf(archivo, "Nombre Alumno    1er Parcial    2do Parcial    3er Parcial    1er Final    2do Final\n");
    fprintf(archivo, "----------------------------------------------------------------------------------\n");
    for (int i = 0; i < cantidad; i++) {
        if (resultados[i].aprobo == 0) {
            fprintf(archivo, "%-16s %-14d %-14d %-14d %-14d %-14d\n",
                    alumnos[i].nombre,
                    resumen[i].parcial1,
                    resumen[i].parcial2,
                    resumen[i].parcial3,
                    resumen[i].primerFinal,
                    resumen[i].segundoFinal);
        }
    }

    fclose(archivo);
    printf("Archivo de calificaciones generado correctamente: %s\n", nombreArchivo);
}

void generarArchivoEstadisticas(const char *nombreArchivo, ResultadoAlumno resultados[], int cantidad, Alumno alumnos[], int cantidadAlumnos) {
    int primerFinal = 0, segundoFinal = 0, noRindieron = 0;
    float sumaCalificaciones = 0;
    int alumnosValidos = cantidad; // Todos los alumnos en el resumen son válidos

    // Crear un mapa para contar aprobados por carrera
    typedef struct {
        char carrera[100];
        int aprobados;
    } CarreraAprobados;

    CarreraAprobados carreras[MAX_ALUMNOS];
    int cantidadCarreras = 0;

    for (int i = 0; i < cantidad; i++) {
        if (resultados[i].aprobo == 1)
            primerFinal++;
        else if (resultados[i].aprobo == 2)
            segundoFinal++;
        else if (resultados[i].notaFinalRendida == 0)
            noRindieron++;

        sumaCalificaciones += resultados[i].calificacion;

        // Contar aprobados por carrera
        if (resultados[i].aprobo > 0) {
            int encontrado = 0;
            for (int k = 0; k < cantidadCarreras; k++) {
                if (strcmp(carreras[k].carrera, alumnos[i].carrera) == 0) {
                    carreras[k].aprobados++;
                    encontrado = 1;
                    break;
                }
            }
            if (!encontrado) {
                strcpy(carreras[cantidadCarreras].carrera, alumnos[i].carrera);
                carreras[cantidadCarreras].aprobados = 1;
                cantidadCarreras++;
            }
        }
    }

    float porcentajeAprobados = (primerFinal + segundoFinal) * 100.0 / alumnosValidos;
    float porcentajeAplazados = 100.0 - porcentajeAprobados;
    float promedioGeneral = sumaCalificaciones / alumnosValidos;

    FILE *archivo = fopen(nombreArchivo, "w");
    if (!archivo) {
        printf("No se pudo crear el archivo %s\n", nombreArchivo);
        return;
    }

    fprintf(archivo, "■ Cantidad alumnos: %d\n", alumnosValidos);
    fprintf(archivo, "■ Cantidad de alumnos que aprobaron en primer final: %d\n", primerFinal);
    fprintf(archivo, "■ Cantidad de alumnos que aprobaron en segundo final: %d\n", segundoFinal);
    fprintf(archivo, "■ Cantidad de alumnos que no rindieron final, ni el primero, ni el segundo: %d\n", noRindieron);
    fprintf(archivo, "■ Porcentaje de alumnos aprobados: %.2f%%\n", porcentajeAprobados);
    fprintf(archivo, "■ Porcentaje de alumnos aplazados: %.2f%%\n", porcentajeAplazados);
    fprintf(archivo, "■ Promedio general de calificaciones de la materia: %.2f\n", promedioGeneral);

    fprintf(archivo, "\n■ Aprobados por carrera:\n");
    for (int i = 0; i < cantidadCarreras; i++) {
        fprintf(archivo, "  - %s: %d aprobados\n", carreras[i].carrera, carreras[i].aprobados);
    }

    fclose(archivo);
    printf("Archivo 'estadisticas.txt' generado correctamente.\n");
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

        // Validar si el alumno es válido antes de procesarlo
        int esValido = 0;
        for (int j = 0; j < cantidadAlumnos; j++) {
            if (alumnos[j].codigo == codigo) {
                esValido = 1;
                break;
            }
        }
        if (!esValido) continue; // Ignorar alumnos no válidos

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

    // Ajuste para establecer la nota final rendida en 0 si el alumno no rinde ningún final
    for (int i = 0; i < cantidadResumen; i++) {
        NotasAlumno n = resumen[i];
        ResultadoAlumno r;
        r.codigoAlumno = n.codigoAlumno;
        r.promedioPonderado = calcularPromedioPonderado(n);
        r.aprobo = 0;
        r.notaFinalRendida = 0; // Inicializar en 0 si no rinde ningún final
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
    generarArchivoCalificaciones("calificaciones.txt", resultados, cantidadResultados, alumnos, cantidadAlumnos, resumen);
    generarArchivoEstadisticas("estadisticas.txt", resultados, cantidadResultados, alumnos, cantidadAlumnos);
    printf("Archivos de calificaciones y estadísticas generados correctamente.\n");
    return 0;
}

