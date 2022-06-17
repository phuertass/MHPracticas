#include "Generacional.h"

/////////////////////////////////////////////////////////////////////////////////////
// FUNCIONES DEL MODELO GENERACIONAL
/////////////////////////////////////////////////////////////////////////////////////
void SeleccionGeneracional(const vector<Solucion> & poblacion, vector<Solucion> & nueva_poblacion){
    int tam_pob = poblacion.size();
    nueva_poblacion.clear();
    nueva_poblacion.resize(tam_pob);
    
    //Mezclo la poblacion
    for(int i=0; i<tam_pob; i++){
        //Realizo un torneo binario y selecciono el mejor
        int pos1 = Random::get(0, tam_pob-1);
        int pos2 = Random::get(0, tam_pob-1);
        while(pos1==pos2){
            pos2 = Random::get(0, tam_pob-1);
        }
        if(poblacion[pos1].dispersion < poblacion[pos2].dispersion){
            nueva_poblacion[i] = poblacion[pos1];
        }
        else{
            nueva_poblacion[i] = poblacion[pos2];
        }
    }
}



////////////////////////////////////////////////////////////////////////////////////////////
// CRUCES
////////////////////////////////////////////////////////////////////////////////////////////

void CruceGeneracionalUniforme(int n, int m, vector<Solucion> & poblacion,int semilla, 
double probabilidad, double ** &matriz_datos){
    //Recorro la poblacion, y si el numero aleatorio es menor que la probabilidad,
    //selecciono dos padres aleatorios y los cruzo
    int tam_poblacion = poblacion.size();
    int numero_esperado_de_cruces = probabilidad*(tam_poblacion);

    for(int i=0; i<numero_esperado_de_cruces; i+=2){
        int padre1 = i;
        int padre2 = i+1;

        poblacion[i].solucion = CruceUniforme(n, m, poblacion[padre1].solucion, poblacion[padre2].solucion, semilla, matriz_datos);

    }
}

void CruceGeneracionalPosicion(int n, int m, vector<Solucion> & poblacion, int semilla,
double probabilidad){
    //Recorro la poblacion, y si el numero aleatorio es menor que la probabilidad,
    //selecciono dos padres aleatorios y los cruzo
    int tam_poblacion = poblacion.size();

    int numero_esperado_de_cruces = probabilidad*(tam_poblacion);

    //Cruzar el primero con el segundo, 2 con 3
    for(int i=0; i<numero_esperado_de_cruces; i+=2){
        int padre1 = i;
        int padre2 = i+1;
        
        vector<bool> hijo1;
        vector<bool> hijo2;
        //cout<<"Cruzando padre "<<padre1<<" con padre "<<padre2<<endl;
        CrucePosicion(n, m, poblacion[padre1].solucion, poblacion[padre2].solucion, 
        hijo1, hijo2, semilla);

        poblacion[padre1].solucion = hijo1;
        poblacion[padre2].solucion = hijo2;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
// MUTACION
////////////////////////////////////////////////////////////////////////////////////////////

void MutacionGeneracional(vector<Solucion> & poblacion, int semilla, double probabilidad){
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

////////////////////////////////////////////////////////////////////////////////////////////
// REEMPLAZAMIENTOS
////////////////////////////////////////////////////////////////////////////////////////////

void ReemplazamientoGeneracional(vector<Solucion> & poblacion, const Solucion & mejor_solucion, int pos_mejor){
    //Si la mejor solucion no ha sobrevivido, la sustituyo por la peor de la nueva poblacion
    //Primero busco si la mejor solucion ha sobrevivido
    int pos_esta = -1;
    bool esta = EstaPosicion(poblacion, mejor_solucion, pos_esta);

    if(!esta){
        //cout<<"Se ha perdido la mejor solucion por lo que la recuperamos"<<endl;
        int posicion_peor = 0;
        //Busco el peor de la nueva poblacion y en dicha posicion meto la mejor solucion
        Solucion peor = GetPeor(poblacion, posicion_peor);
        poblacion[posicion_peor] = mejor_solucion;
    }
}



////////////////////////////////////////////////////////////////////////////////////////////
// ALGORITMO AGE-CRUCEPOSICION
////////////////////////////////////////////////////////////////////////////////////////////


void AlgoritmoGeneracionalCrucePosicion(int n, int m, int semilla, double probabilidad_mutacion, 
double probabilidad_cruce, vector<Solucion> & poblacion, double ** & matriz_datos)
{
    int num_it = 0;
    vector<Solucion> poblacion_algoritmo;
    int num_evaluaciones=0;
    int posicion_mejor_solucion=0;
    Solucion mejor_sol = GetMejor(poblacion, posicion_mejor_solucion);

    while(num_evaluaciones<100000){
        posicion_mejor_solucion=0;
        mejor_sol = GetMejor(poblacion, posicion_mejor_solucion);
        //poblacion_algoritmo.clear();
        SeleccionGeneracional(poblacion, poblacion_algoritmo);

        CruceGeneracionalPosicion(n,m,poblacion_algoritmo, semilla, probabilidad_cruce);

        MutacionGeneracional(poblacion_algoritmo, semilla, probabilidad_mutacion);

        vector<int> seleccionados;
        for(int i=0; i<poblacion_algoritmo.size(); i++){
            Solucion s = poblacion_algoritmo[i];

            seleccionados.clear();
            for(int i=0; i<s.solucion.size(); i++){
                if(s.solucion[i]){
                    seleccionados.push_back(i);
                }
            }
            GeneraVDistancias(s.distancias, seleccionados, matriz_datos);
            CalculaDispersion(s.distancias, s.dispersion);
            poblacion_algoritmo[i] = s;
            num_evaluaciones++;
        }

        ReemplazamientoGeneracional(poblacion_algoritmo, mejor_sol, posicion_mejor_solucion);

        poblacion = poblacion_algoritmo;
        num_it++;

    }

}

void AlgoritmoGeneracionalCruceUniforme(int n, int m, int semilla, double probabilidad_mutacion, 
double probabilidad_cruce, vector<Solucion> & poblacion, double ** & matriz_datos)
{
    int num_it = 0;
    vector<Solucion> poblacion_algoritmo;
    int num_evaluaciones=0;
    int posicion_mejor_solucion=0;
    Solucion mejor_sol = GetMejor(poblacion, posicion_mejor_solucion);

    while(num_evaluaciones<100000){
        posicion_mejor_solucion=0;
        mejor_sol = GetMejor(poblacion, posicion_mejor_solucion);
        //poblacion_algoritmo.clear();
        SeleccionGeneracional(poblacion, poblacion_algoritmo);

        CruceGeneracionalUniforme(n,m,poblacion_algoritmo, semilla, probabilidad_cruce, matriz_datos);

        MutacionGeneracional(poblacion_algoritmo, semilla, probabilidad_mutacion);

        vector<int> seleccionados;
        for(int i=0; i<poblacion_algoritmo.size(); i++){
            Solucion s = poblacion_algoritmo[i];

            seleccionados.clear();
            for(int i=0; i<s.solucion.size(); i++){
                if(s.solucion[i]){
                    seleccionados.push_back(i);
                }
            }
            GeneraVDistancias(s.distancias, seleccionados, matriz_datos);
            CalculaDispersion(s.distancias, s.dispersion);
            poblacion_algoritmo[i] = s;
            num_evaluaciones++;
        }

        ReemplazamientoGeneracional(poblacion_algoritmo, mejor_sol, posicion_mejor_solucion);

        poblacion = poblacion_algoritmo;
        num_it++;
    }

}