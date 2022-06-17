#include "Estacionario.h"


////////////////////////////////////////////////////////////////////////////////////////////
// METODOS DEL METODO ESTACIONARIO
////////////////////////////////////////////////////////////////////////////////////////////
void SeleccionEstacionario(const vector<Solucion> & poblacion, vector<Solucion> & nueva_poblacion)
{
    //Aplicar dos veces el torneo binario para completar la nueva poblacion 
    //que solo tendra dos cromosomas
    int tam_pob = poblacion.size();
    nueva_poblacion.clear();
    
    //Mezclo la poblacion
    for(int i=0; i<2; i++){
        //Realizo un torneo binario y selecciono el mejor
        int pos1 = Random::get(0, tam_pob-1);
        int pos2 = Random::get(0, tam_pob-1);
        while(pos1==pos2)
            pos2 = Random::get(0, tam_pob-1);
        if(poblacion[pos1].dispersion < poblacion[pos2].dispersion){
            nueva_poblacion.push_back(poblacion[pos1]);
        }
        else{
            nueva_poblacion.push_back(poblacion[pos2]);
        }
    }

}

void CruceEstacionarioUniforme(int n, int m,vector<Solucion> & poblacion, int semilla,
double probabilidad, double ** &matriz_datos){
    probabilidad = 1;
    //Cruce de dos cromosomas
    int padre1 = 0;
    int padre2 = 1;

    vector<bool> hijo1;
    vector<bool> hijo2;
    //cout<<"Cruzando padre "<<padre1<<" con padre "<<padre2<<endl;
    CrucePosicion(n, m, poblacion[padre1].solucion, poblacion[padre2].solucion, 
    hijo1, hijo2, semilla);

    poblacion[padre1].solucion = hijo1;
    poblacion[padre2].solucion = hijo2;
}


void CruceEstacionarioPosicion(int n, int m,vector<Solucion> & poblacion, int semilla,
double probabilidad){
    probabilidad = 1;
    //Cruce de dos cromosomas
    int padre1 = 0;
    int padre2 = 1;

    vector<bool> hijo1;
    vector<bool> hijo2;
    CrucePosicion(n, m, poblacion[padre1].solucion, poblacion[padre2].solucion, 
    hijo1, hijo2, semilla);

    poblacion[padre1].solucion = hijo1;
    poblacion[padre2].solucion = hijo2;
}

void MutacionEstacionario(vector<Solucion> & poblacion, int semilla, double probabilidad){
    for(int i=0; i<2; i++){
        if(Random::get(0,1)<probabilidad){
            int tam_sol = poblacion[0].solucion.size();
            int x1 = Random::get(0, tam_sol-1);
            int x2 = x1;
            while(poblacion[i].solucion[x1]==poblacion[i].solucion[x2]){
                x2 = Random::get(0,tam_sol-1);
            }
            bool tmp = poblacion[i].solucion[x1];
            poblacion[i].solucion[x1] = poblacion[i].solucion[x2];
            poblacion[i].solucion[x2] = tmp;
        }
    }
}

void ReemplazamientoEstacionario(vector<Solucion> & poblacion_actual, const vector<Solucion> & poblacion_mutacion_cruce){
    Solucion s1 = poblacion_mutacion_cruce[0];
    Solucion s2 = poblacion_mutacion_cruce[1];
    int posicion_peor1=0;
    Solucion peor = GetPeor(poblacion_actual, posicion_peor1);
    int posicion2peor=0;
    Solucion segundopeor = poblacion_actual[0];
    //Obtenemos el segundo peor de la poblacion que no sea peor
    for(int i=0; i<poblacion_actual.size(); i++){
        if(poblacion_actual[i].dispersion > segundopeor.dispersion && i!=posicion_peor1){
            segundopeor = poblacion_actual[i];
            posicion2peor = i;
        }
    }


    //Ahora de los 4 que tengo, meto en la poblacion los dos mejores
    //Ordeno las  4 soluciones por dispersion
    vector<Solucion> poblacion_ordenada;
    poblacion_ordenada.push_back(s1);
    poblacion_ordenada.push_back(s2);
    poblacion_ordenada.push_back(peor);
    poblacion_ordenada.push_back(segundopeor);
    for(int i=0; i<poblacion_ordenada.size()-1; i++){
        for(int j=i+1; j<poblacion_ordenada.size(); j++){
            if(poblacion_ordenada[i].dispersion > poblacion_ordenada[j].dispersion){
                Solucion aux = poblacion_ordenada[i];
                poblacion_ordenada[i] = poblacion_ordenada[j];
                poblacion_ordenada[j] = aux;
            }
        }
    }
    poblacion_actual[posicion_peor1] = poblacion_ordenada[0];
    poblacion_actual[posicion2peor] = poblacion_ordenada[1];
}

void AlgoritmoEstacionarioCrucePosicion(int n, int m, int semilla, double probabilidad_mutacion,
                                        double probabilidad_cruce, vector<Solucion> &poblacion, double **&matriz_datos)
{
    int num_it = 0;
    vector<Solucion> poblacion_algoritmo;
    int num_evaluaciones = 0;
    int posicion_mejor_solucion = 0;
    Solucion mejor_sol = GetMejor(poblacion, posicion_mejor_solucion);

    //while (num_it < 100000)
    while (num_evaluaciones < 100000)
    {
        posicion_mejor_solucion = 0;
        mejor_sol = GetMejor(poblacion, posicion_mejor_solucion);

        SeleccionEstacionario(poblacion, poblacion_algoritmo);

        CruceEstacionarioPosicion(n, m, poblacion_algoritmo, semilla, probabilidad_cruce);

        MutacionEstacionario(poblacion_algoritmo, semilla, probabilidad_mutacion);

        vector<int> seleccionados;
        for (int i = 0; i < poblacion_algoritmo.size(); i++)
        {
            Solucion s = poblacion_algoritmo[i];

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
            poblacion_algoritmo[i] = s;
            num_evaluaciones++;
        }

        ReemplazamientoEstacionario(poblacion, poblacion_algoritmo);

        poblacion_algoritmo.clear();
        num_it++;
    }

}

void AlgoritmoEstacionarioCruceUniforme(int n, int m, int semilla, double probabilidad_mutacion,
                                        double probabilidad_cruce, vector<Solucion> &poblacion, double **&matriz_datos)
{
    int num_it = 0;
    vector<Solucion> poblacion_algoritmo;
    int num_evaluaciones = 0;
    int posicion_mejor_solucion = 0;
    Solucion mejor_sol = GetMejor(poblacion, posicion_mejor_solucion);

    while (num_it < 100000)
    {
        posicion_mejor_solucion = 0;
        mejor_sol = GetMejor(poblacion, posicion_mejor_solucion);

        SeleccionEstacionario(poblacion, poblacion_algoritmo);

        CruceEstacionarioUniforme(n, m, poblacion_algoritmo, semilla, probabilidad_cruce, matriz_datos);

        MutacionEstacionario(poblacion_algoritmo, semilla, probabilidad_mutacion);

        vector<int> seleccionados;
        for (int i = 0; i < poblacion_algoritmo.size(); i++)
        {
            Solucion s = poblacion_algoritmo[i];

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
            poblacion_algoritmo[i] = s;
        }

        ReemplazamientoEstacionario(poblacion, poblacion_algoritmo);

        poblacion_algoritmo.clear();
        num_it++;
    }

}