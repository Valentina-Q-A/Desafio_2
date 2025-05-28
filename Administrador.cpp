#include "Administrador.h"
#include <sstream>
using namespace std;

Administrador::Administrador(string documento, short int exp, float estrellas)
    : documento(documento), exp(exp), estrellas(estrellas),
    numAlojamientos(0), capacidad(5)
{
    alojamientos = new Alojamiento*[capacidad];
}

Administrador::~Administrador() {
    delete[] alojamientos; // Solo borra el arreglo de punteros
}


void Administrador::mostrarAlojamientos() const {
    for (int i = 0; i < numAlojamientos; i++)
        alojamientos[i]->mostrar();
}

string Administrador::getDocumento() const { return documento; }
short int Administrador::getExp() const { return exp; }
float Administrador::getEstrellas() const { return estrellas; }
short int Administrador::getNumAlojamientos() const { return numAlojamientos; }

void Administrador::setDocumento(string d) { documento = d; }
void Administrador::setExp(short int e) { exp = e; }
void Administrador::setEstrellas(float est) { estrellas = est; }

Administrador* Administrador::cargarDesdeLinea(const string& linea) {
    stringstream ss(linea);
    string doc, expStr, estStr;

    getline(ss, doc, '|');
    getline(ss, expStr, '|');
    getline(ss, estStr, '|');

    return new Administrador(doc, stoi(expStr), stof(estStr));
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

Alojamiento* Administrador::getAlojamiento(int index) const {
    if (index >= 0 && index < numAlojamientos) {
        return alojamientos[index];
    }
    return nullptr;
}
