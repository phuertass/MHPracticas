#include "Memetico.h"
#include "Generacional.h"

using namespace std;


void AlgoritmoMemeticoVariante1(int n, int m, int semilla, double probabilidad_mutacion, 
double probabilidad_cruce, vector<Solucion> & poblacion, double ** &matriz_datos)
{
    int num_it = 0;
    vector<Solucion> poblacion_algoritmo;
    int num_evaluaciones=0;
    int posicion_mejor_solucion=0;
    Solucion mejor_sol = GetMejor(poblacion, posicion_mejor_solucion);
    vector<int> restantes;
    vector<pair<int,int>> vecindario;
    vector<int> seleccionados;

    while(num_evaluaciones<100000){
        if(num_it%10==0){
            seleccionados.clear();
            restantes.clear();
            vecindario.clear();
            // Aplico la búsqueda local sobre todos los cromosomas de la población
            for(int i=0; i<poblacion.size(); i++){
                Solucion s = poblacion[i];
                seleccionados.clear();
                for(int i=0; i<s.solucion.size(); i++){
                    if(s.solucion[i]){
                        seleccionados.push_back(i);
                    }
                }
                CalcularRestantes(restantes, seleccionados, n);
                //MuestraVector("Solucion before BL: ",s.solucion);
                BL(seleccionados, vecindario, s.dispersion, restantes, matriz_datos, s.distancias, n);
                vector<bool> seleccionados_binario(n,false);
                for(int i=0; i<seleccionados.size(); i++){
                    seleccionados_binario[seleccionados[i]]=true;
                }
                s.solucion = seleccionados_binario;

                //MuestraVector("Solucion after BL: ",s.solucion);
                GeneraVDistancias(s.distancias, seleccionados, matriz_datos);
                CalculaDispersion(s.distancias, s.dispersion);
                num_evaluaciones++;
                // Actualizo la población
                poblacion[i] = s;
            }
        }

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
};

void AlgoritmoMemeticoVariante2(int n, int m, int semilla, double probabilidad_mutacion, 
double probabilidad_cruce, vector<Solucion> & poblacion, double ** &matriz_datos)
{
    int num_it = 0;
    vector<Solucion> poblacion_algoritmo;
    int num_evaluaciones=0;
    int posicion_mejor_solucion=0;
    Solucion mejor_sol = GetMejor(poblacion, posicion_mejor_solucion);
    vector<int> restantes;
    vector<pair<int,int>> vecindario;
    vector<int> seleccionados;

    while(num_evaluaciones<100000){
        if(num_it%10 == 0){
            seleccionados.clear();
            restantes.clear();
            vecindario.clear();

            int num_bl = poblacion.size()*0.1;
            random_shuffle(poblacion.begin(), poblacion.end());
            // Aplico la búsqueda local sobre todos los cromosomas de la población
            for(int i=0; i<num_bl; i++){
                Solucion s = poblacion[i];
                seleccionados.clear();
                for(int i=0; i<s.solucion.size(); i++){
                    if(s.solucion[i]){
                        seleccionados.push_back(i);
                    }
                }
                CalcularRestantes(restantes, seleccionados, n);
                BL(seleccionados, vecindario, s.dispersion, restantes, matriz_datos, s.distancias, n);
                vector<bool> seleccionados_binario(n,false);
                for(int i=0; i<seleccionados.size(); i++){
                    seleccionados_binario[seleccionados[i]]=true;
                }
                s.solucion = seleccionados_binario;
                GeneraVDistancias(s.distancias, seleccionados, matriz_datos);
                CalculaDispersion(s.distancias, s.dispersion);
                num_evaluaciones++;
                // Actualizo la población
                poblacion[i] = s;
            }
        }
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
};

void AlgoritmoMemeticoVariante3(int n, int m, int semilla, double probabilidad_mutacion, 
double probabilidad_cruce, vector<Solucion> & poblacion, double ** &matriz_datos)
{
    int num_it = 0;
    vector<Solucion> poblacion_algoritmo;
    int num_evaluaciones=0;
    int posicion_mejor_solucion=0;
    Solucion mejor_sol = GetMejor(poblacion, posicion_mejor_solucion);
    vector<int> restantes;
    vector<pair<int,int>> vecindario;
    vector<int> seleccionados;
    int num_bl = poblacion.size()*0.1;

    while(num_evaluaciones<100000){
        if(num_it%10 == 0){
            seleccionados.clear();
            restantes.clear();
            vecindario.clear();
            for (int izda = 0; izda < poblacion.size(); izda++) {

                // Calcular el mínimo entre "izda" y "total_utilizados"-1

                Solucion minimo = poblacion[izda]; // Valor del mínimo
                int pos_min = izda;   // Posición del mínimo

                for (int i = izda + 1; i < poblacion.size(); i++)

                    if (poblacion[i].dispersion < minimo.dispersion){ // Nuevo mínimo
                        minimo = poblacion[i];
                        pos_min = i;
                    }

                // Intercambiar los valores guardados en "izda" y "pos_min"  

                Solucion tmp = poblacion[izda];
                poblacion[izda] = poblacion[pos_min];
                poblacion[pos_min] = tmp;

            }
            // Aplico la búsqueda local sobre todos los cromosomas de la población
            for(int i=0; i<num_bl; i++){
                Solucion s = poblacion[i];
                seleccionados.clear();
                for(int i=0; i<s.solucion.size(); i++){
                    if(s.solucion[i]){
                        seleccionados.push_back(i);
                    }
                }
                CalcularRestantes(restantes, seleccionados, n);
                BL(seleccionados, vecindario, s.dispersion, restantes, matriz_datos, s.distancias, n);
                vector<bool> seleccionados_binario(n,false);
                for(int i=0; i<seleccionados.size(); i++){
                    seleccionados_binario[seleccionados[i]]=true;
                }
                s.solucion = seleccionados_binario;
                GeneraVDistancias(s.distancias, seleccionados, matriz_datos);
                CalculaDispersion(s.distancias, s.dispersion);
                num_evaluaciones++;
                // Actualizo la población
                poblacion[i] = s;
            }
        }
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
};