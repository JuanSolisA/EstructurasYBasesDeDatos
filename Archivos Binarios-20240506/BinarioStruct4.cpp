#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
char nombre[25];
int edad;
}Persona;

int main(){
Persona aux;
int pos;
FILE *pArchivo;
pArchivo=fopen("datos.dat","rb");
printf("Ingrese posici�n a leer. La primera es 0 -1 para fin");
scanf("%d", &pos);
if(pArchivo!=NULL)
{
   while (pos!=-1)
             {
                   
                    fseek (pArchivo, pos * sizeof(Persona), SEEK_SET);
					fread(&aux,sizeof(Persona),1,pArchivo);
					printf("Nombre: %s, Edad: %d\n",aux.nombre, aux.edad);
				    printf("Ingrese posici�n a leer. La primera es 0 -1 para fin");
                    scanf("%d", &pos);
			
            }
   fclose(pArchivo); 
} 
else{
printf("Error en la apertura del archivo");
}
system("pause");
return 0;
}
