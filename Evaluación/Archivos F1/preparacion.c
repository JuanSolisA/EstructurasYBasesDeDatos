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

typedef struct
{
    int numCorredor;
    float tiempoTotal;
} Resultado;

void cargarConfig();
void mostrarCorredores();
void mostrarTiempos();

void mostrarTiemposCorredor(int);
void mostrarCorredoresOrdenados();
void mostrarMejorVuelta();
void mostrarGanador();
void generarCSV();

int main()
{
    int opcion, numeroCorredor;

    do
    {
        system("cls");
        cargarConfig();
        printf("Menu de opciones\n");
        printf("1. Si desea mostrar los corredores\n");
        printf("2. Si desea mostrar el archivo con los tiempos\n");
        printf("3. Si desea mostrar los tiempos de un corredor\n");
        printf("4. Si desea mostrar los corredores ordenados por numero\n");
        printf("5. Si desea mostrar el ganador de la carrera\n");
        printf("6. Si desea mostrar el ganador de la mejor vuelta\n");
        printf("7. Si desea generar un archivo CSV con los resultados\n");
        printf("0. Salir\n");

        scanf("%i", &opcion);

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
            system("cls");
            printf("Ingrese el numero de corredor para mostrar los tiempos: ");
            scanf("%d", &numeroCorredor);
            mostrarTiemposCorredor(numeroCorredor);
            system("pause");
            break;
        case 4:
            system("cls");
            mostrarCorredoresOrdenados();
            system("pause");
            break;
        case 5:
            system("cls");
            mostrarMejorVuelta();
            system("pause");
            break;
        case 6:
            system("cls");
            mostrarGanador();
            system("pause");
            break;
        case 7:
            system("cls");
            generarCSV();
            system("pause");
            break;
        case 0:
            printf("Saliendo del sistema...");
            break;
        default:
            printf("Ingrese una opcion valida.\n");
            system("pause");
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

void mostrarTiemposCorredor(int numeroCorredor)
{
    FILE *archivoTiempos = fopen("../tiempos2.dat", "rb");
    if (archivoTiempos == NULL)
    {
        printf("No se pudo abrir el archivo de tiempos.\n");
        return;
    }

    Tiempos tiempo;
    int corredorEncontrado = 0;

    while (fread(&tiempo, sizeof(Tiempos), 1, archivoTiempos))
    {
        if (tiempo.numCorredor == numeroCorredor)
        {
            printf("Vuelta: %d - Tiempo: %.3f\n", tiempo.numVuelta, tiempo.tiempo);
            corredorEncontrado = 1;
        }
    }

    if (!corredorEncontrado)
    {
        printf("No se encontro el corredor con el número: %d\n", numeroCorredor);
    }

    fclose(archivoTiempos);
}

void mostrarCorredoresOrdenados()
{
    FILE *archivoCorredores = fopen("../corredores.dat", "rb");
    if (archivoCorredores == NULL)
    {
        printf("No se pudo abrir el archivo de corredores.\n");
        return;
    }

    Corredor corredor;
    Corredor corredores[20];
    int cantidadCorredores = 0;

    while (fread(&corredor, sizeof(Corredor), 1, archivoCorredores))
    {
        corredores[cantidadCorredores] = corredor;
        cantidadCorredores++;
    }

    fclose(archivoCorredores);

    for (int i = 0; i < cantidadCorredores; i++)
    {
        for (int j = 0; j < cantidadCorredores - 1; j++)
        {
            if (corredores[j].numeroCorredor > corredores[j + 1].numeroCorredor)
            {
                Corredor aux = corredores[j];
                corredores[j] = corredores[j + 1];
                corredores[j + 1] = aux;
            }
        }
    }

    for (int i = 0; i < cantidadCorredores; i++)
    {
        printf("Num:|%d|, Nombre: %s. Apellido: %s. Scuderia: %s \n", corredores[i].numeroCorredor, corredores[i].nombreCorredor, corredores[i].apellidoCorredor, corredores[i].scuderia);
    }
}

void mostrarMejorVuelta()
{
    FILE *archivoTiempos = fopen("../tiempos2.dat", "rb");
    if (archivoTiempos == NULL)
    {
        printf("No se pudo abrir el archivo de tiempos.\n");
        return;
    }

    Tiempos tiempo;
    int corredorGanador = -1;
    float tiempoGanador = 9999;

    while (fread(&tiempo, sizeof(Tiempos), 1, archivoTiempos))
    {
        if (tiempo.tiempo < tiempoGanador)
        {
            tiempoGanador = tiempo.tiempo;
            corredorGanador = tiempo.numCorredor;
        }
    }

    fclose(archivoTiempos);

    if (corredorGanador != -1)
    {
        FILE *archivoCorredores = fopen("../corredores.dat", "rb");
        if (archivoCorredores == NULL)
        {
            printf("No se pudo abrir el archivo de corredores.\n");
            return;
        }

        Corredor corredor;

        while (fread(&corredor, sizeof(Corredor), 1, archivoCorredores))
        {
            if (corredor.numeroCorredor == corredorGanador)
            {
                printf("El ganador de la carrera es:\n");
                printf("Numero de corredor: %d\n", corredor.numeroCorredor);
                printf("Nombre: %s %s\n", corredor.nombreCorredor, corredor.apellidoCorredor);
                printf("Scuderia: %s\n", corredor.scuderia);
                printf("Tiempo total: %.3f\n", tiempoGanador);
                break;
            }
        }

        fclose(archivoCorredores);
    }
    else
    {
        printf("No hay datos de tiempos para determinar al ganador.\n");
    }
}

void mostrarGanador()
{
    Resultado resultados[20];
    int cantidadCorredores = 0;

    // Abrir el archivo de corredores
    FILE *archivoCorredores = fopen("../corredores.dat", "rb");
    if (archivoCorredores == NULL)
    {
        printf("No se pudo abrir el archivo de corredores.\n");
        return;
    }

    // Leer los corredores y guardarlos en un arreglo
    Corredor corredor;
    while (fread(&corredor, sizeof(Corredor), 1, archivoCorredores))
    {
        resultados[cantidadCorredores].numCorredor = corredor.numeroCorredor;
        resultados[cantidadCorredores].tiempoTotal = 0;
        cantidadCorredores++;
    }

    fclose(archivoCorredores);

    // Abrir el archivo de tiempos
    FILE *archivoTiempos = fopen("../tiempos2.dat", "rb");
    if (archivoTiempos == NULL)
    {
        printf("No se pudo abrir el archivo de tiempos.\n");
        return;
    }

    // Leer los tiempos y sumarlos al tiempo total de cada corredor
    Tiempos tiempo;
    while (fread(&tiempo, sizeof(Tiempos), 1, archivoTiempos))
    {
        for (int i = 0; i < cantidadCorredores; i++)
        {
            if (resultados[i].numCorredor == tiempo.numCorredor)
            {
                resultados[i].tiempoTotal += tiempo.tiempo;
                break;
            }
        }
    }

    fclose(archivoTiempos);

    // Mostrar los resultados
    printf("Resultados finales:\n");
    for (int i = 0; i < cantidadCorredores; i++)
    {
        printf("Num:|%d|, Tiempo total: %.3f\n", resultados[i].numCorredor, resultados[i].tiempoTotal);
    }
}

void generarCSV()
{
    FILE *archivoCorredores = fopen("../corredores.dat", "rb");
    FILE *archivoTiempos = fopen("../tiempos2.dat", "rb");
    FILE *archivoCSV = fopen("../resultados.csv", "w");

    if (archivoCorredores == NULL || archivoTiempos == NULL || archivoCSV == NULL)
    {
        printf("No se pudo abrir uno de los archivos.\n");
        return;
    }

    Corredor corredor;
    Tiempos tiempo;

    //fprintf(archivoCSV, "Numero de corredor,Nombre,Apellido,Scuderia,Tiempo total\n");

    while (fread(&corredor, sizeof(Corredor), 1, archivoCorredores))
    {
        float tiempoTotal = 0;

        fseek(archivoTiempos, 0, SEEK_SET);
        while (fread(&tiempo, sizeof(Tiempos), 1, archivoTiempos))
        {
            if (tiempo.numCorredor == corredor.numeroCorredor)
            {
                tiempoTotal += tiempo.tiempo;
            }
        }

        fprintf(archivoCSV, "%d,%s,%s,%s,%.03f\n", corredor.numeroCorredor, corredor.nombreCorredor, corredor.apellidoCorredor, corredor.scuderia, tiempoTotal);
    }

    fclose(archivoCorredores);
    fclose(archivoTiempos);
    fclose(archivoCSV);

    printf("Se genero el archivo resultados.csv\n");
}