#ifndef ESTACIONARIO_H
#define ESTACIONARIO_H

#include "funciones.h"
#include "Cruces.h"
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
// Metodos del modelo estacionario
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
void SeleccionEstacionario(const vector<Solucion> & poblacion, vector<Solucion> & nueva_poblacion);

void CruceEstacionarioUniforme(int n, int m,vector<Solucion> & poblacion, int semilla, 
double probabilidad, double ** &matriz_datos);
void CruceEstacionarioPosicion(int n, int m,vector<Solucion> & poblacion, int semilla,
double probabilidad);

void MutacionEstacionario(vector<Solucion> & poblacion, int semilla, double probabilidad);
void ReemplazamientoEstacionario(vector<Solucion> & poblacion, const vector<Solucion> & poblacion_mutacion_cruce);

/////////////////////////////////////////////////////////////
// ALGORITMOS
/////////////////////////////////////////////////////////////


void AlgoritmoEstacionarioCrucePosicion(int n, int m, int semilla, double probabilidad_mutacion, 
double probabilidad_cruce, vector<Solucion> & poblacion, double ** & matriz_datos);

void AlgoritmoEstacionarioCruceUniforme(int n, int m, int semilla, double probabilidad_mutacion, 
double probabilidad_cruce, vector<Solucion> & poblacion, double ** & matriz_datos);

#endif