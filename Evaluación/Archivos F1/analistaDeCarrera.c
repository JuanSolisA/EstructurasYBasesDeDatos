#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nombreApp[15];
    char circuito[15];
    char version[5];
} Config;

typedef struct
{
    int numeroCorredor;
    char nombreCorredor[15];
    char apellidoCorredor[15];
    char scuderia[15];
} Corredor;

typedef struct
{
    int numVuelta;
    int numCorredor;
    float tiempo;
} Tiempos;

void cargarConfig();
void mostrarCorredores();
void mostrarTiempos();

int main()
{
    int opcion;
    do
    {
        system("cls");
        cargarConfig();
        printf("Menu de opciones\n");
        printf("1. Si desea mostrar los corredores\n");
        printf("2. Si desea mostrar el archivo con los tiempos\n");
        // printf("3. Si desea ...\n");
        // printf("4. Si desea ...\n");
        printf("0. Salir\n");

        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            system("cls");
            mostrarCorredores();
            system("pause");
            break;
        case 2:
            system("cls");
            mostrarTiempos();
            system("pause");
            break;
        case 3:
            break;
        case 4:
            break;
        case 0:
            printf("Saliendo del sistema...");
            break;
        default:
            printf("Ingrese una opcion valida");
            break;
        }
    } while (opcion != 0);

    return 0;
}

void cargarConfig()
{
    FILE *archivo;
    char texto[15];

    archivo = fopen("../config.txt", "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo config");
    }
    else
    {
        fgets(texto, 15, archivo);
        while (!feof(archivo))
        {
            puts(texto);
            fgets(texto, 15, archivo);
        }
        fclose(archivo);
    }
}

void mostrarCorredores()
{
    FILE *archivo;
    Corredor aux;

    archivo = fopen("../corredores.dat", "rb");
    if (archivo == NULL)
    {
        perror("Hubo un error al abrir el archivo corredores.dat\n");
    }
    else
    {

        printf("Lista de corredores\n");

        fread(&aux, sizeof(Corredor), 1, archivo);
        while (!feof(archivo))
        {
            printf("Num:|%d|, Nombre: %s. Apellido: %s. Scuderia: %s \n", aux.numeroCorredor, aux.nombreCorredor, aux.apellidoCorredor, aux.scuderia);
            fread(&aux, sizeof(Corredor), 1, archivo);
        }
        fclose(archivo);
    }
}

void mostrarTiempos()
{
    FILE *archivo;
    Tiempos aux;
    archivo = fopen("../tiempos2.dat", "rb");
    if (archivo == NULL)
    {
        printf("Hubo un error al abrir el archivo de los tiempos");
        return;
    }
    else
    {
        printf("Lista de tiempos\n");
        fread(&aux, sizeof(Tiempos), 1, archivo);
        while (!feof(archivo))
        {
            printf("Numero de vuenta: %d, Numero de corredor: %d, Tiempo: %.3f\n", aux.numVuelta, aux.numCorredor, aux.tiempo);
            fread(&aux, sizeof(Tiempos), 1, archivo);
        }
        fclose(archivo);
    }
}
