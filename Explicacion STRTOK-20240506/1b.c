#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Se encarga de transformar una línea del archivo de texto
en los datos correspondientes. Para ello extrae los tokens
y los convierte al tipo adecuado*/

void extraeDatos(char *linea, char *tipo, int *modelo, double *precio) 
{
char *cadModelo, *cadPrecio;
strcpy(tipo,strtok(linea,";"));
cadModelo=strtok(NULL,";");
*modelo=atoi(cadModelo);
cadPrecio=strtok(NULL,";");
*precio=atof(cadPrecio);
}

int main(){
FILE *pArchivo=fopen("../stock.csv","r");
char tipo[3];
char linea[2000];
int modelo;
double precio;
if(pArchivo!=NULL){
					fgets(linea,2000,pArchivo);
							while(!feof(pArchivo))
							{
							extraeDatos(linea,tipo,&modelo,&precio);
							printf("%s %d %lf\n",tipo,modelo,precio);
							fgets(linea,2000,pArchivo);
							}
					fclose(pArchivo);
}
system("pause");
return 0;
}
