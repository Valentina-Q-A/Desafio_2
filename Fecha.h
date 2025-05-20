#ifndef FECHA_H
#define FECHA_H

#include <string>
#include <iostream>

class Fecha {
private:
    int dia;
    short int mes;
    short int anio;

public:
    Fecha(short int d = 1, short int m = 1, short int a = 2000);

    static bool compararFecha(Fecha* f1, Fecha* f2);
    bool esBisiesto(int anio) const;
    Fecha sumarNoches(unsigned int noches) const;

    std::string mostrarFechaFormato() const;
    bool cargarDesdeCadena(const std::string& cadena);
    std::string aCadena() const;

    int getDia() const;
    int getMes() const;
    int getAnio() const;

    void setDia(int d);
    void setMes(short int m);
    void setAnio(short int a);

    friend std::ostream& operator<<(std::ostream& os, const Fecha& f);
    friend std::istream& operator>>(std::istream& is, Fecha& f);
};

#endif


