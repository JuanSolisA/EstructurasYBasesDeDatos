#include <stdlib.h>
#include <stdio.h>
//#include <string.h>

int main(){
char texto[] = "Texto de ejemplo. Utiliza, varios delimitadores\n\n";
char delim[] = " ,.";
char *token;

printf("Texto inicial: %s\n", texto);
/* En res se guarda el primer texto delimitado (token) */
token = strtok( texto, delim);
/* Obtención del resto de tokens (se debe usar NULL
en el primer parámetro)*/
do{
	printf("%s\n", token);
	token=strtok(NULL,delim);
   }while(token != NULL );

system("pause");
return 0;
}
