#ifndef RESERVA_H
#define RESERVA_H

#include "Fecha.h"
#include <string>
#include <iostream>

class Reserva {
private:
    std::string id;
    Fecha fechaInicio;
    unsigned int noches;
    std::string idAlojamiento;
    char docCliente;
    std::string metodoPago;
    Fecha fechaPago;
    double valor;
    std::string comentario;

public:
    Reserva();
    Reserva(std::string id, Fecha fi, unsigned int noches,
            std::string idAlojamiento, char docCliente,
            std::string metodoPago, Fecha fechaPago,
            double valor, std::string comentario);

    std::string getId() const;
    Fecha getFechaInicio() const;
    Fecha getFechaSalida() const;
    char getDocCliente() const;
    std::string getIdAlojamiento() const;
    std::string getMetodoPago() const;
    std::string getComentario() const;
    double getValor() const;

    bool fechaEnUso(Fecha inicio, unsigned int nochesNueva) const;
    void mostrarResumen() const;

    static Reserva* cargarDesdeLinea(const std::string& linea);
    std::string aLinea() const;
};

#endif
