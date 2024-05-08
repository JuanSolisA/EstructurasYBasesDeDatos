
#include <stdio.h>
#include <stdlib.h>

int main(){
int n=1;
char nombre[80];
double salario;
FILE *pArchivo;
pArchivo=fopen("../prueba3.txt","r");
if(pArchivo!=NULL){

	            
				while(!feof(pArchivo))
				{
					

				fscanf(pArchivo,"%d\t%s\t%lf\n",&n,nombre,&salario);

				printf("%d\t%s\t%lf\n",n,nombre,salario);
				}
			fclose(pArchivo);
			}
system("pause");
return 0;
}
