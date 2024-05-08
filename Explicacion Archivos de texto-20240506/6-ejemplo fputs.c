

#include <stdio.h>
#include <stdlib.h>

int main(){
//int n=1; /*Número del empleado*/
char cadena[80];
//double salario;
FILE *pArchivo;
pArchivo=fopen("prueba5.txt","w");
if(pArchivo!=NULL){
		
		printf("Introduzca una frase \n ");
		gets(cadena);

		/*Solo seguimos si n es positivo, en otro caso
		entenderemos que la lista ha terminado */
						while(!feof(stdin)){
					    
                        fputs(cadena,pArchivo);
						fputs("\n",pArchivo);
						printf("Introduzca una frase \n");
						
						gets(cadena);
						
						}
		
fclose(pArchivo);
}
system("pause");
return 0;}


