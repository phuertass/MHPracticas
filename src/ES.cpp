#include "ES.h"
#include "BL.h"
#include "funciones.h"

using namespace std;

Solucion CalcularSolucionVecinaAleatoria(int n, int m, const Solucion &s, double **&matriz_datos)
{
    int elemento = Random::get<int>(0, s.seleccionados.size() - 1);
    int elemento_2 = Random::get<int>(0, n - 1);
    while (s.seleccionados[elemento] == elemento_2)
        elemento_2 = Random::get<int>(0, n - 1);

    Solucion solucion_vecina = s;

    SustituirPunto(solucion_vecina.distancias, make_pair(s.seleccionados[elemento], elemento_2), matriz_datos, solucion_vecina.seleccionados);
    CalculaDispersion(solucion_vecina.distancias, solucion_vecina.dispersion);
    return solucion_vecina;
}

inline double CalcularTInicial(const double mu, const Solucion &s)
{
    double log_n = log(mu);
    double dispersion = s.dispersion;

    double t_inicial = (mu * dispersion) / -(log_n);
    return t_inicial;
}

inline double CalcularBeta(const double t_inicial, const double t_final, const int M)
{
    double beta = (t_inicial - t_final) / (t_inicial * t_final * M);
    return beta;
}

inline double CalcularTK1(const double t_k, const double beta)
{
    double t_k1 = t_k / (1 + (beta * t_k));
    return t_k1;
}

void AlgoritmoEnfriamientoSimulado(int n, int m, Solucion &s, double **&matriz_datos, int num_ev_maximo)
{
    const double temperatura_final = 0.001;
    const double mu = 0.3;
    const double t_inicial = CalcularTInicial(mu, s);
    const int max_vecinos = 10 * n;
    const int max_exitos = 0.1 * max_vecinos;

    double temperatura_actual = t_inicial;
    int numero_iteraciones_ES = 100000 / max_vecinos;
    int numero_enfriamientos = numero_iteraciones_ES;

    int iteraciones = 0;
    Solucion s_mejor = s;
    int num_evaluaciones = 0;

    while ((temperatura_actual > temperatura_final) and (iteraciones < numero_iteraciones_ES) and (num_evaluaciones < num_ev_maximo))
    {
        // For count 1 to l(t) do
        int exitos = 0;
        for (int i = 0; i < max_vecinos && exitos < max_exitos; i++)
        {
            // Generacion de una nueva solucion
            Solucion vecino = CalcularSolucionVecinaAleatoria(n, m, s, matriz_datos);
            num_evaluaciones++;

            // Calculo de la diferencia de costos
            double delta_dispersion = vecino.dispersion - s.dispersion;

            // Aplicacion del criterio de aceptacion
            double probabilidad = exp(-delta_dispersion / temperatura_actual);

            // Si la solucion es mejor que la actual, la actual se cambia por la nueva siempre
            // Si la generacion del numero aleatorio entre 0 y 1 es menor que la probabilidad de aceptacion,
            // tampoco se cambia la solucion actual
            if ((delta_dispersion < 0) or (Random::get<double>(0, 1) < probabilidad))
            {
                s = vecino;
                exitos++;
            }

            // Comnparamos la solucion actual con la mejor hasta el momento y actualizamos
            if (s.dispersion < s_mejor.dispersion)
                s_mejor = s;
        }

        // Mecanismo de enfriamiento
        double beta = CalcularBeta(t_inicial, temperatura_final, numero_enfriamientos);
        temperatura_actual = CalcularTK1(temperatura_actual, beta);
        iteraciones++;
    }

    s = s_mejor;
}