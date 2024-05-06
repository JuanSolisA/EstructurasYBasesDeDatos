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

    do
    {
        printf("Ejercicio de procesamiento de archivos empleados.csv\n");
        printf("1. Mostrar el archivo de texto\n");
        printf("2. Generar un archivo binario con empleados del sector de ventas\n");
        printf("3. Generar informes separados en archivos de texto\n");
        printf("0. Salir\n");
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
        case 0:
            printf("Saliendo del programa\n");
            break;
        default:
            printf("Opcion no valida\n");
            break;
        }

    } while (opcion != 0);

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
    printf("Num de Empleado\tEmpleado\tPuesto\tSalario\tSector\n\n");

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
        perror("Error al abrir los archivos. \n");
        return;
    }

    while (fscanf(archivoCSV, "%d;%[^;];%[^;];%f;%[^\n]\n", &empleado.id, empleado.nombre, empleado.cargo, &empleado.salario, empleado.sector) != EOF)
    {
        printf("ID: %d, Nombre: %s, Cargo: %s, Salario: %.2f, Sector: %s\n", empleado.id, empleado.nombre, empleado.cargo, empleado.salario, empleado.sector);
        if (strcmp(empleado.sector, "VENTAS") == 0)
        {
            fwrite(&empleado, sizeof(Empleado), 1, archivoBinario);
        }
    }
    fclose(archivoCSV);
    fclose(archivoBinario);

    printf("Archivo binario generado correctamente\n");
}

void generarInformesSeparados()
{
    FILE *archivoCSV, *archivoEmpleado, *archivoOtro;
    Empleado empleado;

    // Apertura de archivos
    archivoCSV = fopen("empleados.csv", "r");
    archivoEmpleado = fopen("empleados.txt", "w");
    archivoOtro = fopen("otro.txt", "w");

    if (archivoCSV == NULL || archivoEmpleado == NULL || archivoOtro == NULL)
    {
        perror("Error al abrir los archivos. \n");
        return;
    }

    fprintf(archivoEmpleado, "Empleados con oficio 'Empleado':\n");
    fprintf(archivoOtro, "Otros empleados:\n");

    while (fscanf(archivoCSV, "%d;%[^;];%[^;];%f;%[^\n]\n", &empleado.id, empleado.nombre, empleado.cargo, &empleado.salario, empleado.sector) != EOF)
    {
        if (strcmp(empleado.cargo, "EMPLEADO") == 0)
        {
            fprintf(archivoEmpleado, "ID: %d, Nombre: %s, Cargo: %s, Salario: %.2f, Sector: %s\n", empleado.id, empleado.nombre, empleado.cargo, empleado.salario, empleado.sector);
        }
        else
        {
            fprintf(archivoOtro, "ID: %d, Nombre: %s, Cargo: %s, Salario: %.2f, Sector: %s\n", empleado.id, empleado.nombre, empleado.cargo, empleado.salario, empleado.sector);
        }
    }

    fclose(archivoCSV);
    fclose(archivoEmpleado);
    fclose(archivoOtro);

    printf("Informes generados correctamente\n");
}