#ifndef MEMETICO_H
#define MEMETICO_H

#include "funciones.h"
#include "BL.h"
using namespace std;



void AlgoritmoMemeticoVariante1(int n, int m, int semilla, double probabilidad_mutacion, 
double probabilidad_cruce, vector<Solucion> & poblacion, double ** &matriz_datos);

void AlgoritmoMemeticoVariante2(int n, int m, int semilla, double probabilidad_mutacion, 
double probabilidad_cruce, vector<Solucion> & poblacion, double ** &matriz_datos);

void AlgoritmoMemeticoVariante3(int n, int m, int semilla, double probabilidad_mutacion, 
double probabilidad_cruce, vector<Solucion> & poblacion, double ** &matriz_datos);

#endif