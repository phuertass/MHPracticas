#include "funciones.h"
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

    ////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////
    // PARAMETROS DEL BBO
    ////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////

    // Numero de SIV por solucion
    const int DIMENSION_PROBLEMA = n;

    // Numero maximo de generaciones creadas
    const int TOPE_GENERACIONES = 1;

    // Tamaño de la poblacion
    const int TAMANIO_POBLACION = poblacion.size();

    // Cantidad de mejores elementos que se quieren conservar entre generaciones
    const int NUMERO_ELITES = 0.2*TAMANIO_POBLACION;

    // Numero de nuevos habitats a generar
    const int NUMERO_NUEVOS_HABITANTES = TAMANIO_POBLACION - NUMERO_ELITES;



    ////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////
    // VARIABLES DE MIGRACION
    ////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////
    const double PROB_MUTACION = 0.05;
    const double alpha = 0.9;
    vector<double> mu(TAMANIO_POBLACION);
    vector<double> lambda(TAMANIO_POBLACION);
    for (int i = 0; i < TAMANIO_POBLACION; i++)
    {
        double calculo = double((TAMANIO_POBLACION + 1) - i) / (TAMANIO_POBLACION + 1);

        mu[i] = calculo;
        lambda[i] = 1 - calculo;
    }


    ////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////
    // INICIALIZACION DEL ALGORITMO
    ////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////

    // Lo primero que hacemos es ordenar en cada iteraciones la poblacion por fitness
    // Las soluciones con mejor fitnees (en este caso menor dispersion) se encuentran al principio
    OrdenarPorFitness(poblacion);

    // Para conversar el elitismo se van a guardar las mejores NUMERO_ELITES soluciones
    vector<Solucion> elites;
    GetElites(poblacion, elites, NUMERO_ELITES);


    ////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////
    // BUCLE PRINCIPAL DEL ALGORITMO BBO
    ////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////

    for (int num_iteraciones = 0; num_iteraciones < TOPE_GENERACIONES; num_iteraciones++) // While stop criterion is not satisfied
    {

        // CREAMOS COPIA DE LA POBLACION
        vector<Solucion> nuevas_soluciones = poblacion;

        for (int i = 0; i < TAMANIO_POBLACION; i++)
        {
            for (int j = 0; j < DIMENSION_PROBLEMA; j++)             //  Recorremos cada elemento de la solucion
            {
                /////////////////////////////////////////////////////////////////////////////////////////////
                // MIGRACION
                /////////////////////////////////////////////////////////////////////////////////////////////
                if (Random::get<double>(0, 1) < lambda[i])
                {
                    // Realizamos la migracion
                    // Seleccionamos una isla emigrante con probabilidad mu
                    vector<double> probabilidades_emigracion(mu);
                    probabilidades_emigracion[i] = 0;

                    int emigrante = IndiceRouletteWheel(probabilidades_emigracion);

                    cout << "Elemento emigrante es: " << emigrante << endl;
                    // EL INDICE EMIGRANTE INDICA EL ELEMENTO DEL HABITAT I QUE SE VA A MIGRAR

                }

                /////////////////////////////////////////////////////////////////////////////////////////////
                // MUTACION
                /////////////////////////////////////////////////////////////////////////////////////////////
                if (Random::get<double>(0, 1) < PROB_MUTACION)
                {
                    // Realizamos la mutacion
                    nuevas_soluciones[i].solucion[j] = !nuevas_soluciones[i].solucion[j];
                }

                CalculoFuncionObjetivo(nuevas_soluciones, matriz_datos);
        
            }


            OrdenarPorFitness(nuevas_soluciones);
            for (int i = 0; i < NUMERO_ELITES; i++)
                nuevas_soluciones[TAMANIO_POBLACION - i - 1] = elites[i];
            CalculoFuncionObjetivo(nuevas_soluciones, matriz_datos);

            poblacion = nuevas_soluciones;
        }
    }

    OrdenarPorFitness(poblacion);

    //for (int i = 0; i < poblacion.size(); i++)
    //{
    //    Solucion s = poblacion[i];
    //    AlgoritmoEnfriamientoSimulado(n, m, s, matriz_datos, 10000);
    //    poblacion[i] = s;
    //}
    CalculoFuncionObjetivo(poblacion, matriz_datos);
}