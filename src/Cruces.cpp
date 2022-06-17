#include "Cruces.h"
#include <vector>
#include <algorithm>    // std::find

/////////////////////////////////////////////////////////////////////////////////////
// CRUCE UNIFORME
/////////////////////////////////////////////////////////////////////////////////////
vector<bool> CruceUniforme(int n, int m, const vector<bool> & padre1, const vector<bool> & padre2, int semilla,
double ** &matriz_datos){
    //Recorro los dos padres, si tienen diferentes valores en la posicion i-esima,
    //escojo uno aleatoriamente y se lo asigno al hijo, y si lo dos tienen el mismo,
    //lo asigno al hijo
    vector<bool> hijo(n, false);
    vector<int> pos_a_rellenar;
    int numero_de_escogidos=0;

    for(int i=0; i<n; i++){
        if(padre1[i]!=padre2[i]){
            pos_a_rellenar.push_back(i);
            if(Random::get(0,1)==0)
                hijo[i] = padre1[i];
            else
                hijo[i] = padre2[i];
        }
        else{
            hijo[i] = padre1[i];
        }

     numero_de_escogidos = count(hijo.begin(), hijo.end(), true);
    }

    //Si el numero de escogidos es distinto a m, llamo al operador de reparacion
    if(numero_de_escogidos!=m){
        Reparacion(n, m, hijo, pos_a_rellenar, matriz_datos);
    }else{
    }


    return hijo;
};

inline double GetSumatoria(vector<double> & distancias){
    double sumatoria = 0;
    for(int i=0; i<distancias.size(); i++){
        sumatoria += distancias[i];
    }
    return sumatoria;
}

inline double GetMedia(vector <double> & distancias){
    double media = 0;
    for(int i=0; i<distancias.size(); i++){
        media += distancias[i];
    }
    media /= distancias.size();
    return media;
}

void Reparacion(int n, int m, vector<bool> & v, const vector<int> & pos_a_rellenar, double ** &matriz_datos){
    //Se chequea la factibilidad de x. Si selecciona m elementos, no se hace nada
    int a_reparar = m - count(v.begin(), v.end(), true);
    vector<int> seleccionados;
    for(int i=0; i<v.size(); i++){
        if(v[i]){
            seleccionados.push_back(i);
        }
    }

    vector<double> distancias;
    double dispersion_actual;
    GeneraVDistancias(distancias,seleccionados, matriz_datos);
    CalculaDispersion(distancias, dispersion_actual);

    //Calculamos la media de las distancias de los elementos seleccionados
    double media_distancias = 0;
    media_distancias = GetMedia(distancias);
    //cout<<"\nMedia de distancias es "<<media_distancias<<endl;
    if(a_reparar==0)
        return;

    //Si sobran elementos, se van eliminando los más distantes a 
    //la media hasta que sea factible
    if(a_reparar<0){
        while(a_reparar<0){
            // Buscamos el elemento que mas se aleja de la media
            int pos_mas_distante = 0;
            double mayor_lejania_a_media = 0;
            for(int i=0; i<distancias.size(); i++){
                if(abs(distancias[i]-media_distancias)>mayor_lejania_a_media){
                    mayor_lejania_a_media = abs(distancias[i]-media_distancias);
                    pos_mas_distante = i;
                }
            }

            //Eliminamos el elemento mas distante
            v[seleccionados[pos_mas_distante]] = false;
            seleccionados.erase(seleccionados.begin()+pos_mas_distante);
            distancias.erase(distancias.begin()+pos_mas_distante);
            a_reparar++;
        }
    }
    //Si faltan elementos, se van añadiendo los más cercanos a la 
    //media hasta que x sea factible
    else  if (a_reparar>0){
        vector<int> seleccionados_aux = seleccionados;
        vector<double> distancias_aux = distancias;

        int pos_min=0;
        while(a_reparar>0){
            //Buscamos el elemento no seleccionado que dismite la dispersion,
            //y lo seleccionamos
            double media_min = 9999999999999;
            double media_act;
            for(int i=0; i<n; i++){
                auto it = find(seleccionados_aux.begin(), seleccionados_aux.end(), i);
                if( it ==seleccionados_aux.end()){
                    seleccionados_aux.push_back(i);
                    double distancia_tmp = 0;
                    int a_comparar = i;
                    GeneraVDistancias(distancias_aux,seleccionados_aux, matriz_datos);
                    CalculaDispersion(distancias_aux, distancia_tmp);

                    media_act = GetMedia(distancias_aux);
                    if(media_act<media_min){
                        media_min = media_act;
                        pos_min = i;
                    }

                    // Elimino el elemento de la lista de seleccionados y de la lista de distancias
                    seleccionados_aux.pop_back();
                    distancias_aux.pop_back();
                    GeneraVDistancias(distancias_aux,seleccionados_aux, matriz_datos);
                    CalculaDispersion(distancias_aux, distancia_tmp);
                }
            }
            a_reparar--;
        }
        seleccionados.push_back(pos_min);
        GeneraVDistancias(distancias,seleccionados, matriz_datos);

    }


    GeneraVDistancias(distancias,seleccionados, matriz_datos);
    CalculaDispersion(distancias, dispersion_actual);

    for(int i=0; i<seleccionados.size(); i++){
        v[seleccionados[i]] = true;
    }

}

/////////////////////////////////////////////////////////////////////////////////////
// CRUCE POSICION
/////////////////////////////////////////////////////////////////////////////////////

void CrucePosicion(int n, int m, const vector<bool> & padre1, const vector<bool> & padre2,
    vector<bool> & hijo1, vector<bool> &hijo2, 
    int semilla){
    //Recorro los dos padres, si tienen diferentes valores en la posicion i-esima,
    //escojo uno aleatoriamente y se lo asigno al hijo, y si lo dos tienen el mismo,
    //lo asigno al hijo
    hijo1.resize(n);
    hijo2.resize(n);
    vector<bool> restantespadre1;
    vector<bool> restantespadre2;

    vector<int> pos_rellenar_hijos;
    for(int i=0; i<n; i++){
        if(padre1[i]!=padre2[i]){
            restantespadre1.push_back(padre1[i]);
            restantespadre2.push_back(padre2[i]);
            pos_rellenar_hijos.push_back(i);
        }
        else{
            hijo1[i] = padre1[i];
            hijo2[i] = padre2[i];
        }
    }

    random_shuffle(restantespadre1.begin(), restantespadre1.end());
    random_shuffle(restantespadre2.begin(), restantespadre2.end());
    for(int i=0; i<restantespadre1.size(); i++){
        int pos_a_rellenar = pos_rellenar_hijos[i];
        hijo1[pos_a_rellenar] = restantespadre1[i];
        hijo2[pos_a_rellenar] = restantespadre2[i];
    }

}
