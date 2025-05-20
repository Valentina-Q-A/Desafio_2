#include "Alojamiento.h"
#include <iostream>
#include <sstream>

Alojamiento::Alojamiento(std::string codigo, std::string nombre, bool tipo,
                         std::string direccion, std::string municipio,
                         std::string departamento, double precio,
                         char anfitrionDoc)
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
        if (reservas[i]->fechaEnUso(f, noches)) return false;
    }
    return true;
}

void Alojamiento::mostrarDisponibilidad() {
    std::cout << "Disponible\n";
}

void Alojamiento::mostrar() const {
    std::cout << "Alojamiento: " << nombre << " - Precio: " << precioPorNoche << "\n";
}

std::string Alojamiento::getCodigo() const { return codigo; }
bool Alojamiento::getTipo() const { return tipo; }
double Alojamiento::getPrecio() const { return precioPorNoche; }
std::string Alojamiento::getMunicipio() const { return municipio; }
std::string Alojamiento::getAmenidades() const { return amenidades; }
int Alojamiento::getCantReservas() const { return cantidadReservas; }

void Alojamiento::setPrecio(double p) { precioPorNoche = p; }
void Alojamiento::setDireccion(const std::string& d) { direccion = d; }
void Alojamiento::setTipo(bool t) { tipo = t; }

Alojamiento* Alojamiento::cargarDesdeLinea(const std::string& linea) {
    std::stringstream ss(linea);
    std::string codigo, nombre, direccion, municipio, departamento;
    bool tipo;
    double precio;
    char docAdmin;

    ss >> codigo >> nombre >> tipo >> direccion >> municipio >> departamento >> precio >> docAdmin;

    return new Alojamiento(codigo, nombre, tipo, direccion, municipio, departamento, precio, docAdmin);
}
