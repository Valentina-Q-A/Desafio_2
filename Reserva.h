#ifndef RESERVA_H
#define RESERVA_H

#include "Fecha.h"
#include <string>
#include <iostream>
using namespace std;

class Reserva {
private:
    string id;
    Fecha fechaInicio;
    unsigned int noches;
    string idAlojamiento;
    string docCliente;
    string metodoPago;
    Fecha fechaPago;
    double valor;
    string comentario;

public:
    Reserva();
    Reserva(string id, Fecha fi, unsigned int noches,
            string idAlojamiento, string docCliente,
            string metodoPago, Fecha fechaPago,
            double valor, string comentario);

    string getId() const;
    Fecha getFechaInicio() const;
    Fecha getFechaSalida() const;
    string getDocCliente() const;
    string getIdAlojamiento() const;
    string getMetodoPago() const;
    string getComentario() const;
    double getValor() const;

    bool fechaEnUso(Fecha inicio, unsigned int nochesNueva) const;
    void mostrarResumen() const;

    static Reserva* cargarDesdeLinea(const string& linea);
    string aLinea() const;
};

#endif
