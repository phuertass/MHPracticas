#include "BL.h"
#include "funciones.h"
#include "omp.h"
#include "BBO.h"
#include "ES.h"

using namespace std;

inline double GetSumatoria(vector<double> &distancias)
{
    double sumatoria = 0;
    for (int i = 0; i < distancias.size(); i++)
    {
        sumatoria += distancias[i];
    }
    return sumatoria;
}

inline double GetMedia(vector<double> &distancias)
{
    double media = 0;
    for (int i = 0; i < distancias.size(); i++)
    {
        media += distancias[i];
    }
    media /= distancias.size();
    return media;
}

inline void Reparacion(int n, int m, Solucion &s, double **&matriz_datos)
{
    // Se chequea la factibilidad de x. Si selecciona m elementos, no se hace nada
    int a_reparar = m - count(s.solucion.begin(), s.solucion.end(), true);

    double dispersion_actual = s.dispersion;

    // Calculamos la media de las distancias de los elementos seleccionados
    double media_distancias = 0;
    media_distancias = GetMedia(s.distancias);
    // cout<<"\nMedia de distancias es "<<media_distancias<<endl;
    if (a_reparar == 0)
        return;

    // Si sobran elementos, se van eliminando los más distantes a
    // la media hasta que sea factible
    if (a_reparar < 0)
    {
        while (a_reparar < 0)
        {
            // Buscamos el elemento que mas se aleja de la media
            int pos_mas_distante = 0;
            double mayor_lejania_a_media = 0;
            for (int i = 0; i < s.distancias.size(); i++)
            {
                if (abs(s.distancias[i] - media_distancias) > mayor_lejania_a_media)
                {
                    mayor_lejania_a_media = abs(s.distancias[i] - media_distancias);
                    pos_mas_distante = i;
                }
            }

            // Eliminamos el elemento mas distante
            s.solucion[s.seleccionados[pos_mas_distante]] = false;
            s.seleccionados.erase(s.seleccionados.begin() + pos_mas_distante);
            s.distancias.erase(s.distancias.begin() + pos_mas_distante);
            a_reparar++;
        }
    }
    // Si faltan elementos, se van añadiendo los más cercanos a la
    // media hasta que x sea factible
    else if (a_reparar > 0)
    {
        vector<int> seleccionados_aux = s.seleccionados;
        vector<double> distancias_aux = s.distancias;

        int pos_min = 0;
        while (a_reparar > 0)
        {
            // Buscamos el elemento no seleccionado que dismite la dispersion,
            // y lo seleccionamos
            double media_min = 9999999999999;
            double media_act;
            for (int i = 0; i < n; i++)
            {
                auto it = find(seleccionados_aux.begin(), seleccionados_aux.end(), i);
                if (it == seleccionados_aux.end())
                {
                    seleccionados_aux.push_back(i);
                    double distancia_tmp = 0;
                    int a_comparar = i;
                    GeneraVDistancias(distancias_aux, seleccionados_aux, matriz_datos);
                    CalculaDispersion(distancias_aux, distancia_tmp);

                    media_act = GetMedia(distancias_aux);
                    if (media_act < media_min)
                    {
                        media_min = media_act;
                        pos_min = i;
                    }

                    // Elimino el elemento de la lista de seleccionados y de la lista de distancias
                    seleccionados_aux.pop_back();
                    distancias_aux.pop_back();
                    GeneraVDistancias(distancias_aux, seleccionados_aux, matriz_datos);
                    CalculaDispersion(distancias_aux, distancia_tmp);
                }
            }
            a_reparar--;
        }
        s.seleccionados.push_back(pos_min);
        GeneraVDistancias(s.distancias, s.seleccionados, matriz_datos);
    }

    GeneraVDistancias(s.distancias, s.seleccionados, matriz_datos);
    CalculaDispersion(s.distancias, dispersion_actual);

    for (int i = 0; i < s.seleccionados.size(); i++)
    {
        s.solucion[s.seleccionados[i]] = true;
    }
}

inline int numero_elementos_seleccionados(const Solucion &s)
{
    return count(s.solucion.begin(), s.solucion.end(), true);
}
inline void CalcularMu(vector<Solucion> &p)
{
    const double TASA_MAXIMA_EMIGRACION = 1;
    const double n = p.size();
    int contador = 0;
    for (Solucion s : p)
    {
        // double calculo = TASA_MAXIMA_EMIGRACION * ( (contador+1) / n);
        double calculo = ((n + 1) - contador) / (n + 1);

        // s.prob_emigracion = 1-( TASA_MAXIMA_EMIGRACION * (contador / n));
        s.prob_emigracion = calculo;

        p[contador] = s;
        contador++;
    }
}

inline void CalcularLambda(vector<Solucion> &p)
{
    int contador = 0;
    for (Solucion s : p)
    {
        s.prob_inmigracion = 1 - s.prob_emigracion;
        p[contador] = s;
        contador++;
    }
}

inline void GetElites(const vector<Solucion> &p, vector<Solucion> &elites, int numero_elites)
{
    elites.clear();
    elites.resize(numero_elites);

    for (int i = 0; i < numero_elites; i++)
    {
        elites[i] = p[i];
    }
}

inline double SumatoriaMu(const vector<Solucion> &p)
{
    double suma = 0;
    for (Solucion s : p)
    {
        suma += s.prob_emigracion;
    }
    return suma;
}

inline void CalculoFuncionObjetivo(vector<Solucion> &p, double **&matriz_datos)
{
    // vector<int> seleccionados;
    for (int i = 0; i < p.size(); i++)
    {
        Solucion s = p[i];

        s.seleccionados.clear();
        for (int i = 0; i < s.solucion.size(); i++)
        {
            if (s.solucion[i])
            {
                s.seleccionados.push_back(i);
            }
        }
        GeneraVDistancias(s.distancias, s.seleccionados, matriz_datos);
        CalculaDispersion(s.distancias, s.dispersion);

        assert(count(s.solucion.begin(), s.solucion.end(), true) == s.seleccionados.size());
        p[i] = s;
    }
}

inline void Mutar(Solucion &s, int j, int m, int DIMENSION_PROBLEMA, double **&matriz_datos)
{
    // int n = s.solucion.size();
    // int m = s.seleccionados.size();

    bool elemento = s.solucion[j];
    int posicion = Random::get(0, DIMENSION_PROBLEMA);
    while (s.solucion[posicion] == elemento)
    {
        posicion = Random::get(0, DIMENSION_PROBLEMA);
    }
    int num_select = numero_elementos_seleccionados(s);
    if (num_select > m)
    {
        int random = Random::get<int>(0, DIMENSION_PROBLEMA);
        while (s.solucion[random])
        {
            random = Random::get<int>(0, DIMENSION_PROBLEMA);
        }
        s.solucion[random] = false;
    }
    else if (num_select < m)
    {
        int random = Random::get<int>(0, DIMENSION_PROBLEMA);
        while (!s.solucion[random])
        {
            random = Random::get<int>(0, DIMENSION_PROBLEMA);
        }
        s.solucion[random] = true;
    }

    bool aux = s.solucion[j];
    s.solucion[j] = s.solucion[posicion];
    s.solucion[posicion] = aux;
    s.seleccionados.clear();
    for (int i = 0; i < s.solucion.size(); i++)
    {
        if (s.solucion[i])
        {
            s.seleccionados.push_back(i);
        }
    }
    GeneraVDistancias(s.distancias, s.seleccionados, matriz_datos);
    CalculaDispersion(s.distancias, s.dispersion);
}

void AlgoritmoBBO(int n, int m, int semilla, const double probabilidad_mutacion, vector<Solucion> &poblacion, double **&matriz_datos)
{
    Random::seed(semilla);
    // Cantidad de mejores elementos que se quieren conservar entre generaciones
    const int NUMERO_ELITES = 5;
    // Numero de SIV por solucion
    const int DIMENSION_PROBLEMA = n;
    // Numero maximo de generaciones creadas
    const int TOPE_GENERACIONES = 1;
    // Tamaño de la poblacion
    const int TAMANIO_POBLACION = poblacion.size();

    const int SMAX = 20;

    const double PROB_MUTACION = probabilidad_mutacion;

    // Cada individuo de la poblacion se considera como un habitat (SIV)

    // Cuando una isla tiene SMAX especies, lamba = 0

    // La tasa maxima de emigracion ocurre cuando la isla tiene SMAX especies
    // La tasa maximo de inmigracion ocurre cuando la isla tiene 0 especies

    // Elites que se van a conservar entre generaciones
    vector<Solucion> elites;

    CalcularMu(poblacion);
    CalcularLambda(poblacion);

    int indice = 1;
    int num_iteraciones = 0;
    while (num_iteraciones < TOPE_GENERACIONES) // While stop criterion is not satisfied
    {
        if (num_iteraciones % 10 == 0)
        {
            int contador = 0;
            for (Solucion s : poblacion)
            {
                AlgoritmoEnfriamientoSimulado(n, m, s, matriz_datos, 10000);
                poblacion[contador] = s;
                contador++;
            }
        }
        // Lo primero que hacemos es ordenar en cada iteraciones la poblacion por fitness
        // Las soluciones con mejor fitnees (en este caso menor dispersion) se encuentran al principio
        OrdenarPorFitness(poblacion);

        // Para conversar el elitismo se van a guardar las mejores NUMERO_ELITES soluciones
        GetElites(poblacion, elites, NUMERO_ELITES);

        vector<Solucion> poblacion_temporal = poblacion;
        // Calculamos lambda(i) y mu(i) para cada una de las soluciones de la poblacion
        CalcularMu(poblacion_temporal);
        CalcularLambda(poblacion_temporal);

        //////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////
        // MIGRACION
        // Recorremos todas las soluciones de la poblacion actual
        // cout << "Poblacion actual: " << poblacion_temporal << endl;
        // cout << "Migracion" << endl;
        for (int i = 0; i < TAMANIO_POBLACION; i++)
        {
            Solucion s = poblacion[i];
            const double fitness = s.dispersion;
            const double mu = s.prob_emigracion;
            const double lambda = s.prob_inmigracion;
            // cout << "Fitness: " << fitness << " Mu: " << mu << " Lambda: " << lambda << endl;
            //  Recorremos cada elemento de la solucion
            for (int j = 0; j < DIMENSION_PROBLEMA; j++)
            {
                // Debemos migrar?
                if (Random::get<double>(0, 1) < lambda)
                {
                    // Realizamos la migracion

                    // Seleccionamos una isla emigrante con probabilidad mu
                    const double numero_random = Random::get<double>(0, SumatoriaMu(poblacion));
                    double seleccionado = poblacion[0].prob_emigracion;
                    int indice_seleccionado = 0;

                    while ((numero_random > seleccionado) && (indice_seleccionado < TAMANIO_POBLACION))
                    {
                        indice_seleccionado++;
                        seleccionado += poblacion[indice_seleccionado].prob_emigracion;
                    }
                    if (numero_elementos_seleccionados(poblacion_temporal[i]) != m)
                    {
                    }
                }
                else
                {
                }
            }
        }

        CalculoFuncionObjetivo(poblacion_temporal, matriz_datos);


        ///////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////
        // MUTACION
        for (int i = 0; i < TAMANIO_POBLACION; i++)
        {
            Solucion s = poblacion_temporal[i];
            for (int j = 0; j < DIMENSION_PROBLEMA; j++)
            {
                if (Random::get<double>(0, 1) < PROB_MUTACION)
                {
                    // cout << "hola"<< endl;
                    Mutar(s, j, m, DIMENSION_PROBLEMA, matriz_datos);
                }
            }
        }

        CalculoFuncionObjetivo(poblacion_temporal, matriz_datos);

        OrdenarPorFitness(poblacion_temporal);

        // cout << "#############################################################################################" << endl;
        // cout << "Poblacion actual: " << poblacion_temporal << endl;
        for (int i = 0; i < elites.size(); i++)
        {
            // cout << "Elite " << i << ": " << elites[i] << endl;
            // cout << "Peor elite " << i << ": " << poblacion_temporal[TAMANIO_POBLACION-1-i] << endl;
            poblacion_temporal[TAMANIO_POBLACION - i - 1] = elites[i];
        }
        poblacion = poblacion_temporal;
        num_iteraciones++;
        indice++;

        CalculoFuncionObjetivo(poblacion_temporal, matriz_datos);
    }

    OrdenarPorFitness(poblacion);
}