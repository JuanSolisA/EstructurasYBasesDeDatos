/* Empleado.csv
Opción 1: Mostrar el archivo de texto

Opción 2: Generar un archivo binario que contenga el nombre de los empleados y salario
 solo de aquellas que trabajen en el sector de "ventas".

 Opción 3: Generar un informe con los que tienen oficio="Empleado"  (empleados.txt)
 y otro con los demas empleados.    (otro.txt)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char nombre[50];
    char cargo[50];
    float salario;
    char sector[50];
} Empleado;

void mostrarArchivoTexto();
void generarArchivoBinarioVentas();
void generarInformesSeparados();

int main()
{
    int opcion;
    char continuar;

    do
    {
        printf("Ejercicio de procesamiento de archivos Empleado.csv\n");
        printf("1. Mostrar el archivo de texto\n");
        printf("2. Generar un archivo binario con empleados del sector de ventas\n");
        printf("3. Generar informes separados en archivos de texto\n");
        printf("Ingrese el numero de la opcion que desea ejecutar: ");

        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            mostrarArchivoTexto();
            break;
        case 2:
            generarArchivoBinarioVentas();
            break;
        case 3:
            generarInformesSeparados();
            break;
        default:
            printf("Opcion no valida\n");
            break;
        }

        printf("Desea realizar otra operación? (s/n): ");
        scanf(" %c", &continuar);

    } while (continuar == 's' || continuar == 'S');

    printf("Fin del programa\n");

    return 0;
}

void mostrarArchivoTexto()
{
    FILE *archivo;
    char linea[100];

    archivo = fopen("./empleados.csv", "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    printf("Contenido del archivo Empleado.cvs:\n");
    printf("Num de Empleado\tEmpleado\tPuesto\tSalario\tHobby\n\n");

    while (fgets(linea, sizeof(linea), archivo) != NULL)
    {
        char *token = strtok(linea, ";");
        while (token != NULL)
        {
            printf("%s\t", token);
            token = strtok(NULL, ";");
        }
        printf("\n");
    }

    fclose(archivo);
}

void generarArchivoBinarioVentas()
{
    FILE *archivoCSV, *archivoBinario;
    Empleado empleado;

    // Apertura de archivos
    archivoCSV = fopen("empleados.csv", "r");
    archivoBinario = fopen("empleadosVentas.bin", "wb");

    if (archivoCSV == NULL || archivoBinario == NULL)
    {
        printf("Error al abrir los archivos. \n");
        return;
    }
    while (fscanf(archivoCSV, "%d;%[^;];%[^;];%f;%[^;\n]", &empleado.id, empleado.nombre, empleado.cargo, &empleado.salario, empleado.sector) != EOF)
    {
        if (strcmp(empleado.sector, "VENTAS") == 0)
        {
            fwrite(&empleado, sizeof(Empleado), 1, archivoBinario);
        }
    }
}

void generarInformesSeparados() {}