#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LISTAS 5     // Listas de candidatos
#define MAX_CADENA 81    // Máximo de caracteres en una cadena
#define MAX_PROVINCIAS 3 // Máximo de provincias
#define MAX_DISTRITOS 4  // Máximo de distritos

typedef char cadena[40];

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
    static const char *candidatos[MAX_LISTAS] = {"Juan Gonzalez", "Marcos Alvarez", "Ana Lopez", "Nicolas Ramirez", "Sofia Flores"};
    return (lista >= 0 && lista < MAX_LISTAS) ? candidatos[lista] : "Desconocido";
}

void liberarMemoria(nodo *cabeza)
{
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

int menu(void)
{
    int op;
    do
    {
        printf("\n\n** MENU PRINCIPAL **\n");
        printf("1. Cargar datos desde archivo de texto\n");
        printf("2. Mostrar registros del archivo binario\n");
        printf("3. Buscar datos por provincia, distrito y lista\n");
        printf("4. Mostrar resultado general de votos\n");
        printf("5. Ingresar Resultados a la lista Enlazada\n");
        printf("6. Mostrar la lista Enlazada\n");
        printf("0. Salir\n");
        printf("****\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &op);

    } while (op < 0 || op > 6);
    return op;
}

int leerEntero(cadena mensaje)
{
    int numero;
    printf("%s: ", mensaje);
    fflush(stdin);
    scanf("%d", &numero);
    return numero;
}

void cargar(FILE *archivoBinario, registro reg)
{
    registro tempReg;
    size_t size = sizeof(reg);
    int encontrado = 0;

    // Mueve el puntero del archivo binario al inicio
    fseek(archivoBinario, 0, SEEK_SET);
    while (fread(&tempReg, size, 1, archivoBinario) == 1)
    {
        if (tempReg.prov == reg.prov && tempReg.distrito == reg.distrito && tempReg.lista == reg.lista)
        {
            // Registro encontrado, incrementar votos
            tempReg.votos += 1;
            fseek(archivoBinario, -size, SEEK_CUR);
            fwrite(&tempReg, size, 1, archivoBinario);
            encontrado = 1;
            break;
        }
    }

    // Si el registro no fue encontrado, añadir uno nuevo
    if (!encontrado)
    {
        reg.votos = 1;
        fseek(archivoBinario, 0, SEEK_END);
        fwrite(&reg, size, 1, archivoBinario);
    }

    fflush(archivoBinario);             // Asegúrate de que los cambios se escriban en el disco
    fseek(archivoBinario, 0, SEEK_SET); // Regresa al inicio para la próxima operación
}

void mostrar(FILE *archivo)
{
    registro reg;
    size_t size = sizeof(reg);

    fseek(archivo, 0, SEEK_SET);

    // Leer y mostrar cada registro del archivo binario
    while (fread(&reg, size, 1, archivo) == 1)
    {
        // Mostrar los datos del registro
        printf("Provincia: %d, Distrito: %d, Candidato: %d, Votos: %d\n",
               reg.prov, reg.distrito, reg.lista, reg.votos);
    }

    // Mueve el puntero del archivo binario al inicio para la próxima operación
    fseek(archivo, 0, SEEK_SET);
}

void buscar(FILE *archivo, int provincia, int distrito, int lista)
{
    registro tempReg;
    size_t size = sizeof(tempReg);
    while (fread(&tempReg, size, 1, archivo) == 1)
    {
        if (tempReg.prov == provincia && tempReg.distrito == distrito && tempReg.lista == lista)
        {
            printf("Provincia: %s, Distrito: %s, Lista: %s, Votos: %d", obtenerNombreProvincia(tempReg.prov - 1), obtenerNombreDistrito(tempReg.prov - 1, tempReg.distrito - 1), obtenerNombreCandidato(tempReg.lista - 1), tempReg.votos);
            break;
        }
    }
}

void imprimegeneral(FILE *archivo)
{
    registro reg;
    size_t size = sizeof(reg);
    int votosPorLista[MAX_LISTAS] = {0};
    int totalVotos = 0;

    fseek(archivo, 0, SEEK_SET);
    while (fread(&reg, size, 1, archivo) == 1)
    {
        votosPorLista[reg.lista] += reg.votos;
        totalVotos += reg.votos;
    }

    printf("Resultado general de votos:\n");
    // Ajustar índices para reflejar los nombres correctos
    for (int i = 0; i < MAX_LISTAS; i++) // Empezar en 0 para incluir todos los candidatos
    {
        printf("Candidato %d (%s) - Votos: %d\n", i + 1, obtenerNombreCandidato(i), votosPorLista[i + 1]);
    }

    printf("Total de votos: %d\n", totalVotos);

    fseek(archivo, 0, SEEK_SET);
}

void insertar(nodo **cabeza, int lista, int votos)
{
    nodo *nuevo = (nodo *)malloc(sizeof(nodo));
    if (nuevo == NULL)
    {
        printf("Error al asignar memoria\n");
        exit(1);
    }
    nuevo->lista = lista;
    nuevo->votos = votos;
    nuevo->sig = NULL;

    if (*cabeza == NULL)
    {
        *cabeza = nuevo;
    }
    else
    {
        nodo *actual = *cabeza;
        while (actual->sig != NULL)
        {
            actual = actual->sig;
        }
        actual->sig = nuevo;
    }
}

void listar(nodo *cabeza)
{
    if (cabeza == NULL)
    {
        printf("La lista está vacía.\n");
        return;
    }

    printf("Contenido de la lista enlazada:\n");
    while (cabeza != NULL)
    {
        printf("Candidato: %d (%s), Votos: %d\n",
               cabeza->lista, obtenerNombreCandidato(cabeza->lista), cabeza->votos);
        cabeza = cabeza->sig;
    }
}

void ingresarResultadosListaEnlazada(FILE *archivoBinario, nodo **cabeza)
{
    registro reg;
    size_t size = sizeof(reg);
    nodo *actual;

    fseek(archivoBinario, 0, SEEK_SET);
    while (fread(&reg, size, 1, archivoBinario) == 1)
    {
        actual = *cabeza;
        int encontrado = 0;

        // Buscar si ya existe un nodo para la lista
        while (actual != NULL)
        {
            if (actual->lista == reg.lista)
            {
                actual->votos += reg.votos;
                encontrado = 1;
                break;
            }
            actual = actual->sig;
        }

        // Si no se encontró, insertar un nuevo nodo
        if (!encontrado)
        {
            insertar(cabeza, reg.lista, reg.votos);
        }
    }
}

int main()
{
    FILE *archivo, *binario;
    char archivoTxt[] = "./votos.txt";
    char *nombin = "./datos.dat";
    nodo *cabeza = NULL;
    system("color 9f");
    // Abrir archivos
    archivo = fopen(archivoTxt, "r");
    manejarErrorArchivo(archivo, archivoTxt);
    binario = fopen(nombin, "wb+");
    manejarErrorArchivo(binario, nombin);
    registro reg;
    cadena linea;
    int op = menu();

    while (op)
    {
        switch (op)
        {
        case 1:
            while (fgets(linea, sizeof(linea), archivo))
            {
                if (strlen(linea) >= 3)
                {
                    reg.prov = linea[0] - '0';                                                                 // Primer dígito: Provincia
                    reg.distrito = linea[1] - '0';                                                             // Segundo dígito: Distrito
                    reg.lista = linea[2] - '0';                                                                // Tercer dígito: Número de lista
                    printf("Leído: Provincia %d, Distrito %d, Lista %d\n", reg.prov, reg.distrito, reg.lista); // Depuración
                }
                cargar(binario, reg);
            }
            break;

        case 2:
            mostrar(binario);
            break;

        case 3:
        {
            int prov = leerEntero("Ingrese el numero de provincia: ");
            int distr = leerEntero("Ingrese el numero de distrito: ");
            int list = leerEntero("Ingrese el numero de lista: ");
            buscar(binario, prov, distr, list);
            break;
        }
        break;

        case 4:
            imprimegeneral(binario);
            break;

        case 5:
            ingresarResultadosListaEnlazada(binario, &cabeza);
            break;

        case 6:
            listar(cabeza);
            break;

        case 0:
            break;
        }
        op = menu();
    }

    // Liberar memoria
    liberarMemoria(cabeza);
    fclose(archivo);
    fclose(binario);

    return 0;
}