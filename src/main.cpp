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


typedef struct{
    string algoritmo;
    double dispersion;
    double tiempo;
} resultado;

int main(){
    const int TOPE=100;
    char cadena_lectura[TOPE];
    int n;
    int m;
    vector<int> semillas= {1,2,3,4,5};
    vector<dato> vector_datos;
    vector<double> distancias;
    resultado r;

    cin>>n;
    cin>>m;

    //cout<<"N: "<<n<<" M: "<<m<<endl;

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
    vector<resultado> resultados;

    //PRUEBA DE CORRECTO FUNCIONAMIENTO DEL ALGORITMO
    poblacion.clear();
    CalcularPoblacionAleatoria(n, m, poblacion, semilla, matriz_datos, 50);
    vector<Solucion> poblacion_auxiliar(poblacion);
    //MuestraPoblacion(poblacion);
    //cout<<"Media de la poblacion: "<<GetDispersionMediaPoblacion(poblacion)<<endl;
    //cout<<setprecision(8)<<"Dispersion media de la poblacion-->"<<GetDispersionMediaPoblacion(poblacion)<<endl;
   
    posicion_mejor_solucion=0;
    mejor_sol = GetMejor(poblacion, posicion_mejor_solucion);
    //cout<<"La mejor solucion es: "<<endl;
    //MuestraVector("",mejor_sol.solucion);
    //cout<<"Dispersion: "<<mejor_sol.dispersion<<endl;
    
    //cout<<"ALGORITMO GENERACIONAL"<<endl;

    chrono::high_resolution_clock::time_point t1;
    chrono::high_resolution_clock::time_point t2;
    chrono::duration<double> time_span;

    #pragma omp parallel sections private(poblacion)
    {   
        
        #pragma omp section
        {
            poblacion = poblacion_auxiliar;
            t1 = chrono::high_resolution_clock::now();
            AlgoritmoEnfriamientoSimulado(n, m, semilla, probabilidad_mutacion, probabilidad_cruce, poblacion, matriz_datos);
            t2 = chrono::high_resolution_clock::now();
            time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
            posicion_mejor_solucion=0;
            mejor_sol = GetMejor(poblacion, posicion_mejor_solucion);
            //cout<<"La mejor solucion es: "<<endl;
            //MuestraVector("",mejor_sol.solucion);
            //cout<<"Dispersion: "<<mejor_sol.dispersion<<endl;
            tiempos.push_back(make_pair("Enfriamiento Simulado", mejor_sol.dispersion));

            r = {"Enfriamiento Simulado", mejor_sol.dispersion, time_span.count()};
            resultados.push_back(r);
        }
        
    
        #pragma omp section
        {
            //AlgoritmoGeneracionalCruceUniforme(n, m, semilla, probabilidad_mutacion, probabilidad_cruce, poblacion, matriz_datos);
            //posicion_mejor_solucion=0;
            //mejor_sol = GetMejor(poblacion, posicion_mejor_solucion);
            //tiempos.push_back(make_pair("GeneracionalU", mejor_sol.dispersion));
            //cout<<"\n\n\n\nALGORITMO ESTACIONARIO"<<endl;

            poblacion = poblacion_auxiliar;
            t1 = chrono::high_resolution_clock::now();
            AlgoritmoMultiarranqueBasico(n, m, semilla, probabilidad_mutacion, probabilidad_cruce, poblacion, matriz_datos);
            t2 = chrono::high_resolution_clock::now();
            time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
            
            posicion_mejor_solucion=0;
            mejor_sol = GetMejor(poblacion, posicion_mejor_solucion);
            //cout<<"La mejor solucion es: "<<endl;
            //MuestraVector("",mejor_sol.solucion);
            //cout<<"Dispersion: "<<mejor_sol.dispersion<<endl;
            tiempos.push_back(make_pair("Multiarranque basico", mejor_sol.dispersion));

            r = {"Multiarranque basico", mejor_sol.dispersion, time_span.count()};
            resultados.push_back(r);
        }

        #pragma omp section
        {
            //AlgoritmoGeneracionalCruceUniforme(n, m, semilla, probabilidad_mutacion, probabilidad_cruce, poblacion, matriz_datos);
            //posicion_mejor_solucion=0;
            //mejor_sol = GetMejor(poblacion, posicion_mejor_solucion);
            //tiempos.push_back(make_pair("GeneracionalU", mejor_sol.dispersion));
            //cout<<"\n\n\n\nALGORITMO ESTACIONARIO"<<endl;

            poblacion = poblacion_auxiliar;
            t1 = chrono::high_resolution_clock::now();
            AlgoritmoILS(n, m, semilla, probabilidad_mutacion, probabilidad_cruce, poblacion, matriz_datos);
            t2 = chrono::high_resolution_clock::now();
            time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
            
            posicion_mejor_solucion=0;
            mejor_sol = GetMejor(poblacion, posicion_mejor_solucion);
            //cout<<"La mejor solucion es: "<<endl;
            //MuestraVector("",mejor_sol.solucion);
            //cout<<"Dispersion: "<<mejor_sol.dispersion<<endl;
            tiempos.push_back(make_pair("ILS", mejor_sol.dispersion));

            r = {"ILS", mejor_sol.dispersion, time_span.count()};
            resultados.push_back(r);
        }

        #pragma omp section
        {
            //AlgoritmoGeneracionalCruceUniforme(n, m, semilla, probabilidad_mutacion, probabilidad_cruce, poblacion, matriz_datos);
            //posicion_mejor_solucion=0;
            //mejor_sol = GetMejor(poblacion, posicion_mejor_solucion);
            //tiempos.push_back(make_pair("GeneracionalU", mejor_sol.dispersion));
            //cout<<"\n\n\n\nALGORITMO ESTACIONARIO"<<endl;

            poblacion = poblacion_auxiliar;
            t1 = chrono::high_resolution_clock::now();
            AlgoritmoILS_ES(n, m, semilla, probabilidad_mutacion, probabilidad_cruce, poblacion, matriz_datos);
            t2 = chrono::high_resolution_clock::now();
            time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
            
            posicion_mejor_solucion=0;
            mejor_sol = GetMejor(poblacion, posicion_mejor_solucion);
            //cout<<"La mejor solucion es: "<<endl;
            //MuestraVector("",mejor_sol.solucion);
            //cout<<"Dispersion: "<<mejor_sol.dispersion<<endl;
            tiempos.push_back(make_pair("ILS_ES", mejor_sol.dispersion));

            r = {"ILS_ES", mejor_sol.dispersion, time_span.count()};
            resultados.push_back(r);
        }
    
    }

    //for(int i=0; i<tiempos.size(); i++){
    //    cout<<tiempos[i].first<<"\t"<<tiempos[i].second<<endl;
    //}

    for(int i=0; i<resultados.size(); i++){
        cout<<"----------------------------------------------------"<<endl;
        cout<<resultados[i].algoritmo<<"\t"<<resultados[i].dispersion<<endl;
        cout<<"Tiempo "<<resultados[i].algoritmo<<"\t"<<resultados[i].tiempo<<endl;
        cout<<"----------------------------------------------------"<<endl;
    }

   return 0;
}