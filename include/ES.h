#ifndef ENFRIAMIENTO_SIMULADO_H
#define ENFRIAMIENTO_SIMULADO_H


#include "funciones.h"

Solucion CalcularSolucionVecinaAleatoria(int n, int m, const Solucion & s, double ** & matriz_datos);

void AlgoritmoEnfriamientoSimulado(int n, int m, Solucion & s, double ** & matriz_datos, int num_ev_maximo);
#endif
