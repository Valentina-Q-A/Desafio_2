#include "Administrador.h"
#include <iostream>

Administrador::Administrador(char documento, short int exp, float estrellas)
    : documento(documento), exp(exp), estrellas(estrellas),
    numAlojamientos(0), capacidad(5)
{
    alojamientos = new Alojamiento*[capacidad];
}

Administrador::~Administrador() {
    for (int i = 0; i < numAlojamientos; i++)
        delete alojamientos[i];
    delete[] alojamientos;
}

void Administrador::agregarAlojamiento(Alojamiento* a) {
    if (numAlojamientos == capacidad) {
        capacidad *= 2;
        Alojamiento** nuevo = new Alojamiento*[capacidad];
        for (int i = 0; i < numAlojamientos; i++)
            nuevo[i] = alojamientos[i];
        delete[] alojamientos;
        alojamientos = nuevo;
    }
    alojamientos[numAlojamientos++] = a;
}

bool Administrador::eliminarAlojamiento(const std::string& codigo) {
    for (int i = 0; i < numAlojamientos; i++) {
        if (alojamientos[i]->getCodigo() == codigo) {
            delete alojamientos[i];
            for (int j = i; j < numAlojamientos - 1; j++)
                alojamientos[j] = alojamientos[j + 1];
            numAlojamientos--;
            return true;
        }
    }
    return false;
}

void Administrador::mostrarAlojamientos() const {
    for (int i = 0; i < numAlojamientos; i++)
        alojamientos[i]->mostrar();
}

char Administrador::getDocumento() const { return documento; }
short int Administrador::getExp() const { return exp; }
float Administrador::getEstrellas() const { return estrellas; }
short int Administrador::getNumAlojamientos() const { return numAlojamientos; }

void Administrador::setDocumento(char d) { documento = d; }
void Administrador::setExp(short int e) { exp = e; }
void Administrador::setEstrellas(float est) { estrellas = est; }
