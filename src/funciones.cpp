#include "funciones.h"
using Random = effolkronium::random_static;

dato Dividir_Cadena_Clasificar(string cadena)
{
    stringstream input(cadena);
    string i, j;
    string distancia;
    dato d;

    getline(input, i, ' ');
    getline(input, j, ' ');
    getline(input, distancia, ' ');

    char a[100];
    strcpy(a, distancia.c_str());
    d.i = atoi(i.c_str());
    d.j = atoi(j.c_str());
    d.distancia = atof(a);
    return d;
};

void MuestraVector(string cad, vector<dato> &vector_datos)
{
    cout << cad << endl;
    int i = 0;
    for (auto it = vector_datos.begin(); it < vector_datos.end(); it++, i++)
    {
        cout << "(" << i << ")" << (*it).i << " " << (*it).j << " " << setprecision(10) << (*it).distancia
             << endl;
    }
}

void MuestraVector(string cad, vector<int> &vector_datos)
{
    cout << cad << endl;
    for (auto it = vector_datos.begin(); it < vector_datos.end(); it++)
    {
        cout << "|" << (*it) << "|";
    }
    cout << endl;
}

void MuestraVector(string cad, vector<double> &vector_datos)
{
    cout << cad << endl;
    for (auto it = vector_datos.begin(); it < vector_datos.end(); it++)
    {
        cout << "|" << (*it) << "|";
    }
    cout << endl;
}

void MuestraVector(string cad, set<int> &vector_datos)
{
    cout << cad << endl;
    for (auto it = vector_datos.begin(); it != vector_datos.end(); it++)
    {
        cout << "|" << (*it) << "|";
    }
    cout << endl;
}

void MuestraVector(string cad, vector<bool> &v)
{
    cout << cad << endl;
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}

void MuestraDato(const dato d)
{
    cout << d.i << " " << d.j << " " << setprecision(10) << d.distancia
         << endl;
}

void CopiaVector(vector<dato> &destino, vector<dato> origen)
{
    for (auto it = origen.begin(); it != origen.end(); it++)
    {
        destino.push_back(*it);
    }
};

void CopiaVector(vector<int> &destino, vector<int> origen)
{
    for (auto it = origen.begin(); it != origen.end(); it++)
    {
        destino.push_back(*it);
    }
};

void RellenaVector(vector<int> &vector, int tamanio)
{
    for (int i = 0; i < tamanio; i++)
        vector.push_back(i);
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void GeneraVDistancias(vector<double> &distancias, const vector<int> &seleccionados, double **&matriz)
{
    distancias.clear();

    distancias.resize(seleccionados.size(), 0);

    //for (int i : distancias)
    //    distancias[i] = 0;

//    cout << "Generando distancias..." << endl;
//    cout << "Seleccionados: ";
//    for (int i = 0; i < seleccionados.size(); i++)
//    {
//        cout << seleccionados[i] << " ";
//    }
//    cout << endl;
    

    int contador = 0;
    int tamanio_seleccionados = seleccionados.size();
    for (auto it = seleccionados.cbegin(); it != seleccionados.cend(); it++, contador++)
    {
        int a_comparar = *it;
        for (int i = 0; i < tamanio_seleccionados; i++)
        {
            if (seleccionados[i] != a_comparar)
                distancias[contador] += matriz[a_comparar][seleccionados[i]];
        }
    }


};

void Intercambia(vector<int> &Seleccionados, int original, int nuevo, vector<double> &distancias, double &dispersion)
{
    Seleccionados[original] = nuevo;
};
void CalculaDispersion(vector<double> distancias, double &dispersion)
{
    // Calculamos la distancia maxima y la distancia minima
    //double maximo = *max_element(distancias.begin(), distancias.end());
    //double minimo = *min_element(distancias.begin(), distancias.end());
    double maximo = -1;
    for (auto it = distancias.begin(); it != distancias.end(); it++)
    {
        if (*it > maximo)
            maximo = *it;
    }
    double minimo = maximo;
    for (auto it = distancias.begin(); it != distancias.end(); it++)
    {
        if (*it < minimo)
            minimo = *it;
    }


    //cout << "Maximo: " << maximo << endl;
    //cout << "Minimo: " << minimo << endl;
    
    // Calculamos la dispersion que es la diferencia entre la distancia maxima y la minima
    dispersion = maximo - minimo;
    //cout << "Dispersion: " << dispersion << endl;
};
void SustituirPunto(vector<double> &copia_dist, const pair<int,int> pareja, double **&matriz,
vector<int> & seleccionados)
{
    int posicion_a_sustituir = pareja.first;
    int posicion_sustituir = pareja.second;
    double suma=0;
    int posicion;
    for(int i=0; i<seleccionados.size(); i++)
    {
        if(seleccionados[i]==pareja.first)
            posicion = i;
        else{
            copia_dist[i] -= matriz[seleccionados[i]][posicion_a_sustituir];
            copia_dist[i] += matriz[seleccionados[i]][posicion_sustituir];
            suma+= matriz[seleccionados[i]][posicion_sustituir]; 
        }  
    }

    seleccionados[posicion ] = posicion_sustituir;
    copia_dist[posicion]=suma;
}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
// Funciones de la practica 2
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
// Funciones de Poblacion
/////////////////////////////////////////////////////////////////////////////////////


void CalcularPoblacionAleatoria(int n, int m, vector<Solucion> &p, int semilla, double **&matriz_datos, int tam_poblacion)
{

    vector<int> seleccionados;
    Random::seed(semilla);
    p.clear();
    for (int i = 0; i < tam_poblacion; i++)
    {
        Solucion s;

        s.solucion = CalcularSolucionAleatoria(n, m, semilla);

        seleccionados.clear();
        for (int i = 0; i < s.solucion.size(); i++)
        {
            if (s.solucion[i])
            {
                seleccionados.push_back(i);
            }
        }
        GeneraVDistancias(s.distancias, seleccionados, matriz_datos);
        CalculaDispersion(s.distancias, s.dispersion);

        s.seleccionados = seleccionados;

        p.push_back(s);
    }
}

void OrdenarPorFitness(vector<Solucion> &poblacion)
{
    sort(poblacion.begin(), poblacion.end(), [](const Solucion &a, const Solucion &b) { return a.dispersion < b.dispersion; });
}


vector<bool> CalcularSolucionAleatoria(int n, int m, int semilla)
{
    vector<bool> solucion(n, false);
    set<int> seleccionados;

    //Random::seed(semilla);

    // Calcula una solucion aleatoria de n elementos con m elementos seleccionados
    // con representacion de vector booleano
    while (seleccionados.size() < m)
    {
        int pos = Random::get(0, n - 1);
        seleccionados.insert(pos);
    }

    for (int i : seleccionados)
    {
        solucion[i] = true;
    }

    return solucion;
}



Solucion GetMejor(const vector<Solucion> &poblacion, int &posicion)
{
    // Busco la mejor solucion de la poblacion
    Solucion mejor_solucion = poblacion[0];
    for (int i = 1; i < poblacion.size(); i++)
    {
        if (poblacion[i].dispersion < mejor_solucion.dispersion)
        {
            mejor_solucion = poblacion[i];
            posicion = i;
        }
    }
    return mejor_solucion;
}

Solucion GetPeor(const vector<Solucion> &poblacion, int &posicion)
{
    Solucion peor_solucion = poblacion[0];
    posicion = 0;
    for (int i = 1; i < poblacion.size(); i++)
    {
        if (poblacion[i].dispersion > peor_solucion.dispersion)
        {
            peor_solucion = poblacion[i];
            posicion = i;
        }
    }
    return peor_solucion;
}

bool EstaPosicion(const vector<Solucion> &poblacion, const Solucion &s, int &posicion)
{
    for (int i = 0; i < poblacion.size(); i++)
    {
        if (poblacion[i].solucion == s.solucion)
        {
            posicion = i;
            return true;
        }
    }
    return false;
}



void MutacionPoblacion(vector<Solucion> & poblacion, const double probabilidad, const int semilla){
    Random::seed(semilla);
    int tam_poblacion = poblacion.size();
    int numero_esperado_mutaciones = probabilidad*tam_poblacion;
    int tam_soluciones = poblacion[0].solucion.size();

    int rango_mutacion = tam_soluciones*tam_poblacion-1;

    vector<int> a_mutar;
    while(a_mutar.size()<numero_esperado_mutaciones){
        int pos = Random::get(0,rango_mutacion);
        if(find(a_mutar.begin(), a_mutar.end(), pos) == a_mutar.end()){
            a_mutar.push_back(pos);
        }
    }
    

    for(int i=0; i<numero_esperado_mutaciones; i++){
        
        int x1 = a_mutar.back();
        a_mutar.pop_back();
        int solucion_a_mutar = x1/tam_soluciones;
        int pos_a_mutar = x1%tam_soluciones;

        int x2 = pos_a_mutar;
        while(poblacion[solucion_a_mutar].solucion[pos_a_mutar]==poblacion[solucion_a_mutar].solucion[x2]){
            x2 = Random::get(0,tam_soluciones-1);
        }   

        //Intercambio dichas posiciones
        bool tmp = poblacion[solucion_a_mutar].solucion[pos_a_mutar];
        poblacion[solucion_a_mutar].solucion[pos_a_mutar] = poblacion[solucion_a_mutar].solucion[x2];
        poblacion[solucion_a_mutar].solucion[x2] = tmp;
        //cout<<"Intercambio "<<pos_a_mutar<<" con "<<x2<<" en la solucion "<<solucion_a_mutar<<endl;


    }
}

int IndiceRouletteWheel(const vector<double> & probabilidades_emigraciones)
{
    double fsum = 0;
    for(double p : probabilidades_emigraciones){
        fsum += p;
    }

    double cumsum = 0;
    double r = Random::get<double>(0,int(fsum));

    for(int i=0; i<probabilidades_emigraciones.size(); i++){
        cumsum += probabilidades_emigraciones[i];
        if(cumsum>=r){
            return i;
        }
    }

    return -1;
}