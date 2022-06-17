#include "BMB.h"
#include "BL.h"
#include "funciones.h"
#include "omp.h"

using namespace std;

void AlgoritmoMultiarranqueBasico(int n, int m, int semilla, double probabilidad_mutacion,
                                  double probabilidad_cruce, vector<Solucion> &poblacion, double **&matriz_datos)
{
    vector<pair<int, int>> vecindario;
    vector<int> restantes;
    int num_iteraciones = 0;
    while (num_iteraciones < 10)
    {
        //#pragma omp parallel for private(vecindario, restantes) num_threads(10)
        for (int i = 0; i < poblacion.size(); i++)
        {
            Solucion s = poblacion[i];
            BL(s.seleccionados, vecindario, s.dispersion, restantes, matriz_datos, s.distancias, n);
            poblacion[i] = s;
        }
        num_iteraciones++;
    }
}