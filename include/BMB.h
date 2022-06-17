#ifndef MULTIARRANQUE_BASICO_H
#define MULTIARRANQUE_BASICO_H

#include "funciones.h"
void AlgoritmoMultiarranqueBasico(int n, int m, int semilla, double probabilidad_mutacion, 
double probabilidad_cruce, vector<Solucion> & poblacion, double ** & matriz_datos);
#endif