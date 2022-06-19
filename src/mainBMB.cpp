#include <iostream>
#include <random>
#include <vector>
#include <omp.h>
#include <chrono>
#include <ctime>
#include <set>
#include "funciones.h"
#include "random.h"
#include "Cruces.h"
#include "ES.h"
#include "BMB.h"
#include "ILS.h"

using namespace std;
using Random = effolkronium::random_static;

typedef struct
{
    string algoritmo;
    double dispersion;
    double tiempo;
} resultado;

int main()
{
    const int TOPE = 100;
    char cadena_lectura[TOPE];
    int n;
    int m;
    vector<dato> vector_datos;
    resultado r;

    cin >> n;
    cin >> m;

    dato f;
    int total_utilizados = 0;
    while (cin.getline(cadena_lectura, TOPE))
    {

        dato f = Dividir_Cadena_Clasificar(cadena_lectura);

        if (f.distancia != 0)
        {
            vector_datos.push_back(f);

            total_utilizados++;
        }
    }

    double **matriz_datos = new double *[n];

    for (int i = 0; i < n; i++)
    {
        matriz_datos[i] = new double[n];
    }

    int i = 0;
    for (auto it = vector_datos.begin(); it != vector_datos.end(); it++, i++)
    {
        dato d = *it;
        matriz_datos[d.i][d.j] = d.distancia;
        matriz_datos[d.j][d.i] = d.distancia;
    }

    // La poblacion va a ser un vector que contiene todos las soluciones creadas,
    // y la dispersion obtenida por evaluar estos
    int semilla = 1;
    double probabilidad_mutacion = 0.1;
    double probabilidad_cruce = 0.7;
    int posicion_mejor_solucion = 0;

    vector<pair<string, double>> tiempos;
    vector<resultado> resultados;
    chrono::high_resolution_clock::time_point t1;
    chrono::high_resolution_clock::time_point t2;
    chrono::duration<double> time_span;

    //////////////////////////////////////////////////////////////////////////////
    // Calculo de las 10 soluciones aleatorias
    Random::seed(semilla);
    vector<Solucion> poblacion;
    Solucion mejor_sol;
    CalcularPoblacionAleatoria(n, m, poblacion, semilla, matriz_datos, 100);

    //cout << poblacion << endl;

    mejor_sol = GetMejor(poblacion, posicion_mejor_solucion);
    //cout << "Mejor solucion: " << mejor_sol << endl;

    t1 = chrono::high_resolution_clock::now();
    AlgoritmoMultiarranqueBasico(n, m, semilla, probabilidad_mutacion, probabilidad_cruce, poblacion, matriz_datos);
    t2 = chrono::high_resolution_clock::now();
    time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);

    //cout << poblacion << endl;

    posicion_mejor_solucion = 0;
    mejor_sol = GetMejor(poblacion, posicion_mejor_solucion);
    tiempos.push_back(make_pair("BMB", mejor_sol.dispersion));

    r = {"BMB", mejor_sol.dispersion, time_span.count()};
    resultados.push_back(r);

    for (int i = 0; i < resultados.size(); i++)
    {
        cout << "----------------------------------------------------" << endl;
        cout << resultados[i].algoritmo << "\t" << resultados[i].dispersion << endl;
        cout << "Tiempo" << resultados[i].algoritmo << "\t" << resultados[i].tiempo << endl;
        cout << "----------------------------------------------------" << endl;
    }

    return 0;
}