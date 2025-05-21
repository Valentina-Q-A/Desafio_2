#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H

#include "Alojamiento.h"
#include <string>
using namespace std;

class Administrador {
private:
    string documento;
    short int exp;
    float estrellas;
    Alojamiento** alojamientos;
    short int numAlojamientos;
    int capacidad;

public:
    Administrador(string documento = "-", short int exp = 0, float estrellas = 0.0);
    ~Administrador();

    void agregarAlojamiento(Alojamiento* a);
    bool eliminarAlojamiento(const string& codigo);
    void mostrarAlojamientos() const;

    string getDocumento() const;
    short int getExp() const;
    float getEstrellas() const;
    short int getNumAlojamientos() const;

    void setDocumento(string d);
    void setExp(short int e);
    void setEstrellas(float est);
};

#endif
