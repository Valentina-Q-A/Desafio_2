#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H

#include "Alojamiento.h"

class Administrador {
private:
    char documento;
    short int exp;
    float estrellas;
    Alojamiento** alojamientos;
    short int numAlojamientos;
    int capacidad;

public:
    Administrador(char documento = '-', short int exp = 0, float estrellas = 0.0);
    ~Administrador();

    void agregarAlojamiento(Alojamiento* a);
    bool eliminarAlojamiento(const std::string& codigo);
    void mostrarAlojamientos() const;

    char getDocumento() const;
    short int getExp() const;
    float getEstrellas() const;
    short int getNumAlojamientos() const;

    void setDocumento(char d);
    void setExp(short int e);
    void setEstrellas(float est);
};

#endif
