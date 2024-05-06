#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
char nombre[25];
int edad;
}Persona;

int main(){
Persona aux;
char nom[25];
int cont =0;
FILE *pArchivo;
pArchivo=fopen("datos.dat","rb");
if(pArchivo!=NULL){
                    printf ("Ingrese un nombre y se indicr� si est� y en qu� posici�n \n");
                    scanf ("%s", nom);
					fread(&aux,sizeof(Persona),1,pArchivo);
					while(!feof(pArchivo) && (strcmp(nom, aux.nombre)!=0)){
											cont++;
											fread(&aux,sizeof(Persona),1,pArchivo);
											}
					if (feof(pArchivo))
                       {printf("Ese  nombre no está en ning�n registro de este archivo");}
                    else 
                       	{printf("Ese  nombre est� en el registro de posici�n %d ", cont);}					
					fclose(pArchivo);
					}
else{
printf("Error en la apertura del archivo");
}
system("pause");
return 0;
}
