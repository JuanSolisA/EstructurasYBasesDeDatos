#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct datos{
    char col1[1];
    int col2;
    char col3[20];
    double col4; 
};

void extraeDatos(char * l, struct datos * f){
char * cadcol2, * cadcol4;

strcpy(f->col1, strtok(l,";"));
cadcol2=strtok(NULL,";");
f->col2=atoi(cadcol2);
strcpy(f->col3,strtok(NULL,";"));
cadcol4=strtok(NULL,";");
f->col4=atof(cadcol4);
}

int main(){
FILE *pArchivo=fopen("stock.csv","r+");
char linea[1000];
struct datos fila;

if(pArchivo!=NULL){
					fgets(linea,1000,pArchivo);
							while(!feof(pArchivo))
							{
							extraeDatos(linea, &fila);
							printf("%10s  %10d  %20s  %10.2lf\n",fila.col1, fila.col2, fila.col3, fila.col4);
							fgets(linea,1000,pArchivo);
							}
					fclose(pArchivo);
                     }
system("pause");
return 0;
}
