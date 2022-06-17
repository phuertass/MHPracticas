#include <iostream>
#include <random>
#include <vector>
#include <omp.h>
#include <chrono>
#include <ctime>
#include <set>
#include "funciones.h"
#include "random.h"
#include "Generacional.h"
#include "Cruces.h"
#include "Estacionario.h"
#include "Memetico.h"

using namespace std;
using Random = effolkronium::random_static;

#define VECES 5

int main(){
    const int TOPE=100;
    char cadena_lectura[TOPE];
    int n;
    int m;
    vector<int> semillas= {1,2,3,4,5};
    vector<dato> vector_datos;
    vector<double> distancias;

    cin>>n;
    cin>>m;

    cout<<"N: "<<n<<" M: "<<m<<endl;

    dato f;
    int total_utilizados=0;
    while(cin.getline(cadena_lectura, TOPE)){

        dato f = Dividir_Cadena_Clasificar(cadena_lectura);

        if(f.distancia!=0){
            vector_datos.push_back(f);

            total_utilizados++;
   
        }
           
    }

    double ** matriz_datos = new double * [n];

    for(int i=0; i<n; i++){
        matriz_datos[i] = new double [n];
    }

    int i=0;
    for(auto it=vector_datos.begin(); it!=vector_datos.end(); it++,i++)
    {
        dato d = *it;
        matriz_datos[d.i][d.j] = d.distancia;
        matriz_datos[d.j][d.i] = d.distancia;
    }

    //La poblacion va a ser un vector que contiene todos las soluciones creadas,             
    //y la dispersion obtenida por evaluar estos
    int semilla=1;
    double probabilidad_mutacion=0.1;
    double probabilidad_cruce=0.7;
    int posicion_mejor_solucion=0;
    Solucion mejor_sol;
    vector<Solucion> poblacion;

    vector<pair<string, double>> tiempos;

    //PRUEBA DE CORRECTO FUNCIONAMIENTO DEL ALGORITMO
    poblacion.clear();
    CalcularPoblacionAleatoria(n, m, poblacion, semilla, matriz_datos, 5);
    vector<Solucion> poblacion_auxiliar(poblacion);
    MuestraPoblacion(poblacion);
    cout<<"Media de la poblacion: "<<GetDispersionMediaPoblacion(poblacion)<<endl;
    cout<<setprecision(8)<<"Dispersion media de la poblacion-->"<<GetDispersionMediaPoblacion(poblacion)<<endl;
   
    //Prueba cruce uniforme
    vector<bool> s1 = CalcularSolucionAleatoria(n, m, semilla);
    vector<bool> s2 = CalcularSolucionAleatoria(n, m, semilla);
    vector<bool> s3 = CalcularSolucionAleatoria(n, m, semilla);
    vector<bool> s4 = CalcularSolucionAleatoria(n, m, semilla);
    vector<bool> s5 = CalcularSolucionAleatoria(n, m, semilla);
    vector<bool> s6 = CalcularSolucionAleatoria(n, m, semilla);
    vector<bool> s7 = CalcularSolucionAleatoria(n, m, semilla);
    vector<bool> s8 = CalcularSolucionAleatoria(n, m, semilla);
    
    vector<bool> h1 = CruceUniforme(n, m, s1, s2, semilla, matriz_datos);
    vector<bool> h2 = CruceUniforme(n, m, s3, s4, semilla, matriz_datos);
    vector<bool> h3 = CruceUniforme(n, m, s5, s6, semilla, matriz_datos);
    vector<bool> h4 = CruceUniforme(n, m, s7, s8, semilla, matriz_datos);


   return 0;
}