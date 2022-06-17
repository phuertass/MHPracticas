#ifndef BL_H
#define BL_H

#include "funciones.h"

void CalcularTodoVecindario(vector<int> & seleccionados, vector<int> & restantes, vector<pair<int,int>> & vecindario);
void MostraVecindario(const vector<pair<int,int>> & vecindario);
void SustituirPunto(vector<double> &copia_dist, const pair<int,int> pareja,double **&matriz,
vector<int> & seleccionados);

void CalcularRestantes(vector<int> &restantes, vector<int> &seleccionados, int n);

void BL(vector<int> &seleccionados, vector<pair<int,int>> &vecindario, double &dispersion, 
vector<int>& restantes, double ** &matriz_datos, vector<double> & distancias, int n);

#endif