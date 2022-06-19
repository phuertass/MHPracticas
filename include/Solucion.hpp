#ifndef SOLUCION_H
#define SOLUCION_H

#include <iostream>
#include <vector>

using namespace std;

// typedef struct{
//     vector<bool> solucion;
//     double dispersion;
//     vector<double> distancias;
//     vector<int> seleccionados;
// } Solucion;

class Solucion
{
public:
    vector<bool> solucion;
    double dispersion;
    vector<double> distancias;
    vector<int> seleccionados;
    double prob_inmigracion;
    double prob_emigracion;
    

    friend ostream &operator<<(ostream &os, const Solucion &s)
    {
        os << "{Seleccionados}-->";
        for (int i = 0; i < s.seleccionados.size(); i++)
            os << s.seleccionados[i] << ",";

        os << "\n{Dispersion}-->" << s.dispersion << endl;
        //os << "{Distancias}-->";
        //for (int i = 0; i < s.distancias.size(); i++)
        //    os << s.distancias[i] << " ";
        os << "{Solucion}-->";
        for (int i = 0; i < s.solucion.size(); i++)
            os << s.solucion[i] << " ";

        os << "\n{Numero seleccionados}-->" << count(s.solucion.begin(), s.solucion.end(), true) << endl;

        os << "{Distancias}-->";
        for (int i = 0; i < s.distancias.size(); i++)
            os << s.distancias[i] << " ";
        os << endl;
        //os << "Probabilidad de inmigracion: " << s.prob_inmigracion << endl;
        //os << "Probabilidad de emigracion: " << s.prob_emigracion << endl;
        return os;
    }

    friend ostream &operator<<(ostream &os, const vector<Solucion> &poblacion)
    {
        os << "Poblacion: " << endl;
        for (int i = 0; i < poblacion.size(); i++)
            os << poblacion[i] << endl << endl;
        return os;
    }

    Solucion & operator = (const Solucion &s)
    {
        this->solucion = s.solucion;
        this->dispersion = s.dispersion;
        this->distancias = s.distancias;
        this->seleccionados = s.seleccionados;
        this->prob_inmigracion = s.prob_inmigracion;
        this->prob_emigracion = s.prob_emigracion;
        return *this;
    }
};

#endif
