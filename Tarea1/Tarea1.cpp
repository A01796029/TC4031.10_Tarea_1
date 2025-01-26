// Tarea1.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <omp.h>

#define N 100
#define chunk 10
#define mostrar 10

void imprimeArreglos(float* a, float* b, float* r);
void imprimeFila(float* d, std::string name);

int main()
{
    std::cout << "Sumando Arrreglos en Paralelo!\n";
    float a[N], b[N], r[N];
    int i;
    float base1, base2;
    std::cout << "Ingresar base para arreglo A: ";
    std::cin >> base1;
    std::cout << "Ingresar base para arreglo B: ";
    std::cin >> base2;

    for (i = 0; i < N; i++)
    {
        a[i] = i * base1;
        b[i] = i * base2;
    }
    int pedazos = chunk;

    #pragma omp parallel for \
    shared(a, b, r, pedazos) private(i) \
    schedule(static, pedazos)

    for (i = 0; i < N; i++)
        r[i] = a[i] + b[i];

    std::cout << "Imprimiendo los primeros " << mostrar << " valores de los arreglos: " << std::endl;
    imprimeArreglos(a, b, r);
}

void imprimeArreglos(float* a, float* b, float* r)
{
    for (int x = 0; x < mostrar; x++)
        std::cout << "_______";
    std::cout << std::endl;
    imprimeFila(a, "Arreglo A");

    std::cout << std::endl;
    imprimeFila(b, "Arreglo B");

    std::cout << std::endl;
    imprimeFila(r, "Arreglo R");
}

void imprimeFila(float* d, std::string name)
{
    std::cout << "| " << name << " | ";
    for (int x = 0; x < mostrar; x++)
        std::cout << std::setw(5) << d[x] << " | ";
    std::cout << std::endl;
}

