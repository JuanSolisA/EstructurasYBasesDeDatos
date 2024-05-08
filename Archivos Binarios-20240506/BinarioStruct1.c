#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
	char nombre[25];
	int edad;
} Persona;

int main()
{

	int i = 0;
	FILE *pArchivo;
	Persona per;
	pArchivo = fopen("datos.dat", "wb");
	if (pArchivo != NULL)
	{

		fflush(stdin);
		printf("Introduzca el nombre de la persona: ");

		scanf("%s", per.nombre);
		while (strcmp(per.nombre, "*") != 0)
		{
			printf("Introduzca la edad ");
			scanf("%d", &(per.edad));
			fwrite(&per, sizeof(Persona), 1, pArchivo);
			printf("Introduzca el nombre de la persona: ");
			scanf("%s", per.nombre);
		}
		fclose(pArchivo);
	}

	else
	{
		printf("Error en la apertura del archivo");
	}
	system("pause");
	return 0;
}
