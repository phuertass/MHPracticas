#include <iostream>
#include <random>
#include <vector>
#include <omp.h>
#include <chrono>
#include <ctime>
#include <set>
#include "funciones.h"
#include "random.h"
//#include "Memetico.h"
//#include "Cruces.h"
#include "BBO.h"

using namespace std;
using Random = effolkronium::random_static;

#define VECES 5

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
    vector<int> semillas = {1, 2, 3, 4, 5};
    vector<dato> vector_datos;
    vector<double> distancias;
    resultado r;

    cin >> n;
    cin >> m;

    // cout<<"N: "<<n<<" M: "<<m<<endl;

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
    const double probabilidad_mutacion = 0.004;

    int posicion_mejor_solucion = 0;
    Solucion mejor_sol;
    vector<Solucion> poblacion;

    vector<pair<string, double>> tiempos;
    vector<resultado> resultados;

    // PRUEBA DE CORRECTO FUNCIONAMIENTO DEL ALGORITMO
    CalcularPoblacionAleatoria(n, m, poblacion, semilla, matriz_datos, 100);

    posicion_mejor_solucion = 0;
    mejor_sol = GetMejor(poblacion, posicion_mejor_solucion);

    chrono::high_resolution_clock::time_point t1;
    chrono::high_resolution_clock::time_point t2;
    chrono::duration<double> time_span;

    t1 = chrono::high_resolution_clock::now();
    AlgoritmoBBO(n, m, semilla, probabilidad_mutacion, poblacion, matriz_datos);
    t2 = chrono::high_resolution_clock::now();
    time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);



    posicion_mejor_solucion = 0;
    mejor_sol = GetMejor(poblacion, posicion_mejor_solucion);

    cout << "Solucion" << mejor_sol << endl;

    r = {"BBO", mejor_sol.dispersion, time_span.count()};
    resultados.push_back(r);

    for (int i = 0; i < resultados.size(); i++)
    {
        cout << resultados[i].algoritmo << "\t" << resultados[i].dispersion << endl;
        cout << "T" << resultados[i].algoritmo << "\t" << resultados[i].tiempo << endl;
    }


    //cout << count (mejor_sol.solucion.begin(), mejor_sol.solucion.end(), true);
    //cout << endl;

    return 0;
}