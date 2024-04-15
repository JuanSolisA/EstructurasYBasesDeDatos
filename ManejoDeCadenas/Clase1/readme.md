# Universidad Tecnológica Nacional

## Instituto Nacional Superior del Profesorado Técnico

### Estructuras y Base de Datos TM y TT

#### Ejercicios de Repaso

1. **Recorrer un Vector con Puntero**
   - Dado este vector, utilizar un puntero y recorrerlo:

    ```markdown
     int lista[] = {24, 30, 15, 45, 34};
     ```

2. **Gestión de Alumnos en un Curso de Programación**
   - Realizar un programa que resuelva lo siguiente:
     a) Una función que pida al usuario la cantidad de elementos a almacenar.
     b) Una función `cargar` que cargue los N alumnos con sus respectivas notas correspondientes a un curso de Programación. Puede haber varias notas por alumno (máximo 5 notas).
     c) Una función que muestre los alumnos ordenados de mayor a menor por promedio, considerando solo las notas del 1er Parcial y 2do Parcial.
     d) Una función que muestre cuántos alumnos aprobaron, considerando que para aprobar la nota tiene que ser mayor a 6 inclusive en cada una de las dos instancias: 1er Parcial, 2do Parcial y/o Integral.
     e) Una función que muestre los datos de los alumnos cuyo inicial del nombre empiece con una letra ingresada desde teclado.

   ```markdown
   typedef char cadena[50];
   typedef struct {
       int legajo;
       cadena apellido;
       cadena nombre;
       float nota[5];
   } Alumno;

3. **Gestión de Empleados en una Empresa**
   - Realizar un programa que permita realizar lo siguiente:
    a) Una función que permita cargar los empleados de una empresa hasta que se decida terminar el ingreso de datos con DNI igual a -1. Deberá validarse si el empleado ya fue ingresado o no.
    b) Realizar el ordenamiento de los empleados por orden alfabético.
    c) Mostrar los empleados por sector.

```markdown
typedef char cadena[50];
typedef struct {
    int legajo;
    cadena apellido;
    cadena nombre;
    cadena sector;
} Empleado;
```

Para cada ejercicio, se proporcionan las estructuras de datos necesarias en lenguaje C. Puedes implementar las funciones y el código según tus necesidades.
