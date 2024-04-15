# Manejo de Archivos

En este archivo voy a resumir todo lo necesario para poder trabajar con **archivos en C**, ejemplificando el como se abre, como se leen, como se escriben y modifican.

## Estructura FILE y punteros a archivos

En el archivo de cabecera stdio.h se define una estructura llamada FILE. Esa estructura
representa la cabecera de los archivos. La secuencia de acceso a un archivo debe poseer
esta estructura.
Un programa requiere tener un puntero de tipo **_\*FILE_** a cada archivo que se desee leer
o escribir. A este puntero se le llama puntero de archivos.

## Apertura y cierre de archivos

### Apertura

La apertura de los archivos se realiza con la función **_fopen_**. Esta función devuelve un puntero de tipo FILE al archivo que se desea abrir. El prototipo de la función es:

`FILE *fopen(const char *nombreArchivo, const char *modo)`

**_nombreArchivo_** es una cadena que contiene la ruta hacia el archivo que se desea abrir.

**_modo_** es otra cadena cuyo contenido puede ser:

| modo  | significado                                                                                                                         |
| ----- | ----------------------------------------------------------------------------------------------------------------------------------- |
| "r"   | Abre un archivo para lectura de archivo de textos (el archivo tiene que existir)                                                    |
| "w"   | Crea un archivo de escritura de archivo de textos. Si el archivo ya existe se borra el contenido que posee                          |
| "a"   | Abre un archivo para adición de datos de archivo de textos                                                                          |
| “rb”  | Abre un archivo para lectura de archivos binarios (el archivo tiene que existir)                                                    |
| “wb”  | Crea un archivo para escritura de archivos binarios (si ya existe, se descarta el contenido)                                        |
| “ab”  | Abre un archivo para añadir datos en archivos binarios                                                                              |
| “r+”  | Abre un archivo de texto para lectura/escritura en archivos de texto. El archivo tiene que existir                                  |
| “w+”  | Crea un archivo de texto para lectura/escritura en archivos de texto. Si el archivo tenía datos, estos se descartan en la apertura. |
| “a+”  | Crea o abre un archivo de texto para lectura/escritura. Los datos se escriben al final.                                             |
| “r+b” | Abre un archivo binario para lectura/escritura en archivos de texto                                                                 |
| “w+b” | Crea un archivo binario para lectura/escritura en archivos de texto. Si el archivo tiene datos, éstos se pierden.                   |
| “a+b” | Crea o abre un archivo binario para lectura/escritura. La escritura se hace al final de el archivo.                                 |

Un archivo se puede abrir en modo texto o en modo binario. En modo texto se leen o
escriben caracteres, en modo binario se leen y escriben cualquier otro tipo de datos.
La función fopen devuelve un puntero de tipo FILE al archivo que se está abriendo.
En caso de que esta apertura falle, devuelve el valor NULL (puntero nulo). El fallo se
puede producir porque el archivo no exista (sólo en los modos r), porque la ruta al archivo
no sea correcta, porque no haya permisos suficientes para la apertura, porque haya un
problema en el sistema,...

### Cierre de archivos

La función **_fclose_** es la encargada de cerrar un archivo previamente abierto. Su prototipo es:

`int fclose(FILE *pArchivo);`

**_pArchivo_** es el puntero que señala al archivo que se desea cerrar. Si devuelve el valor cero,
significa que el cierre ha sido correcto, en otro caso se devuelve un número distinto de
cero.

## Procesamiento de archivos de texto

### Leer y escribir caracteres

#### Función _getc_

Esta función sirve para leer caracteres de un archivo de texto. Los caracteres se van leyendo secuencialmente hasta llegar al final. Su prototipo es:

`int getc(FILE *pArchivo);`

Esta función devuelve una contante numérica llama EOF (definida también en el archivo **stdio.h**) cuando ya se ha alcanzado el final del archivo. En otro caso devuelve el siguiente carácter del archivo.

Ejemplo:

```markdown
#include <stdio.h>
#include <conio.h>
int main(){
FILE \_archivo;
char c=0;
archivo=fopen("c:\\prueba.txt","r+");
if(archivo!=NULL) { // Apertura correcta
while(c!=EOF){ // Se lee hasta llegar al final
c=fgetc(archivo);
putchar(c);
}
fclose(archivo);
}
else{
printf("Error");
}
getch();
}
```

#### Función _fputc_

Es la función que permite escribir caracteres en un archivo de texto. Prototipo:

`int putc(int carácter, FILE *pArchivo);`

Escribe el carácter indicado en el archivo asociado al puntero que se indique. Si esta función tiene éxito (es decir, realmente escribe el carácter) devuelve el carácter escrito, en otro caso devuelve EOF.

#### Comprobar final de archivo

Anteriormente se ha visto como la función **_fgetc_** devuelve el valor EOF si se ha llegado al
final del archivo. Otra forma de hacer dicha comprobación, es utilizar la función **_feof_** que
devuelve verdadero si se ha llegado al final del archivo. Esta función es muy útil para ser
utilizada en archivos binarios (donde la constante EOF no tiene el mismo significado)
aunque se puede utilizar en cualquier tipo de archivo. Sintaxis:

`int feof(FILE *pArchivo)`

Así el código de lectura de un archivo para mostrar los caracteres de un texto, quedaría:

```markdown
#include <stdio.h>
#include <conio.h>
int main(){
    FILE *archivo;
    char c=0;
    archivo=fopen("c:\\prueba.txt","r+");
    if(archivo!=NULL) {
        while(!feof(archivo)){
            c=fgetc(archivo);
            putchar(c);
        }
    }
    else{
        printf("Error");
    }
    fclose(archivo);
    getch();
}
```
