#include <stdio.h>
#include <stdlib.h>

int main(){
FILE *archivo;
char c=0;
archivo=fopen("../texto2.txt","r+");
if(archivo!=NULL)
{
			while(!feof(archivo))
			{
			c=fgetc(archivo);
			putchar(c);
			}
}
else {printf("Error");}
fclose(archivo);
system("pause");
return 0;
}
