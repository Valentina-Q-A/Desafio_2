#include "Alojamiento.h"
#include <iostream>
#include <sstream>
using namespace std;

Alojamiento::Alojamiento(string codigo, string nombre, bool tipo,
                         string direccion, string municipio,
                         string departamento, double precio,
                         string anfitrionDoc)
    : codigo(codigo), nombre(nombre), tipo(tipo), direccion(direccion),
    municipio(municipio), departamento(departamento), precioPorNoche(precio),
    anfitrionDoc(anfitrionDoc), cantidadReservas(0), capacidad(5), cantAmenidades(0)
{
    reservas = new Reserva*[capacidad];
}

Alojamiento::~Alojamiento() {
    for (int i = 0; i < cantidadReservas; i++)
        delete reservas[i];
    delete[] reservas;
}

bool Alojamiento::estaDisponible(Fecha f, int noches) {
    for (int i = 0; i < cantidadReservas; i++) {
        if (reservas[i]->fechaEnUso(f, noches))
            return false;
    }
    return true;
}

void Alojamiento::mostrarDisponibilidad() {
    cout << "Disponible\n";
}

void Alojamiento::mostrar() const {
    cout << "Alojamiento: " << nombre << " - Precio: " << precioPorNoche << "\n";
}

string Alojamiento::getCodigo() const { return codigo; }
bool Alojamiento::getTipo() const { return tipo; }
double Alojamiento::getPrecio() const { return precioPorNoche; }
string Alojamiento::getMunicipio() const { return municipio; }
string Alojamiento::getAmenidades() const { return amenidades; }
int Alojamiento::getCantReservas() const { return cantidadReservas; }

void Alojamiento::setPrecio(double p) { precioPorNoche = p; }
void Alojamiento::setDireccion(const string& d) { direccion = d; }
void Alojamiento::setTipo(bool t) { tipo = t; }

Alojamiento* Alojamiento::cargarDesdeLinea(const string& linea) {
    stringstream ss(linea);
    string codigo, nombre, direccion, municipio, departamento, anfitrionDoc;
    string tipoStr, precioStr;

    getline(ss, codigo, '|');
    getline(ss, nombre, '|');
    getline(ss, tipoStr, '|');
    getline(ss, direccion, '|');
    getline(ss, municipio, '|');
    getline(ss, departamento, '|');
    getline(ss, precioStr, '|');
    getline(ss, anfitrionDoc, '|');

    bool tipo = (tipoStr == "1");
    double precio = stod(precioStr);

    return new Alojamiento(codigo, nombre, tipo, direccion, municipio, departamento, precio, anfitrionDoc);
}

string Alojamiento::getAnfitrionDoc() const {
    return anfitrionDoc;
}

void Alojamiento::agregarReserva(Reserva* r) {
    if (cantidadReservas == capacidad) {
        capacidad *= 2;
        Reserva** nuevo = new Reserva*[capacidad];
        for (int i = 0; i < cantidadReservas; i++)
            nuevo[i] = reservas[i];
        delete[] reservas;
        reservas = nuevo;
    }
    reservas[cantidadReservas++] = r;
}

Reserva* Alojamiento::getReserva(int index) const {
    if (index >= 0 && index < cantidadReservas) {
        return reservas[index];
    }
    return nullptr;
}

void Alojamiento::mostrarReservasPorRango(const Fecha& desde, const Fecha& hasta) const {
    for (int i = 0; i < cantidadReservas; i++) {
        Fecha ini = reservas[i]->getFechaInicio();
        Fecha fin = reservas[i]->getFechaSalida();
        // Mostrar si hay traslape con el rango dado
        if (!(Fecha::compararFecha(&fin, &desde) || Fecha::compararFecha(&hasta, &ini))) {
            reservas[i]->mostrarResumen();
        }
    }
}
