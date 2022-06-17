#ifndef FUNCIONES
#define FUNCIONES

#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <vector>
#include <set>
#include <algorithm>
#include "random.h"
#include "Solucion.hpp"

using Random = effolkronium::random_static;
using namespace std;

typedef struct {
    int i;
    int j;
    double distancia;
}dato;

dato Dividir_Cadena_Clasificar(string cadena);
void MuestraVector(string cad, vector<dato> & vector_datos);
void MuestraVector(string cad, vector<int> & vector_datos);
void MuestraVector(string cad, vector<double> & vector_datos);
void MuestraVector(string cad, set<int> & vector_datos);
void MuestraVector(string cad, vector<bool> & v);
void RellenaVector(vector<int> & vector, int tamanio);
void MuestraDato(const dato d);
void Intercambia(vector<int> & Seleccionados, int original, int nuevo, vector<double> & distancias, double & dispersion);


/////////////////////////////////////////////////////////////////////////////////////////////
// FUNCIONES COMUNES PARA LOS ALGORITMOS
/////////////////////////////////////////////////////////////////////////////////////////////
void CalculaDispersion(vector<double> distancias, double &dispersion);
void GeneraVDistancias(vector<double> & distancias, const vector<int> &seleccionados, double ** &matriz);
void SustituirPunto(vector<double> &copia_dist, const pair<int,int> pareja, double **&matriz,
vector<int> & seleccionados);

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
// Funciones de la practica 2
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////


//Funciones generales
double GetDispersionMediaPoblacion(const vector<Solucion> &poblacion);
void MuestraPoblacion(vector<Solucion> & poblacion);
void CalcularPoblacionAleatoria(int n, int m, vector<Solucion> & p, int semilla, double ** &matriz_datos, int tam_poblacion);
vector<bool> CalcularSolucionAleatoria(int n, int m, int semilla);
vector<bool> CalcularSolucionAleatoriaILS(int n, int m, int semilla);
void GeneraVDistanciasBool(vector<double> & distancias, const vector<bool> &seleccionados, double ** &matriz_datos);

//Obtiene el mejor
Solucion GetMejor(const vector<Solucion> & poblacion, int & posicion);
//Obtiene el peor
Solucion GetPeor(const vector<Solucion> & poblacion, int & posicion);

//Devuelve true si esta la posicion en la solucion
bool EstaPosicion(const vector<Solucion> & poblacion, const Solucion & s, int & posicion);

void OrdenarPorFitness(vector<Solucion> &poblacion);

void MutacionPoblacion(vector<Solucion> & poblacion, const double probabilidad, const int semilla);

void Migracion(vector<Solucion> & poblacion);

int IndiceRouletteWheel(Solucion & s, const vector<Solucion> &p);

#endif