#include "Usuario.h"
#include <iostream>
#include <sstream>

Usuario::Usuario(char documento, short int exp, float estrellas)
    : documento(documento), exp(exp), estrellas(estrellas),
    numReservas(0), capacidad(5)
{
    reservaciones = new Reserva*[capacidad];
}

Usuario::~Usuario() {
    for (int i = 0; i < numReservas; i++)
        delete reservaciones[i];
    delete[] reservaciones;
}

void Usuario::agregarReserva(Reserva* r) {
    if (numReservas == capacidad) {
        capacidad *= 2;
        Reserva** nuevo = new Reserva*[capacidad];
        for (int i = 0; i < numReservas; i++)
            nuevo[i] = reservaciones[i];
        delete[] reservaciones;
        reservaciones = nuevo;
    }
    reservaciones[numReservas++] = r;
}

bool Usuario::fechaDisponible(Fecha f, int noches) {
    for (int i = 0; i < numReservas; i++)
        if (reservaciones[i]->fechaEnUso(f, noches))
            return false;
    return true;
}

void Usuario::mostrarReservas() const {
    std::cout << "Reservas del usuario " << documento << ":\n";
    for (int i = 0; i < numReservas; i++)
        reservaciones[i]->mostrarResumen();
}

bool Usuario::eliminarReserva(const std::string& id) {
    for (int i = 0; i < numReservas; i++) {
        if (reservaciones[i]->getId() == id) {
            delete reservaciones[i];
            for (int j = i; j < numReservas - 1; j++)
                reservaciones[j] = reservaciones[j + 1];
            numReservas--;
            return true;
        }
    }
    return false;
}

char Usuario::getDocumento() const { return documento; }
short int Usuario::getExp() const { return exp; }
float Usuario::getEstrellas() const { return estrellas; }
short int Usuario::getNumReservas() const { return numReservas; }

void Usuario::setDocumento(char d) { documento = d; }
void Usuario::setExp(short int e) { exp = e; }
void Usuario::setEstrellas(float est) { estrellas = est; }

Usuario* Usuario::cargarDesdeLinea(const std::string& linea) {
    std::stringstream ss(linea);
    char doc;
    int exp;
    float est;
    ss >> doc >> exp >> est;
    return new Usuario(doc, exp, est);
}
