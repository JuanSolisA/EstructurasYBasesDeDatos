/* ## Practica 3

1. Se ingresa un texto de varias líneas desde teclado y se guarda en un archivo de texto. Luego se muestra la cantidad de palabras que tiene cada línea.
2. Se ingresa un texto o frase desde consola y se muestra el texto original luego se muestra la cadena mas larga de cada renglón.
3. Teniendo en cuenta el ejercicio 2 de la practica 1 generar un archivo de texto que guarde los datos ingresados de los alumnos y luego se muestre contenido desde el archivo. Además, mostrar los alumnos por apellido en orden alfabético y guardar la información obtenida en otro archivo llamado ordenado.txt. Revisar el resultado obtenido
4. Teniendo en cuenta el ejercicio 3 de la Practica 1 realizar un menú con las siguientes opciones:
a) Ingreso de un empleado
b) Mostrar los empleados de la empresa
c) Mostrar los datos de un empleado en particular
d) Mostrar la cantidad de empleados por sector y generar un informe con esa información en un archivo de texto.
e) Mostrar el informe.
5. Leer un archivo de texto llamado empleado.txt y generar un archivo de texto con los empleados que cobran $5000 de sueldo y con un aumento de $1000. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ejercicio1() {
    // 1. Se ingresa un texto de varias líneas desde teclado y se guarda en un archivo de texto.
    // Luego se muestra la cantidad de palabras que tiene cada línea.
    FILE *archivo = fopen("texto.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    char texto[100];
    printf("Ingrese el texto (terminar con una línea vacía):\n");
    while (fgets(texto, sizeof(texto), stdin) != NULL && strcmp(texto, "\n") != 0) {
        fprintf(archivo, "%s", texto);
    }

    fclose(archivo);

    archivo = fopen("texto.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    char linea[100];
    int palabras;

    printf("Cantidad de palabras por línea:\n");
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        palabras = 0;
        char *token = strtok(linea, " ");
        while (token != NULL) {
            palabras++;
            token = strtok(NULL, " ");
        }
        printf("%d\n", palabras);
    }

    fclose(archivo);
}

void ejercicio2() {
    // 2. Se ingresa un texto o frase desde consola y se muestra el texto original
    // luego se muestra la cadena más larga de cada renglón.
    char texto[100];
    printf("Ingrese el texto:\n");
    fgets(texto, sizeof(texto), stdin);

    char *token = strtok(texto, "\n");
    while (token != NULL) {
        printf("Texto original: %s\n", token);

        char *palabra_mas_larga = "";
        char *palabra = strtok(token, " ");
        while (palabra != NULL) {
            if (strlen(palabra) > strlen(palabra_mas_larga)) {
                palabra_mas_larga = palabra;
            }
            palabra = strtok(NULL, " ");
        }

        printf("Cadena más larga: %s\n", palabra_mas_larga);

        token = strtok(NULL, "\n");
    }
}

void ejercicio3() {
    // 3. Teniendo en cuenta el ejercicio 2 de la practica 1 generar un archivo de texto
    // que guarde los datos ingresados de los alumnos y luego se muestre contenido desde el archivo.
    // Además, mostrar los alumnos por apellido en orden alfabético y guardar la información obtenida
    // en otro archivo llamado ordenado.txt. Revisar el resultado obtenido.
    FILE *archivo = fopen("alumnos.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    char nombre[50];
    char apellido[50];
    int edad;

    printf("Ingrese los datos de los alumnos (terminar con nombre vacío):\n");
    while (1) {
        printf("Nombre: ");
        fgets(nombre, sizeof(nombre), stdin);
        nombre[strcspn(nombre, "\n")] = '\0';

        if (strlen(nombre) == 0) {
            break;
        }

        printf("Apellido: ");
        fgets(apellido, sizeof(apellido), stdin);
        apellido[strcspn(apellido, "\n")] = '\0';

        printf("Edad: ");
        scanf("%d", &edad);
        getchar();

        fprintf(archivo, "%s %s %d\n", nombre, apellido, edad);
    }

    fclose(archivo);

    archivo = fopen("alumnos.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    char linea[100];
    char **alumnos = malloc(sizeof(char *));
    int cantidad_alumnos = 0;

    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        alumnos = realloc(alumnos, (cantidad_alumnos + 1) * sizeof(char *));
        alumnos[cantidad_alumnos] = malloc(strlen(linea) + 1);
        strcpy(alumnos[cantidad_alumnos], linea);
        cantidad_alumnos++;
    }

    fclose(archivo);

    // Ordenar los alumnos por apellido en orden alfabético
    for (int i = 0; i < cantidad_alumnos - 1; i++) {
        for (int j = 0; j < cantidad_alumnos - i - 1; j++) {
            char apellido1[50];
            char apellido2[50];
            sscanf(alumnos[j], "%*s %s", apellido1);
            sscanf(alumnos[j + 1], "%*s %s", apellido2);

            if (strcmp(apellido1, apellido2) > 0) {
                char *temp = alumnos[j];
                alumnos[j] = alumnos[j + 1];
                alumnos[j + 1] = temp;
            }
        }
    }

    archivo = fopen("ordenado.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    printf("Contenido del archivo:\n");
    for (int i = 0; i < cantidad_alumnos; i++) {
        printf("%s", alumnos[i]);
        fprintf(archivo, "%s", alumnos[i]);
    }

    fclose(archivo);

    // Liberar memoria
    for (int i = 0; i < cantidad_alumnos; i++) {
        free(alumnos[i]);
    }
    free(alumnos);
}

void ejercicio4() {
    // 4. Teniendo en cuenta el ejercicio 3 de la Practica 1 realizar un menú con las siguientes opciones:
    // a) Ingreso de un empleado
    // b) Mostrar los empleados de la empresa
    // c) Mostrar los datos de un empleado en particular
    // d) Mostrar la cantidad de empleados por sector y generar un informe con esa información en un archivo de texto.
    // e) Mostrar el informe.
    int opcion;
    int cantidad_empleados = 0;
    int cantidad_sectores = 0;

    struct Empleado {
        char nombre[50];
        char apellido[50];
        int sector;
    };

    struct Empleado *empleados = malloc(sizeof(struct Empleado));

    while (1) {
        printf("\nMenú:\n");
        printf("1. Ingreso de un empleado\n");
        printf("2. Mostrar los empleados de la empresa\n");
        printf("3. Mostrar los datos de un empleado en particular\n");
        printf("4. Mostrar la cantidad de empleados por sector y generar un informe\n");
        printf("5. Mostrar el informe\n");
        printf("6. Salir\n");
        printf("Ingrese una opción: ");
        scanf("%d", &opcion);
        getchar();

        if (opcion == 6) {
            break;
        }

        switch (opcion) {
            case 1: {
                cantidad_empleados++;
                empleados = realloc(empleados, cantidad_empleados * sizeof(struct Empleado));

                printf("Ingrese el nombre del empleado: ");
                fgets(empleados[cantidad_empleados - 1].nombre, sizeof(empleados[cantidad_empleados - 1].nombre), stdin);
                empleados[cantidad_empleados - 1].nombre[strcspn(empleados[cantidad_empleados - 1].nombre, "\n")] = '\0';

                printf("Ingrese el apellido del empleado: ");
                fgets(empleados[cantidad_empleados - 1].apellido, sizeof(empleados[cantidad_empleados - 1].apellido), stdin);
                empleados[cantidad_empleados - 1].apellido[strcspn(empleados[cantidad_empleados - 1].apellido, "\n")] = '\0';

                printf("Ingrese el sector del empleado: ");
                scanf("%d", &empleados[cantidad_empleados - 1].sector);
                getchar();

                if (empleados[cantidad_empleados - 1].sector > cantidad_sectores) {
                    cantidad_sectores = empleados[cantidad_empleados - 1].sector;
                }

                break;
            }
            case 2: {
                printf("Empleados de la empresa:\n");
                for (int i = 0; i < cantidad_empleados; i++) {
                    printf("Nombre: %s\n", empleados[i].nombre);
                    printf("Apellido: %s\n", empleados[i].apellido);
                    printf("Sector: %d\n", empleados[i].sector);
                    printf("\n");
                }
                break;
            }
            case 3: {
                int indice;
                printf("Ingrese el índice del empleado: ");
                scanf("%d", &indice);
                getchar();

                if (indice >= 0 && indice < cantidad_empleados) {
                    printf("Datos del empleado:\n");
                    printf("Nombre: %s\n", empleados[indice].nombre);
                    printf("Apellido: %s\n", empleados[indice].apellido);
                    printf("Sector: %d\n", empleados[indice].sector);
                } else {
                    printf("Índice inválido.\n");
                }

                break;
            }
            case 4: {
                int *cantidad_por_sector = calloc(cantidad_sectores + 1, sizeof(int));

                for (int i = 0; i < cantidad_empleados; i++) {
                    cantidad_por_sector[empleados[i].sector]++;
                }

                FILE *archivo = fopen("informe.txt", "w");
                if (archivo == NULL) {
                    printf("Error al abrir el archivo.\n");
                    return;
                }

                printf("Informe generado.\n");
                for (int i = 1; i <= cantidad_sectores; i++) {
                    printf("Cantidad de empleados en el sector %d: %d\n", i, cantidad_por_sector[i]);
                    fprintf(archivo, "Cantidad de empleados en el sector %d: %d\n", i, cantidad_por_sector[i]);
                }

                fclose(archivo);
                free(cantidad_por_sector);

                break;
            }
            case 5: {
                FILE *archivo = fopen("informe.txt", "r");
                if (archivo == NULL) {
                    printf("Error al abrir el archivo.\n");
                    return;
                }

                char linea[100];

                printf("Informe:\n");
                while (fgets(linea, sizeof(linea), archivo) != NULL) {
                    printf("%s", linea);
                }

                fclose(archivo);

                break;
            }
            default:
                printf("Opción inválida.\n");
                break;
        }
    }

    free(empleados);
}

void ejercicio5() {
    // 5. Leer un archivo de texto llamado empleado.txt y generar un archivo de texto
    // con los empleados que cobran $5000 de sueldo y con un aumento de $1000.
    FILE *archivo_entrada = fopen("empleado.txt", "r");
    if (archivo_entrada == NULL) {
        printf("Error al abrir el archivo de entrada.\n");
        return;
    }

    FILE *archivo_salida = fopen("aumento.txt", "w");
    if (archivo_salida == NULL) {
        printf("Error al abrir el archivo de salida.\n");
        fclose(archivo_entrada);
        return;
    }

    char linea[100];
    int sueldo;

    while (fgets(linea, sizeof(linea), archivo_entrada) != NULL) {
        sscanf(linea, "%*s %d", &sueldo);

        if (sueldo == 5000) {
            sueldo += 1000;
            fprintf(archivo_salida, "%s %d\n", linea, sueldo);
        }
    }

    fclose(archivo_entrada);
    fclose(archivo_salida);
}

int main() {
    int opcion;

    printf("Seleccione el ejercicio a ejecutar:\n");
    printf("1. Ejercicio 1\n");
    printf("2. Ejercicio 2\n");
    printf("3. Ejercicio 3\n");
    printf("4. Ejercicio 4\n");
    printf("5. Ejercicio 5\n");
    printf("Ingrese una opción: ");
    scanf("%d", &opcion);
    getchar();

    switch (opcion) {
        case 1:
            ejercicio1();
            break;
        case 2:
            ejercicio2();
            break;
        case 3:
            ejercicio3();
            break;
        case 4:
            ejercicio4();
            break;
        case 5:
            ejercicio5();
            break;
        default:
            printf("Opción inválida.\n");
            break;
    }

    return 0;
}