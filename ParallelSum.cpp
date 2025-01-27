// ParallelSum.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.

#include "pch.h"
#include <iostream>
#include <omp.h>
#include <chrono>
#include <iomanip> 

#define N 9000
#define chunk 30
#define mostrar 10

void imprimirArreglo(float *d, const std::string& nombre, int cantidad);
void imprimirTiempoEjecucion(const std::chrono::high_resolution_clock::time_point& inicio,
	const std::chrono::high_resolution_clock::time_point& fin,
	const std::string& tipo);

int main() {
	std::cout << "Suma de un arreglo con OpenMP" << std::endl;
	std::cout << "Con " << N << " elementos en cada arreglo " << std::endl;
	// Declarar arreglos
	float a[N], b[N], c_n[N], c_p[N];

	int i;
	for (i = 0; i < N; i++) {
		a[i] = (i * 50) - 15;
		b[i] = (i + 75) / 3.7;
	}

	int pedazos = chunk;

	// Ejecutar suma normal
	auto inicio_normal = std::chrono::high_resolution_clock::now();
	for (i = 0; i < N; i++) {
		c_n[i] = a[i] + b[i];
	}
	auto fin_normal = std::chrono::high_resolution_clock::now();

	// Ejecutar suma paralela
	std::cout << "Numero de nucleos disponibles: " << omp_get_num_procs() << std::endl;
	auto inicio_paralelo = std::chrono::high_resolution_clock::now();
	#pragma omp parallel \
	for shared(a, b, c_p, pedazos) \
	private(i) schedule(static, pedazos)
	for (i = 0; i < N; i++) {
		c_p[i] = a[i] + b[i];
	}
	auto fin_paralelo = std::chrono::high_resolution_clock::now();
	
	// Imprimir resultados 
	imprimirArreglo(a, "A", mostrar);
	imprimirArreglo(b, "B", mostrar);
	imprimirArreglo(c_n, "C Normal", mostrar);
	imprimirArreglo(c_p, "C Paralelo", mostrar);

	// Imprimir tiempos de ejecución
	imprimirTiempoEjecucion(inicio_normal, fin_normal, "normal");
	imprimirTiempoEjecucion(inicio_paralelo, fin_paralelo, "paralelo");	
}

void imprimirArreglo(float *d, const std::string& nombre, int cantidad) {
	std::cout << "Imprimiendo " << cantidad << " elementos del arreglo " << nombre << std::endl;
	for (int i = 0; i < cantidad; i++)
		std::cout << d[i] << " | ";
	std::cout << std::endl;
}

void imprimirTiempoEjecucion(const std::chrono::high_resolution_clock::time_point& inicio,
	const std::chrono::high_resolution_clock::time_point& fin,
	const std::string& tipo) {
	auto duracion_us = std::chrono::duration<double>(fin - inicio) * 1000000.0;
	// Imprimir en microsegundos
	std::cout << std::fixed << std::setprecision(3);
	std::cout << "Tiempo de ejecucion (" << tipo << "): "
		<< duracion_us.count() << " microsegundos" << std::endl;
}