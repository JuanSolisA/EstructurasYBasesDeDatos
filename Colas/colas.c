#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

typedef struct elemento
{
    int dato;
    struct elemento *sig;
} nodo;

void acolar(nodo, nodo **, nodo **);
nodo *nuevonodo(nodo);
nodo desacolar(nodo **);
void listar(nodo *);
void vaciar(nodo **);
nodo *verificar(nodo *);
nodo ingresar_dato(void);
void dato_eliminado(nodo);
int menu(void);

void acolar(nodo r, nodo **p, nodo **aux)
{
    nodo *nuevo;
    nuevo = nuevonodo(r);
    if (*p == NULL)
        *p = nuevo;
    else
        (*aux)->sig = nuevo;
    *aux = nuevo;
}

nodo ingresar_dato(void)
{
    nodo r;
    system("cls");
    printf("\nIngrese un numero");
    scanf("%d", &r.dato);
    return (r);
}

nodo *nuevonodo(nodo r)
{
    nodo *x;
    x = (nodo *)malloc(sizeof(nodo));
    x->dato = r.dato;
    x->sig = NULL;
    return (x);
}

void listar(nodo *p)
{
    if (p)
    {
        printf("\tDireccion:<%p> dato:%d siguiente: %p\n", (void *)p, p->dato, (void *)p->sig);
        listar(p->sig);
    }
}

nodo *verificar(nodo *p)
{
    if (p == NULL)
    {
        system("cls");
        printf("\nCOLA VACIA!!");
        printf("\n\n\nPulse una tecla......");
        getch();
    }
    return (p);
}
nodo desacolar(nodo **p)
{
    nodo r, *aux;
    r = **p;
    aux = *p;
    *p = (*p)->sig;
    free(aux);
    return (r);
}

void vaciar(nodo **p)
{
    nodo *aux;
    while (*p != NULL)
    {
        aux = *p;
        *p = (*p)->sig;
        free(aux);
    }
}

int menu(void)
{
    int op;
    system("cls");
    printf("\n\t\t\t******MENU PRINCIPAL******");
    do
    {
        printf("\n\n\t\t\t\tAcolar      <1>");
        printf("\n\n\t\t\t\tDesacolar   <2>");
        printf("\n\n\t\t\t\tListar      <3>");
        printf("\n\n\t\t\t\tVaciar      <4>");
        printf("\n\n\t\t\t\tSalir       <5>");
        scanf("%d, &op");

    } while (op < 1 || op > 5);
    nodo *p = NULL, *aux, r;
    switch (op)
    {
    case 1:
        r = ingresar_dato();
        acolar(r, &p, &aux);
        break;
    case 2:
        if (verificar(p) != NULL)
            r = desacolar(&p);
        dato_eliminado(r);
        break;
    case 3:
        if (verificar(p) != NULL)
            listar(p);
        break;
    case 4:
        if (verificar(p) != NULL)
            vaciar(&p);
        break;
    default:
        break;
    }
    return op;
}