#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LISTAS 5      // listas de condidatos
#define MAX_CADENA 81    // maximo de caracteres en una cadena
#define MAX_PROVINCIAS 3 // maximo de provincias
#define MAX_DISTRITOS 4  // maximo de distritos
    typedef struct
{
    int prov;
    int distrito;
    int lista;
    int votos;
} registro;
typedef struct elemento
{
    int lista; // Número del candidato
    int votos; // Total de votos para ese candidato
    struct elemento *sig;
} nodo;

void manejarErrorArchivo(FILE *archivo, const char *nombre);
void liberarMemoria(nodo *cabeza);
const char *obtenerNombreProvincia(int prov);
const char *obtenerNombreDistrito(int prov, int dis);
const char *obtenerNombreCandidato(int lista);



const char *obtenerNombreProvincia(int prov)
{
    static const char *provincias[MAX_PROVINCIAS] = {"Buenos Aires", "Santa Fe", "Córdoba"};
    return (prov >= 0 && prov < MAX_PROVINCIAS) ? provincias[prov] : "Desconocida";
}
const char *obtenerNombreDistrito(int prov, int dis)
{
    static const char *distritos[MAX_PROVINCIAS][MAX_DISTRITOS] = {
        {"La Plata", "Mar del Plata", "Lanús", "Lomas de Zamora"},
        {"Rosario", "Rafaela", "Venado Tuerto", "Reconquista"},
        {"Río Cuarto", "Villa María", "San Francisco", "Carlos Paz"}};
    return (prov >= 0 && prov < MAX_PROVINCIAS && dis >= 0 && dis < MAX_DISTRITOS) ? distritos[prov][dis] : "Desconocido";
}
const char *obtenerNombreCandidato(int lista)
{
    static const char *candidatos[MAX_LISTAS] = { "Juan Gonzalez", "Marcos Alvarez", "Ana Lopez", "Nicolas Ramirez", "Sofia Flores"};
    return (lista >= 0 && lista < MAX_LISTAS)? candidatos[lista] : "Desconocido";
}

void liberarMemoria(nodo *cabeza)
{
    // Liberar memoria de la lista enlazada
    while (cabeza != NULL)
    {
        nodo *temp = cabeza;
        cabeza = cabeza->sig;
        free(temp);
    }
}

void manejarErrorArchivo(FILE *archivo, const char *nombre)
{
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo %s\n", nombre);
        exit(1);
    }
}

void o



int menu(void)
{
    int op;
    do
    {
        printf("\n\n**** MENU PRINCIPAL ****\n");
        printf("1. Cargar datos desde archivo de texto\n");
        printf("2. Mostrar registros del archivo binario\n");
        printf("3. Buscar datos por provincia, distrito y lista\n");
        printf("4. Mostrar resultado general de votos\n");
        printf("5. Ingresar Resultados a la lista Enlazada\n");
        printf("6. Mostrar la lista Enlazada\n");
        printf("0. Salir\n");
        printf("************\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &op);

    } while (op < 0 || op > 6);
    return op;
}

int main()
{
    FILE *archivo, *binario;
    char nombre[] = "votos.txt";
    char *nombin = "datos.dat";
    nodo *cabeza = NULL;
    system("color 9f");
    // Abrir archivos
    archivo = fopen(nombre, "r");
    manejarErrorArchivo(archivo, nombre);
    binario = fopen(nombin, "wb+");
    manejarErrorArchivo(binario, nombin);
}
