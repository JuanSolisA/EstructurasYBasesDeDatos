#include <stdio.h>

int main() {
    // Abrir un archivo en modo escritura
    FILE *archivo = fopen("archivo.txt", "w");
    
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }
    
    // Escribir en el archivo
    fprintf(archivo, "Hola, mundo!");
    
    // Cerrar el archivo
    fclose(archivo);
    
    // Abrir el archivo en modo lectura
    archivo = fopen("archivo.txt", "r");
    
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }
    
    // Leer el contenido del archivo
    char contenido[100];
    fgets(contenido, 100, archivo);
    
    // Imprimir el contenido del archivo
    printf("Contenido del archivo: %s\n", contenido);
    
    // Cerrar el archivo
    fclose(archivo);
    
    return 0;
}