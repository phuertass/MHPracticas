#ifndef BUSQUEDA_REITERADA_H
#define BUSQUEDA_REITERADA_H

#include "funciones.h"

void AlgoritmoILS(int n, int m, int semilla, double probabilidad_mutacion, 
double probabilidad_cruce, Solucion & s, double ** & matriz_datos);

void AlgoritmoILS_ES(int n, int m, int semilla, double probabilidad_mutacion,
                  double probabilidad_cruce, Solucion &s, double **&matriz_datos);

#endif