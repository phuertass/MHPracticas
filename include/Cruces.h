#ifndef CRUCES_H
#define CRUCES_H

#include "funciones.h"
//Metodos de cruce
vector<bool> CruceUniforme(int n, int m, const vector<bool> & padre1, const vector<bool> & padre2, int semilla, double ** &matriz_datos);
void Reparacion(int n, int m, vector<bool> & hijo, const vector<int> & pos_a_rellenar, double ** &matriz_datos);
void CrucePosicion(int n, int m, const vector<bool> & padre1, const vector<bool> & padre2, 
vector<bool> & hijo1, vector<bool> & hijo2, int semilla);


#endif 