/* Realizar un programa resuelva lo siguiente
a) Una función que pida al usuario la cantidad de elementos a almacenar
b) Una función cargar, que cargue los N alumnos con sus respectivas notas
correspondientes a un curso de Programación. puede haber varias notas por
alumno(máximo 5 notas)
c) Una función que muestre los alumnos ordenados de mayor a menor por promedio
considerando solo las notas de 1er Parcial y 2do Parcial
d) Una función que muestre cuantos alumnos aprobaron considerando que para aprobar
la nota tiene que ser mayor a 6 inclusive en cada una de las dos instancias sea 1er
Parcial, 2do Parcial y/o Integral
e) Una función que muestre los datos de los alumnos cuyo inicial empiece con una letra
ingresada desde teclado

typedef char cadena [50];
typedef struct {
int legajo;
cadena apellido;
cadena nombre;
float nota [5];
} Alumno;
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char cadena[50];
typedef struct {
    int legajo;
    cadena apellido;
    cadena nombre;
    float nota[5];
} Alumno;

void pedirCantidadElementos(int *cantidad) {
    printf("Ingrese la cantidad de elementos a almacenar: ");
    scanf("%d", cantidad);
}

void cargarAlumnos(Alumno *alumnos, int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        printf("Ingrese el legajo del alumno %d: ", i + 1);
        scanf("%d", &alumnos[i].legajo);
        printf("Ingrese el apellido del alumno %d: ", i + 1);
        scanf("%s", alumnos[i].apellido);
        printf("Ingrese el nombre del alumno %d: ", i + 1);
        scanf("%s", alumnos[i].nombre);
        for (int j = 0; j < 5; j++) {
            printf("Ingrese la nota %d del alumno %d: ", j + 1, i + 1);
            scanf("%f", &alumnos[i].nota[j]);
        }
    }
}

float calcularPromedio(float nota1, float nota2) {
    return (nota1 + nota2) / 2;
}

void ordenarAlumnosPorPromedio(Alumno *alumnos, int cantidad) {
    for (int i = 0; i < cantidad - 1; i++) {
        for (int j = 0; j < cantidad - i - 1; j++) {
            float promedio1 = calcularPromedio(alumnos[j].nota[0], alumnos[j].nota[1]);
            float promedio2 = calcularPromedio(alumnos[j + 1].nota[0], alumnos[j + 1].nota[1]);
            if (promedio1 < promedio2) {
                Alumno temp = alumnos[j];
                alumnos[j] = alumnos[j + 1];
                alumnos[j + 1] = temp;
            }
        }
    }
}

int contarAlumnosAprobados(Alumno *alumnos, int cantidad) {
    int contador = 0;
    for (int i = 0; i < cantidad; i++) {
        float promedio = calcularPromedio(alumnos[i].nota[0], alumnos[i].nota[1]);
        if (promedio >= 6) {
            contador++;
        }
    }
    return contador;
}

void mostrarAlumnosPorInicial(Alumno *alumnos, int cantidad, char inicial) {
    for (int i = 0; i < cantidad; i++) {
        if (alumnos[i].apellido[0] == inicial || alumnos[i].nombre[0] == inicial) {
            printf("Legajo: %d\n", alumnos[i].legajo);
            printf("Apellido: %s\n", alumnos[i].apellido);
            printf("Nombre: %s\n", alumnos[i].nombre);
            printf("Notas: ");
            for (int j = 0; j < 5; j++) {
                printf("%.2f ", alumnos[i].nota[j]);
            }
            printf("\n");
        }
    }
}

int main() {
    int cantidad;
    pedirCantidadElementos(&cantidad);
    Alumno *alumnos = (Alumno *)malloc(cantidad * sizeof(Alumno));
    cargarAlumnos(alumnos, cantidad);
    ordenarAlumnosPorPromedio(alumnos, cantidad);
    printf("Alumnos ordenados por promedio:\n");
    for (int i = 0; i < cantidad; i++) {
        printf("Legajo: %d\n", alumnos[i].legajo);
        printf("Apellido: %s\n", alumnos[i].apellido);
        printf("Nombre: %s\n", alumnos[i].nombre);
        printf("Notas: ");
        for (int j = 0; j < 5; j++) {
            printf("%.2f ", alumnos[i].nota[j]);
        }
        printf("\n");
    }
    int aprobados = contarAlumnosAprobados(alumnos, cantidad);
    printf("Cantidad de alumnos aprobados: %d\n", aprobados);
    char inicial;
    printf("Ingrese una letra: ");
    scanf(" %c", &inicial);
    printf("Alumnos cuyo inicial empieza con '%c':\n", inicial);
    mostrarAlumnosPorInicial(alumnos, cantidad, inicial);
    free(alumnos);
    return 0;
}
