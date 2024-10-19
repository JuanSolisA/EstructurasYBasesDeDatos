-- Active: 1728681291059@@127.0.0.1@3306
-- Date: 2021-10-11 20:08:11

DROP DATABASE IF EXISTS TP3SolisJuanEjercicio1;
CREATE DATABASE IF NOT EXISTS TP3SolisJuanEjercicio1 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci;
USE TP3SolisJuanEjercicio1;
    /* Ejercicio 1:
Supongamos utilizamos nuestra tabla "libro", definida con la siguiente estructura:
- código, int auto_increment, clave primaria,
- titulo, varchar (40) not null
- autor, varchar (30)
- editorial, varchar (20)
- precio, decimal (5,2)
- edición date
*/

CREATE TABLE libro (
    código INT AUTO_INCREMENT PRIMARY KEY,
    titulo VARCHAR(40) NOT NULL,
    autor VARCHAR(30),
    editorial VARCHAR(20),
    precio DECIMAL(5,2),
    edición DATE
);


-- a) Agregar el campo "cantidad", de tipo int NOT NULL

ALTER TABLE libro
ADD cantidad INT NOT NULL;

-- b) Eliminar el campo "edición"

ALTER TABLE libro
DROP COLUMN edición;

-- c) Modificar el tipo del campo "titulo" para poder almacenar una longitud de 30 caracteres y que no permita valores nulos.

ALTER TABLE libro
MODIFY titulo VARCHAR(30) NOT NULL;

-- d) Agregar el campo ISBN carácter (20) e indexar el campo.

ALTER TABLE libro
ADD ISBN VARCHAR(20),
ADD INDEX ISBN (ISBN);
