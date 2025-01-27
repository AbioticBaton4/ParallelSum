# Suma de Arreglos en Paralelo con OpenMP

Este repositorio contiene un ejemplo práctico de programación paralela en C++ utilizando la biblioteca **OpenMP**. El programa implementa una operación de suma de arreglos, comparando el rendimiento de una solución secuencial (normal) con una paralela.

## Contenido

- **Archivo principal**: `ParallelSum.cpp`
- **Descripción**: Se genera un conjunto de arreglos de tamaño predefinido, se realizan sumas secuenciales y paralelas, y se mide el tiempo de ejecución de ambas operaciones.

## Requisitos

Antes de ejecutar el programa, asegúrate de cumplir con los siguientes requisitos:

- **Compilador compatible con OpenMP**, como:
  - GCC (añadiendo la bandera `-fopenmp`)
  - Clang
  - Microsoft Visual Studio (configurado para soportar OpenMP)
- C++17 o superior.
- Sistema operativo con soporte para múltiples núcleos.

## Cómo Compilar

1. Clona este repositorio:
   ```bash
   git clone https://github.com/tu-usuario/tu-repo.git
   cd tu-repo
   ```
2. Compila el programa:
   - Usando GCC:
     ```bash
     g++ -o ParallelSum ParallelSum.cpp -fopenmp
     ```
   - Usando Microsoft Visual Studio, habilita OpenMP desde las propiedades del proyecto.

## Ejecución

Ejecuta el programa compilado:

```bash
./ParallelSum
```

El programa:

1. Crea dos arreglos `A` y `B` de tamaño `N` (por defecto, 9000).
2. Realiza una suma secuencial y paralela, almacenando el resultado en `C Normal` y `C Paralelo`.
3. Muestra los primeros 10 elementos de cada arreglo.
4. Calcula el tiempo de ejecución de ambas estrategias y lo imprime en microsegundos.

## Funcionalidades Principales

### Variables Globales

- `N`: Tamaño de los arreglos (por defecto, 9000).
- `chunk`: Tamaño del bloque que se divide entre los hilos en la suma paralela (por defecto, 30).
- `mostrar`: Número de elementos a mostrar de cada arreglo (por defecto, 10).

### Principales Funciones

- `imprimirArreglo`: Imprime los elementos seleccionados de un arreglo.
- `imprimirTiempoEjecucion`: Calcula y muestra el tiempo transcurrido entre dos puntos de referencia.

### Uso de OpenMP

La suma paralela se implementa mediante la siguiente directiva:

```cpp
#pragma omp parallel \
for shared(a, b, c_p, pedazos) \
private(i) schedule(static, pedazos)
```

Esta instrucción divide las iteraciones del bucle entre los hilos disponibles, utilizando un esquema estático con bloques de tamaño `chunk`.

## Ejemplo de Salida

```plaintext
Suma de un arreglo con OpenMP
Con 9000 elementos en cada arreglo
Numero de nucleos disponibles: 8
Imprimiendo 10 elementos del arreglo A
0 | 35 | 100 | 165 | 230 | 295 | 360 | 425 | 490 | 555 |
Imprimiendo 10 elementos del arreglo B
20.2703 | 21.0811 | 21.8919 | 22.7027 | 23.5135 | 24.3243 | 25.1351 | 25.9459 | 26.7568 | 27.5676 |
Imprimiendo 10 elementos del arreglo C Normal
20.2703 | 56.0811 | 121.892 | 187.703 | 253.514 | 319.324 | 385.135 | 450.946 | 516.757 | 582.568 |
Imprimiendo 10 elementos del arreglo C Paralelo
20.2703 | 56.0811 | 121.892 | 187.703 | 253.514 | 319.324 | 385.135 | 450.946 | 516.757 | 582.568 |
Tiempo de ejecucion (normal): 3218.947 microsegundos
Tiempo de ejecucion (paralelo): 1723.411 microsegundos
```

## Contribuciones

Las contribuciones son bienvenidas. Por favor, abre un *issue* o envía un *pull request* con tus mejoras o sugerencias.

## Licencia

Este proyecto está licenciado bajo la [MIT License](LICENSE).

