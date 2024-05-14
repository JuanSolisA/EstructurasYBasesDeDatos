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
    char nombreCorredor[15];
    char apellidoCorredor[15];
    float tiempoTotal;
} Resultado;

void cargarConfig();
void mostrarCorredores();
void mostrarTiempos();
void finDeCarrera();
void imprimirPodio();

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
        printf("3. Si desea ver los resultados de la carrera\n");
        printf("4. Si desea imprimir el podio\n");
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
            finDeCarrera();
            system("pause");
            break;
        case 4:
            system("cls");
            imprimirPodio();
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

void finDeCarrera()
{
    Resultado resultados[20];
    int cantidadCorredores = 0;

    FILE *archivoCorredores = fopen("../corredores.dat", "rb");
    FILE *archivoTiempos = fopen("../tiempos2.dat", "rb");
    if (archivoCorredores == NULL || archivoTiempos == NULL)
    {
        printf("Hubo problemas con la apertura de los archivos.\n");
    }
    else
    {

        Corredor corredor;
        while (fread(&corredor, sizeof(Corredor), 1, archivoCorredores))
        {
            strcpy(resultados[cantidadCorredores].apellidoCorredor, corredor.apellidoCorredor);
            strcpy(resultados[cantidadCorredores].nombreCorredor, corredor.nombreCorredor);
            resultados[cantidadCorredores].numCorredor = corredor.numeroCorredor;
            resultados[cantidadCorredores].tiempoTotal = 0;
            cantidadCorredores++;
        }

        fclose(archivoCorredores);

        Tiempos tiempo;
        while (fread(&tiempo, sizeof(Tiempos), 1, archivoTiempos))
        {
            for (int i = 0; i < cantidadCorredores; i++)
            {
                if (resultados[i].numCorredor == tiempo.numCorredor && tiempo.numVuelta != 0)
                {
                    resultados[i].tiempoTotal += tiempo.tiempo;
                }
            }
        }
        for (int i = 0; i < cantidadCorredores; i++)
        {
            for (int j = 0; j < cantidadCorredores - 1; j++)
            {
                if (resultados[j].tiempoTotal > resultados[j + 1].tiempoTotal)
                {
                    Resultado aux = resultados[j];
                    resultados[j] = resultados[j + 1];
                    resultados[j + 1] = aux;
                }
            }
        }

        fclose(archivoTiempos);

        printf("Resultados finales:\n\n");
        printf("Apellido, Nombre\t\tNumero\t\tTiempo total\n\n");
        for (int i = 0; i < cantidadCorredores; i++)
        {
            printf("%s, %s\t\t\t|%d|\t\t%.3f\n", resultados[i].apellidoCorredor, resultados[i].nombreCorredor, resultados[i].numCorredor, resultados[i].tiempoTotal);
        }
    }
}

void imprimirPodio()
{
    FILE *archivoTiempos = fopen("../tiempos2.dat", "rb");
    FILE *archivoCorredores = fopen("../corredores.dat", "rb");
    FILE *configuracion = fopen("../config.txt", "r");
    FILE *archivoPodio = fopen("../podio.txt", "w");

    if (archivoTiempos == NULL || archivoCorredores == NULL || configuracion == NULL || archivoPodio == NULL)
    {
        printf("Hubo problemas con la apertura de los archivos.\n");
    }
    else
    {

        Tiempos tiempo;
        int corredorGanador = -1;
        float tiempoGanador = 9999;
        char circuito[15];
        Resultado resultados[20];
        int cantidadCorredores = 0;
        printf("Podio de %s\n", circuito);
        fprintf(archivoPodio, "Podio de %s\n", circuito);

        Corredor corredor;
        while (fread(&corredor, sizeof(Corredor), 1, archivoCorredores))
        {
            strcpy(resultados[cantidadCorredores].apellidoCorredor, corredor.apellidoCorredor);
            strcpy(resultados[cantidadCorredores].nombreCorredor, corredor.nombreCorredor);
            resultados[cantidadCorredores].numCorredor = corredor.numeroCorredor;
            resultados[cantidadCorredores].tiempoTotal = 0;
            cantidadCorredores++;
        }

        fclose(archivoCorredores);

        while (fread(&tiempo, sizeof(Tiempos), 1, archivoTiempos))
        {
            for (int i = 0; i < cantidadCorredores; i++)
            {
                if (resultados[i].numCorredor == tiempo.numCorredor && tiempo.numVuelta != 0)
                {
                    resultados[i].tiempoTotal += tiempo.tiempo;
                }
            }
        }
        for (int i = 0; i < cantidadCorredores; i++)
        {
            for (int j = 0; j < cantidadCorredores - 1; j++)
            {
                if (resultados[j].tiempoTotal > resultados[j + 1].tiempoTotal)
                {
                    Resultado aux = resultados[j];
                    resultados[j] = resultados[j + 1];
                    resultados[j + 1] = aux;
                }
            }
        }
        printf("Posicion\tApellido, Nombre\t\tNumero\t\tTiempo total\n\n");
        fprintf(archivoPodio, "Posicion\tApellido, Nombre\t\tNumero\t\tTiempo total\n\n");
        for (int i = 0; i < 3; i++)
        {
            printf("#%i\t\t%s, %s\t\t\t|%d|\t\t%.3f\n", i + 1, resultados[i].apellidoCorredor, resultados[i].nombreCorredor, resultados[i].numCorredor, resultados[i].tiempoTotal);
            fprintf(archivoPodio, "#%i\t\t%s, %s\t\t\t|%d|\t\t%.3f\n", i + 1, resultados[i].apellidoCorredor, resultados[i].nombreCorredor, resultados[i].numCorredor, resultados[i].tiempoTotal);
        }

        while (fread(&tiempo, sizeof(Tiempos), 1, archivoTiempos))
        {
            if (tiempo.tiempo < tiempoGanador && tiempo.numVuelta != 0)
            {
                tiempoGanador = tiempo.tiempo;
                corredorGanador = tiempo.numCorredor;
            }
        }
        Corredor corredorMasRapido;
        while (fread(&corredorMasRapido, sizeof(Corredor), 1, archivoCorredores))
        {
            if (corredorMasRapido.numeroCorredor == corredorGanador)
            {
                printf("Corredor mas rapido: #%d %s %s %.3f#\n", corredorMasRapido.numeroCorredor, corredorMasRapido.nombreCorredor, corredorMasRapido.apellidoCorredor, tiempoGanador);
                fprintf(archivoPodio, "Corredor mas rapido: #%d %s %s %.3f#\n", corredorMasRapido.numeroCorredor, corredorMasRapido.nombreCorredor, corredorMasRapido.apellidoCorredor, tiempoGanador);
            }
        }

        fclose(archivoTiempos);
        fclose(archivoCorredores);
        fclose(configuracion);
        fclose(archivoPodio);
    }
}