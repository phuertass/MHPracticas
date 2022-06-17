#include "ILS.h"
#include "BL.h"
#include "ES.h"
#include "funciones.h"

using namespace std;

inline void Intercambia(Solucion &s1, Solucion &s2)
{
    Solucion aux = s1;
    s1 = s2;
    s2 = aux;
}

inline set<int> BuscarComplementarios(vector<int> seleccionados, int n, int tam)
{
    // Busco tam elementos que no esten en seleccionados desde 0 hasta n
    set<int> complementarios;

    while (complementarios.size() < tam)
    {
        int i = Random::get<int>(0, n - 1);
        if (find(seleccionados.begin(), seleccionados.end(), i) == seleccionados.end())
        {
            complementarios.insert(i);
        }
    }

    return complementarios;
}

void Mutar(Solucion &s, const double probabilidad, double **&matriz_datos, int n, int m)
{
    int t = probabilidad * m ;
    // cout << "t: " << t << endl;
    set<int> a_mutar;
    int rango = s.seleccionados.size();
    while (a_mutar.size() < t)
    {
        int elemento = Random::get(0, rango - 1);
        a_mutar.insert(elemento);
    }

    // MuestraVector("Posiciones de seleccionados para mutar", a_mutar);
    // for (auto it : a_mutar)
    //     cout << "Elemento: " << it << " es " << s.seleccionados[it] << endl;

    set<int> complementarios = BuscarComplementarios(s.seleccionados, n, a_mutar.size());

    // MuestraVector("Elementos complementarios para mutar", complementarios);
    // cout << endl;

    auto it = a_mutar.begin();
    auto it2 = complementarios.begin();
    auto itf = a_mutar.end();
    auto itf2 = complementarios.end();

    for (; it != itf; it++, it2++)
    {
        int pos1 = s.seleccionados[*it];
        int pos2 = *it2;
        // cout << "\nPosiciones a intercambiar: " << pos1 << " y " << pos2 << endl;
        SustituirPunto(s.distancias, make_pair(pos1, pos2), matriz_datos, s.seleccionados);
        // MuestraVector("Seleccionados temporal despues de sustituir", s.seleccionados);
    }

    CalculaDispersion(s.distancias, s.dispersion);
}

void Actualizar(Solucion &s, Solucion &s_mejor)
{
    if (s.dispersion < s_mejor.dispersion)
    {
        s_mejor = s;
    }else{
        s = s_mejor;
    }
}


inline void SolucionAleatoriaYDistancias(Solucion & s, int n, int m, double ** &matriz_datos, int semilla)
{
    Solucion s1;
    vector<pair<int, int>> vecindario;
    vector<int> restantes;

    s1.solucion = CalcularSolucionAleatoriaILS(n, m, semilla);
    for (int i = 0; i < s1.solucion.size(); i++)
            if (s1.solucion[i])
                s1.seleccionados.push_back(i);

    GeneraVDistancias(s1.distancias, s1.seleccionados, matriz_datos);
    CalculaDispersion(s1.distancias, s1.dispersion);

    s = s1;


}

void AlgoritmoILS(int n, int m, int semilla, double probabilidad_mutacion,
                  double probabilidad_cruce, Solucion &s, double **&matriz_datos)
{
    vector<pair<int, int>> vecindario;
    vector<int> restantes;

    // Generacion de la primera solucion aleatoria
    Solucion s1;
    SolucionAleatoriaYDistancias(s1, n, m, matriz_datos, semilla);
    BL(s1.seleccionados, vecindario, s1.dispersion, restantes, matriz_datos, s.distancias, n);

    Solucion s_mejor = s1;
    int iteraciones = 0;
    const double probabilidad = 0.3;

    // Repetimos 10 veces
    while (iteraciones < 10)
    {   
        cout << "ITERACION: " << iteraciones << endl;
        cout << "Pre if S1" << s1 << endl;
        cout << "Pre if S_mejor" << s_mejor << endl;
        // Mantenemos la mejor solucion
        if(s1.dispersion < s_mejor.dispersion){
            s_mejor = s1;
        }else{
            s1 = s_mejor;
        }
        cout << "Post if S1" << s1 << endl;
        cout << "Post if S_mejor" << s_mejor << endl;

        cout << "----------------------------------------------------" << endl;

        cout << "PremutacionBL s_mejor" << s_mejor << endl;
        // Mutamos la mejor solucion y volvemos a aplicar una busqueda local
        double probabilidad = 0.3;
        Mutar(s_mejor, probabilidad, matriz_datos, n, m);
        GeneraVDistancias(s_mejor.distancias, s_mejor.seleccionados, matriz_datos);
        CalculaDispersion(s_mejor.distancias, s_mejor.dispersion);
        BL(s_mejor.seleccionados, vecindario, s_mejor.dispersion, restantes, matriz_datos, s_mejor.distancias,n);
        cout << "PostmutacionBL s_mejor" << s_mejor << endl;


        cout << "-------------------------------------------------------------------------------------------------" << endl;
        cout << "-------------------------------------------------------------------------------------------------" << endl;
        cout << "-------------------------------------------------------------------------------------------------" << endl;
        cout << "-------------------------------------------------------------------------------------------------" << endl;


        iteraciones++;
    }

    if(s1.dispersion < s_mejor.dispersion){
        s_mejor = s1;
    }

    s = s_mejor;
}

void AlgoritmoILS_ES(int n, int m, int semilla, double probabilidad_mutacion,
                  double probabilidad_cruce, Solucion &s, double **&matriz_datos)
{
    vector<pair<int, int>> vecindario;
    vector<int> restantes;
    
    Solucion s1;
    SolucionAleatoriaYDistancias(s1, n, m, matriz_datos, semilla);
    AlgoritmoEnfriamientoSimulado(n, m, s1, matriz_datos, 10000);
    //cout << "Solucion pre ES" << s << endl;
    //AlgoritmoEnfriamientoSimulado(n, m, s, matriz_datos,100000);
    //cout << "Solucion post ES" << s << endl;

    Solucion s_mejor = s1;

    // Busqueda local sobre s_mejor

    int iteraciones = 0;
    while (iteraciones < 10)
    {
        
        if(s1.dispersion < s_mejor.dispersion){
            s_mejor = s1;
        }else{
            s1 = s_mejor;
        }
        // Mutamos la mejor solucion y volvemos a aplicar una busqueda local
        double probabilidad = 0.3;
        Mutar(s_mejor, probabilidad, matriz_datos, n, m);
        GeneraVDistancias(s_mejor.distancias, s_mejor.seleccionados, matriz_datos);
        CalculaDispersion(s_mejor.distancias, s_mejor.dispersion);

        //cout << "Pre ES final" << s_mejor << endl;
        AlgoritmoEnfriamientoSimulado(n, m, s_mejor, matriz_datos,10000);
        //cout << "Post ES final" << s_mejor << endl;
        iteraciones++;
    }

    if(s1.dispersion < s_mejor.dispersion){
        s_mejor = s1;
    }
    
    s = s_mejor;

}