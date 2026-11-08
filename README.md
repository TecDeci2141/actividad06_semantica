# Actividad 6: acciones semánticas y tabla de símbolos en C

## Identificación
- Matrícula: 10240041
- Nombre completo: DIEGO DECIDERIO GARCÍA
- Asignatura: Programación de Sistemas
- Actividad: 6
- Unidad: 5. Análisis semántico

## Objetivo
Implementar acciones semánticas sencillas en C para registrar declaraciones y comprobar usos de variables mediante una tabla de símbolos global, detectando variables utilizadas antes de declararse y previniendo declaraciones repetidas en un analizador de CompInt.

## Declaración
El programa extiende un analizador sintáctico descendente existente, agregando comprobaciones de significado. Las acciones semánticas se ejecutan únicamente después de reconocer una construcción sintáctica completa, evitando contaminar la tabla con sentencias malformadas.

## Estructura del proyecto
A06_semantica/
├── Makefile
├── main.c
├── mini_parser.c
├── mini_parser.h
├── tabla_simbolos.c
├── tabla_simbolos.h
├── pruebas/
│   ├── valido.ci
│   ├── uso_antes.ci
│   ├── redeclaracion.ci
│   ├── uso_repetido.ci
│   └── sintaxis_invalida.ci
├── .gitignore
└── README.md

## Compilación
make clean
make

## Ejecución
./compint_a06 < pruebas/valido.ci
./compint_a06 < pruebas/uso_antes.ci
./compint_a06 < pruebas/redeclaracion.ci
./compint_a06 < pruebas/uso_repetido.ci
./compint_a06 < pruebas/sintaxis_invalida.ci

## Resultados de las cinco pruebas obligatorias

### Prueba 1 – Compilación estricta
Make con gcc terminó sin errores ni advertencias. El ejecutable `compint_a06` se generó correctamente.

### Prueba 2 – Caso válido (valido.ci)
- entradas en tabla: 2 (contador int, promedio float)
- errores sintácticos: 0
- errores semánticos: 0
- estado de salida: 0

### Prueba 3 – Uso antes de declarar (uso_antes.ci)
- error semántico en línea 1: variable 'x' no declarada
- entradas en tabla: 1 (x int, declarada en línea 2)
- estado de salida: 1

### Prueba 4 – Redeclaración (redeclaracion.ci)
- error semántico en línea 2: variable 'total' ya declarada
- entradas en tabla: 1 (conserva total como int de la línea 1)
- estado de salida: 1

### Prueba 5 – Sintaxis inválida (sintaxis_invalida.ci)
- error sintáctico en línea 1: sentencia no reconocida
- entradas en tabla: 0 (tabla vacía)
- estado de salida: 1

## Explicación de conceptos clave

- **Tabla de símbolos**: estructura de datos global (arreglo de structs) que almacena el nombre, tipo y línea de declaración de cada variable.
- **Acción semántica**: operación ejecutada tras reconocer una construcción completa (ej. llamar a `ts_declara` después de validar `int ID;`).
- **Ámbito global**: regla de CompInt v1.0 donde no existen ámbitos anidados; un identificador solo puede declararse una vez en todo el programa.
- **ts_busca**: recorre la tabla de 0 a cantidad-1; devuelve el índice si existe, o -1 si no.
- **ts_declara**: verifica espacio y existencia previa antes de insertar; si ya existe, reporta error y no sobrescribe.
- **ts_usa**: consulta la tabla; si `ts_busca` devuelve -1, reporta error de variable no declarada.

## Respuestas de razonamiento

### 1. Diferencia entre sintaxis y semántica
La sintaxis valida la forma y el orden de los tokens, mientras que la semántica valida el significado y las reglas del lenguaje. Una sentencia como `x = 5;` es sintácticamente válida, pero si `x` no fue declarada previamente, carece de tipo y contexto en memoria, convirtiéndose en un error semántico.

### 2. Por qué una redeclaración no reemplaza la primera entrada
En un ámbito global, cada identificador debe mantener un único tipo de dato asociado durante toda su vida útil. Sobrescribir la entrada original invalidaría las comprobaciones de tipo ya realizadas en usos anteriores y generaría inconsistencias graves e irreversibles en el análisis del programa.

### 3. Por qué una entrada sintácticamente inválida no modifica la tabla
Las acciones semánticas (como `ts_declara` o `ts_usa`) se invocan explícitamente *después* de que el parser valida la construcción completa mediante `sscanf` y validaciones de formato. Si la sintaxis falla, la función retorna con un error sintáctico antes de llegar a la llamada de la acción semántica, dejando la tabla intacta.

## URL del repositorio
https://github.com/TecDeci2141/actividad06_semantica.git