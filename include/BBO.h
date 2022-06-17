#ifndef BBO_H
#define BBO_H

#include "funciones.h"

void AlgoritmoBBO(int n, int m, int semilla, const double probabilidad_mutacion, 
vector<Solucion> & poblacion, double ** & matriz_datos);

#endif