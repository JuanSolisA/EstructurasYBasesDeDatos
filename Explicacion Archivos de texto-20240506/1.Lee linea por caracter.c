#include <stdio.h>
#include <stdlib.h>

int main(){
FILE *archivo;
char c=0;
archivo=fopen("../texto.txt","r+");
if(archivo!=NULL)
				{ /* Apertura correcta */
						while(c!=EOF)
						{ /* Se lee hasta llegar al final */
						c=fgetc(archivo);
						putchar(c);
						}
				fclose(archivo);
				}
else{ printf("Error!");}
system("pause");
return 0;
}
