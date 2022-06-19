#include "BL.h"
#include "funciones.h"
#include <iostream>
using namespace std;

void CalcularTodoVecindario(vector<int> & seleccionados, vector<int> & restantes, vector<pair<int,int>> & vecindario)
{
    vecindario.clear();
    pair<int,int> pareja;
    for(int i=0; i<seleccionados.size(); i++)
    {
        for(int j=0; j<restantes.size(); j++)
        {
            pareja.first = seleccionados[i];
            pareja.second = restantes[j];
            vecindario.push_back(pareja);
        }
    }
        
}

void MostraVecindario(const vector<pair<int,int>> & vecindario)
{
    cout<<endl<<endl<<endl;
    cout<<"Vecindario"<<endl;
    for(auto it=vecindario.cbegin(); it!=vecindario.cend(); it++)
    {
        cout<<"("<<(*it).first<<","<<(*it).second<<") ";
    }
    cout<<endl;
    cout<<"-------------------------------------"<<endl;
}



void CalcularRestantes(vector<int> &restantes, vector<int> &seleccionados, int n)
{
    restantes.clear();
    for(int i=0; i<n; i++) {
        if(seleccionados.end() == find(seleccionados.begin(), seleccionados.end(), i)) {
            restantes.push_back(i);
        }
    }
};

void BL(vector<int> &seleccionados, vector<pair<int,int>> &vecindario, double &dispersion, 
vector<int>& restantes, double ** &matriz_datos, vector<double> & distancias, int n)
{
    //Empezamos con el algoritmo de busqueda local
    bool mejora=true;
    int num_it = 0;
    double dispersion_comparacion;
    vector<int> copia_sel = seleccionados;
    vector<double> copia_dist = distancias;
    restantes.clear();
    vecindario.clear();
    CalcularRestantes(restantes, seleccionados, n);

    while(mejora and num_it<100000)
    {
        //CALCULAMOS TODO EL VECINDARIO, LO DESORDENAMOS Y VAMOS VIENDO SI 
        //MEJORA CON ALGUNO
        CalcularTodoVecindario(seleccionados, restantes, vecindario);

        random_shuffle(vecindario.begin(), vecindario.end());

        copia_sel = seleccionados;
        mejora=false;
        dispersion_comparacion=dispersion;

        for(int i=0; i<vecindario.size() && !mejora; i++)
        {
            //Quitamos el punto anterior del vector distancias, y lo sustituimos por el nuevo
            //Luego volvemos a calcular la dispersion
            SustituirPunto(copia_dist, vecindario[i],matriz_datos,copia_sel);
            CalculaDispersion(copia_dist, dispersion_comparacion);

            if(dispersion_comparacion<dispersion)
            {
                dispersion = dispersion_comparacion;
                seleccionados = copia_sel;
                distancias = copia_dist;
                mejora = true;
                CalcularRestantes(restantes, seleccionados, n);
            }
            else{
                copia_sel = seleccionados;
                copia_dist = distancias;
            }
            num_it++;
        }

    }
}

