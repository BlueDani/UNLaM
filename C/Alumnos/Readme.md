# Sistema de gestión de Alumnos

## Introducción
Proyecto integrador de la materia Tópicos de Programación de la carrera de Ingeniería en Informática ([UNLaM - DIIT](https://ingenieria.unlam.edu.ar/)), primer cuatrimestre de 2023.


## Funcionamiento

Se ofrece mediante consola un menú para que el usuario interactúe por teclado, con las siguientes opciones:
- Alta
- Baja
- Buscar por DNI
- Listar Bajas
- Listar Altas (ordenados por DNI)

El código fuente crea un archivo con 5 alumnos por default para que el usuario ya cuente con el proyecto listo para usar, ahorrándole tener que insertar los primeros alumnos a mano.


## Implementación
Se implementa mediante un vector en memoria dinámica que actúa como índice, vinculado por clave con el archivo de alumnos, para su procesamiento.