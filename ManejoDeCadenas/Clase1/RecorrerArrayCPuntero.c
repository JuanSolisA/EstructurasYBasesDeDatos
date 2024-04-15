/* Dado este vector, utilizar un puntero y recorrerlo

Int lista[] = {24,30,15,45,34}
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int lista[] = {24, 30, 15, 45, 34};
    // Declaro un puntero que apunta a un entero
    int *puntero;
    // Asigno al puntero la dirección de memoria del primer elemento del array "lista"
    puntero = lista;

    for (int i = 0; i < 5; i++)
    {
        printf("El valor del puntero en la posicion %d sera: %d\n", i, *puntero);
        puntero++;
        // *puntero     accede al valor al que apunta el puntero en la posición actual del recorrido.
        //  puntero++   incrementa el puntero para que apunte al siguiente elemento del vector en la próxima iteración del bucle.
    }
    return 0;
}