

#include <stdio.h>
#include <stdlib.h>

int main(){
int n=1; /*Número del empleado*/
char nombre[80];
double salario;
FILE *pArchivo;
pArchivo=fopen("prueba4.txt","w");
if(pArchivo!=NULL){
		do{
		printf("Introduzca el número de empleado: ");
		scanf("%d",&n);
		/*Solo seguimos si n es positivo, en otro caso
		entenderemos que la lista ha terminado */
						if(n>0){
						printf("Introduzca el nombre del empleado: ");
						scanf("%s",nombre);
						printf("Introduzca el salario del empleado: ");
						scanf("%lf",&salario);
						fprintf(pArchivo,"%d\t%s\t%lf\n", n,nombre,salario);
						}
		}while(n>0);
fclose(pArchivo);
}
system("pause");
return 0;}


