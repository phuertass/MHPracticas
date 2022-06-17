#ifndef GENERACIONAL_H
#define GENERACIONAL_H

#include "funciones.h"
#include "Cruces.h"

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
//Metodos del modelo generacional
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
void SeleccionGeneracional(const vector<Solucion> & poblacion, vector<Solucion> & nueva_poblacion);
void TorneoSeleccionGeneracional(vector<Solucion> & poblacion);

void CruceGeneracionalUniforme(int n, int m,vector<Solucion> & poblacion, int semilla
,double probabilidad, double ** &matriz_datos);
void CruceGeneracionalPosicion(int n, int m,vector<Solucion> & poblacion, int semilla
,double probabilidad);

void MutacionGeneracional(vector<Solucion> & poblacion, int semilla, double probabilidad);
void ReemplazamientoGeneracional(vector<Solucion> & poblacion, const Solucion & mejor_solucion, int pos_mejor);

void AlgoritmoGeneracionalCrucePosicion(int n, int m, int semilla, double probabilidad_mutacion, 
double probabilidad_cruce, vector<Solucion> & poblacion, double ** &matriz_datos);

void AlgoritmoGeneracionalCruceUniforme(int n, int m, int semilla, double probabilidad_mutacion, 
double probabilidad_cruce, vector<Solucion> & poblacion, double ** &matriz_datos);
#endif