// Tarea1.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <omp.h>

#define N 100
#define chunk 10
#define mostrar 10

void imprimeArreglos(int inicio, float* a, float* b, float* r);
void imprimeFila(int inicio, int fin, float* d, std::string name);

int main()
{
    std::cout << "Sumando Arrreglos en Paralelo!\n";
    // Declaramos las variables necesarias
    float a[N], b[N], r[N];
    int i, inicio;
    float base1, base2;
    std::cout << "Ingresar base para arreglo A: ";
    std::cin >> base1;
    std::cout << "Ingresar base para arreglo B: ";
    std::cin >> base2;

    for (i = 0; i < N; i++)
    {
        a[i] = (i + 1) * base1;
        b[i] = (i + 1) * base2;
    }
    int pedazos = chunk;

    // `#pragma omp parallel for` indica que el for tiene que ejecutarse
    // de forma paralela
    // `shared` recibe las variables "a", "b", "r" y "pedazos" para marcarlas como compartidas
    // entre todos los hilos
    // `schedule` se encarga de distribuir las iteraciones en los hilos
    // el parametro "static" divide las iteraciones en bloques del mismo tamaño
    // especificamos el tamaño con la variable "pedazos" que es igual a 10
    #pragma omp parallel for shared(a, b, r, pedazos) private(i) \
    schedule(static, pedazos)
    for (i = 0; i < N; i++)
        r[i] = a[i] + b[i];

    std::cout << "Ingresar el indice inicial para mostrar: " << std::endl;
    std::cin >> inicio;
    imprimeArreglos(inicio, a, b, r);
}

void imprimeArreglos(int inicio, float* a, float* b, float* r)
{
    if (inicio > N)
        inicio = N - 1;
    int fin = inicio + mostrar;
    if (fin > N)
        fin = N;

    for (int x = 0; x < 10; x++)
        std::cout << "_______";
    std::cout << std::endl;
    imprimeFila(inicio, fin, a, "Arreglo A");

    std::cout << std::endl;
    imprimeFila(inicio, fin, b, "Arreglo B");

    std::cout << std::endl;
    imprimeFila(inicio, fin, r, "Arreglo R");
}

void imprimeFila(int inicio, int fin, float* d, std::string name)
{
    std::cout << "| " << name << " | ";
    for (int x = inicio; x < fin ; x++)
        std::cout << std::setw(5) << d[x] << " | ";
    std::cout << std::endl;
}

