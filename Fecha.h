#ifndef FECHA_H
#define FECHA_H

#include <string>
#include <iostream>
using namespace std;

/*
 * Clase Fecha: representa una fecha en formato dia/mes/año.
 * Incluye metodos para manipulacion, comparacion y conversion de fechas.
 */
class Fecha {
private:
    int dia;
    short int mes;
    short int anio;

public:
    // Constructor con valores por defecto: 01/01/2000
    Fecha(short int d = 1, short int m = 1, short int a = 2000);

    /*
     * Metodo estatico para comparar dos fechas.
     * Retorna -1 si f1 < f2, 0 si son iguales, y 1 si f1 > f2.
     */
    static int compararFecha(const Fecha* f1, const Fecha* f2);

    bool esBisiesto(int anio) const; // verificar si es bisiesto

    /*
     * Retorna una nueva fecha resultado de sumar noches a la fecha actual.
     * Avanza los dias correctamente teniendo en cuenta meses y años.
     */
    Fecha sumarNoches(int noches) const;

    string mostrarFechaFormato() const; // Devuelve la fecha en formato dd/mm/aaaa como string.
    bool cargarDesdeCadena(const string& cadena); // Carga una fecha desde una cadena con formato dd/mm/aaaa.
    string aCadena() const; // Retorna la fecha como cadena en formato dd/mm/aaaa.

    // Getters
    int getDia() const;
    int getMes() const;
    int getAnio() const;

    //Setters
    void setDia(int d);
    void setMes(short int m);
    void setAnio(short int a);

    friend ostream& operator<<(ostream& os, const Fecha& f); // Sobrecarga del operador de salida << para mostrar una fecha como string.
    friend istream& operator>>(istream& is, Fecha& f); // Sobrecarga del operador de entrada >> para cargar una fecha desde una cadena.
};

#endif



