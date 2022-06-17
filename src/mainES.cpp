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
#include "BL.h"

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
    Random::seed(semilla);
    double probabilidad_mutacion = 0.1;
    double probabilidad_cruce = 0.7;
    int posicion_mejor_solucion = 0;
    Solucion mejor_sol;
    vector<Solucion> poblacion;

    vector<pair<string, double>> tiempos;
    vector<resultado> resultados;
    chrono::high_resolution_clock::time_point t1;
    chrono::high_resolution_clock::time_point t2;
    chrono::duration<double> time_span;

    //////////////////////////////////////////////////////////////////////////////
    // Calculo de la primera solucion aleatoria
    Solucion s;
    s.solucion = CalcularSolucionAleatoriaILS(n, m, semilla);
    for (int i = 0; i < s.solucion.size(); i++)
    {
        if (s.solucion[i])
        {
            s.seleccionados.push_back(i);
        }
    }
    GeneraVDistancias(s.distancias, s.seleccionados, matriz_datos);
    CalculaDispersion(s.distancias, s.dispersion);
    //cout << s;
    //cout << "--------------------------------------------------------------------------------" << endl;

    t1 = chrono::high_resolution_clock::now();
    AlgoritmoEnfriamientoSimulado(n, m, s, matriz_datos, 100000);
    t2 = chrono::high_resolution_clock::now();
    time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);

    posicion_mejor_solucion = 0;
    mejor_sol = s;
    tiempos.push_back(make_pair("ES", mejor_sol.dispersion));
    //cout << "--------------------------------------------------------------------------------" << endl;
    //cout << "Solucion final \n" << mejor_sol;

    r = {"ES", mejor_sol.dispersion, time_span.count()};
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