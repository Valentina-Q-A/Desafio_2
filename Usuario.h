#ifndef USUARIO_H
#define USUARIO_H

#include "Reserva.h"
#include <string>

class Usuario {
private:
    char documento;
    short int exp;
    float estrellas;
    Reserva** reservaciones;
    short int numReservas;
    int capacidad;

public:
    Usuario(char documento = '-', short int exp = 0, float estrellas = 0.0);
    ~Usuario();

    void agregarReserva(Reserva* r);
    bool fechaDisponible(Fecha f, int noches);
    void mostrarReservas() const;
    bool eliminarReserva(const std::string& id);

    char getDocumento() const;
    short int getExp() const;
    float getEstrellas() const;
    short int getNumReservas() const;

    void setDocumento(char d);
    void setExp(short int e);
    void setEstrellas(float est);

    static Usuario* cargarDesdeLinea(const std::string& linea);
};

#endif
