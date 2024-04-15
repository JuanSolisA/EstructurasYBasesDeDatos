# Manejo de Archivos

En este archivo voy a resumir todo lo necesario para poder trabajar con **archivos en C**, ejemplificando el como se abre, como se leen, como se escriben y modifican.

## Menu

- [Manejo de Archivos](#manejo-de-archivos)
  - [Menu](#menu)
  - [Estructura FILE y punteros a archivos](#estructura-file-y-punteros-a-archivos)
  - [Apertura y cierre de archivos](#apertura-y-cierre-de-archivos)
    - [Apertura](#apertura)
    - [Cierre de archivos](#cierre-de-archivos)
  - [Procesamiento de archivos de texto](#procesamiento-de-archivos-de-texto)
    - [Leer y escribir caracteres](#leer-y-escribir-caracteres)
      - [Función _getc_](#función-getc)
      - [Función _fputc_](#función-fputc)
      - [Comprobar final de archivo](#comprobar-final-de-archivo)
    - [Leer y escribir strings](#leer-y-escribir-strings)
      - [Función fgets](#función-fgets)
      - [Función fputs](#función-fputs)
      - [Función fprintf](#función-fprintf)
      - [Función fscanf](#función-fscanf)
      - [Función fflush](#función-fflush)
    - [Volver al principio de un archivo](#volver-al-principio-de-un-archivo)
  - [Operaciones para uso con archivos binarios ()](#operaciones-para-uso-con-archivos-binarios-)

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
    FILE *archivo;
    char c=0;
    archivo=fopen("c:\\prueba.txt","r+");
    if(archivo!=NULL) {   // Apertura correcta
        while(c!=EOF){   // Se lee hasta llegar al final
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

### Leer y escribir strings

#### Función fgets

Se trata de una función que permite leer textos de un archivo de texto. Su prototipo es:

`char *fgets(char *texto, int longitud, FILE *pArchivo)`

Esta función lee una cadena de caracteres del archivo asociado al puntero de archivos **pArchivo** y la almacena en el puntero **texto**. Lee la cadena hasta que llegue un salto de línea, o hasta que se supere la longitud indicada. La función devuelve un puntero señalando al texto leído o un puntero nulo (NULL) si la operación provoca un error.
Ejemplo (lectura de un archivo de texto):

```markdown
#include <stdio.h>
#include <conio.h>
int main(){
    FILE *archivo;
    char texto[2000];
    archivo=fopen("c:\\prueba2.txt","r");
    if(archivo!=NULL) {
        fgets(texto,2000,archivo);
        while(!feof(archivo)){
        puts(texto);
        fgets(texto,2000,archivo);
        }
        fclose(archivo);
    }
    else{
        printf("Error en la apertura");
    }
} 
```

En el listado el valor 2000 dentro de la funcón **fgets** tiene como único sentido, asegurar
que se llega al final de línea cada vez que lee el texto (ya que ninguna línea del archivo tendrá más de 2000 caracteres).

#### Función fputs

Es equivalente a la anterior, solo que ahora sirve para escribir strings dentro de un archivo de texto. Prototipo:

`int fputs(const char texto, FILE *pArchivo)`

Escribe el texto en el archivo indicado. Además al final del texto colocará el carácter del salto de línea (al igual que hace la función **puts**). En el caso de que ocurra un error, devuelve EOF. Ejemplo (escritura en un archivo del texto introducido por el usuario en pantalla).

#### Función fprintf

Es una función que permite escribir en un archivo de texto, de forma similar a la función **printf**. Prototipo:

`int fprintf(FILE *pArchivo, const char *formato, ...)`

Escribe en el archivo asociado al puntero **pArchivo** el texto que se le pasa como argumento. La función devuelve el número de caracteres escritos o un valor negativo si se produce un error. Ejemplo:

```markdown
#include <stdio.h>
int main(){
    int n=1; /*Número del empleado*/
    char nombre[80];
    double salario;
    FILE *pArchivo;
    pArchivo=fopen("c:\\prueba3.txt","w");
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
                fprintf(pArchivo,"%d\t%s\t%lf\n",
                n,nombre,salario);
            }
        }while(n>0);
            fclose(pArchivo);
    }
} 
```

#### Función fscanf

Se trata de la equivalente al **scanf** de lectura de datos por teclado. Funciona igual sólo que
requiere un primer parámetro que sirve para asociar la lectura a un puntero de archivo. El
resto de parámetros se manejan igual que en el caso de scanf.

`int fscanf(FILE *pArchivo, const char *formato, ...)`
Ejemplo:

```markdown
#include <stdio.h>
#include <conio.h>
int main(){
    int n=1;
    char nombre[80];
    double salario;
    FILE *pArchivo;
    pArchivo=fopen("c:\\prueba3.dat","r");
    if(pArchivo!=NULL){
        while(!feof(pArchivo)){
            fscanf(pArchivo,"%d\t%s\t%lf\n",&n,nombre,&salario);
            printf("%d\t%s\t%lf\n",n,nombre,salario);
        }
        fclose(pArchivo);
        getch();
    }
}
```

#### Función fflush

Esta función se utiliza para vaciar el buffer de salida de un archivo. Es decir, si se ha escrito en un archivo y no se ha cerrado, se puede utilizar esta función para asegurarse de que los datos se han escrito en el archivo. Prototipo:

`int fflush(FILE *pArchivo)`

Devuelve cero si la operación ha sido correcta, en otro caso devuelve EOF si se produce un error.

### Volver al principio de un archivo

Para volver al principio de un archivo, se utiliza la función **_rewind_**. Prototipo:

`void rewind(FILE *pArchivo)`

Esta función no devuelve ningún valor. Simplemente coloca el puntero de archivo al principio del archivo.

## Operaciones para uso con archivos binarios ()
