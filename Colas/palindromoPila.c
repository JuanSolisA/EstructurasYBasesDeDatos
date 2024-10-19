/*
Ingresar una palabra o texto, y ver si esa palabra o texto es palindromo o no. Usar Pila o Cola
*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct nodo
{
    char cadena;
    struct nodo *sig;
} nodo;

void push(nodo **cima, char cadena)
{
    nodo *nuevoNodo = (nodo *)malloc(sizeof(nodo));
    nuevoNodo->cadena = cadena;
    nuevoNodo->sig = *cima;
    *cima = nuevoNodo;
}

void pop(nodo ** cima){
    if (cima==NULL)
    return 0;
    nodo temp = *cima;
    char cadena = temp->cadena;
    
    
}