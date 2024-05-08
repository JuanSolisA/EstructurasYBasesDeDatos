/* Gestión de Empleados en una Empresa
   - Realizar un programa que permita realizar lo siguiente:
    a) Una función que permita cargar los empleados de una empresa hasta que se decida terminar el ingreso de datos con DNI igual a -1. Deberá validarse si el empleado ya fue ingresado o no.
    b) Realizar el ordenamiento de los empleados por orden alfabético.
    c) Mostrar los empleados por sector.

typedef char cadena[50];
typedef struct {
    int legajo;
    cadena apellido;
    cadena nombre;
    cadena sector;
} Empleado;

Para cada ejercicio, se proporcionan las estructuras de datos necesarias en lenguaje C. Puedes implementar las funciones y el código según tus necesidades.
 */

#include <stdio.h>
#include <string.h>

typedef char cadena[50];
typedef struct {
    int legajo;
    cadena apellido;
    cadena nombre;
    cadena sector;
} Empleado;

void cargarEmpleados(Empleado empleados[], int *numEmpleados);
void ordenarEmpleados(Empleado empleados[], int numEmpleados);
void mostrarEmpleadosPorSector(Empleado empleados[], int numEmpleados);

int main() {
    Empleado empleados[100];
    int numEmpleados = 0;

    cargarEmpleados(empleados, &numEmpleados);
    ordenarEmpleados(empleados, numEmpleados);
    mostrarEmpleadosPorSector(empleados, numEmpleados);

    return 0;
}

void cargarEmpleados(Empleado empleados[], int *numEmpleados) {
    int dni;
    int i = 0;

    printf("Ingrese el DNI del empleado (ingrese -1 para terminar): ");
    scanf("%d", &dni);

    while (dni != -1) {
        // Verificar si el empleado ya fue ingresado
        int empleadoExistente = 0;
        for (int j = 0; j < *numEmpleados; j++) {
            if (empleados[j].legajo == dni) {
                empleadoExistente = 1;
                break;
            }
        }

        if (empleadoExistente) {
            printf("El empleado con DNI %d ya fue ingresado.\n", dni);
        } else {
            empleados[i].legajo = dni;

            printf("Ingrese el apellido del empleado: ");
            scanf("%s", empleados[i].apellido);

            printf("Ingrese el nombre del empleado: ");
            scanf("%s", empleados[i].nombre);

            printf("Ingrese el sector del empleado: ");
            scanf("%s", empleados[i].sector);

            (*numEmpleados)++;
            i++;
        }

        printf("Ingrese el DNI del empleado (ingrese -1 para terminar): ");
        scanf("%d", &dni);
    }
}

void ordenarEmpleados(Empleado empleados[], int numEmpleados) {
    Empleado temp;
    //Ordenamiento por burbujeo o Buble Sort
    for (int i = 0; i < numEmpleados - 1; i++) {
        for (int j = 0; j < numEmpleados - i - 1; j++) {
            if (strcmp(empleados[j].apellido, empleados[j + 1].apellido) > 0) {
                temp = empleados[j];
                empleados[j] = empleados[j + 1];
                empleados[j + 1] = temp;
            }
        }
    }
}

void mostrarEmpleadosPorSector(Empleado empleados[], int numEmpleados) {
    cadena sectorBuscado;
    int empleadosEncontrados = 0;

    printf("Ingrese el sector a buscar: ");
    scanf("%s", sectorBuscado);

    printf("Empleados en el sector %s:\n", sectorBuscado);

    for (int i = 0; i < numEmpleados; i++) {
        if (strcmp(empleados[i].sector, sectorBuscado) == 0) {
            printf("Legajo: %d, Apellido: %s, Nombre: %s\n", empleados[i].legajo, empleados[i].apellido, empleados[i].nombre);
            empleadosEncontrados++;
        }
    }

    if (empleadosEncontrados == 0) {
        printf("No se encontraron empleados en el sector %s.\n", sectorBuscado);
    }
}