#include "Reserva.h"
#include <sstream>
#include <iostream>

Reserva::Reserva() {}

Reserva::Reserva(std::string id, Fecha fi, unsigned int noches,
                 std::string idAlojamiento, char docCliente,
                 std::string metodoPago, Fecha fechaPago,
                 double valor, std::string comentario)
    : id(id), fechaInicio(fi), noches(noches),
    idAlojamiento(idAlojamiento), docCliente(docCliente),
    metodoPago(metodoPago), fechaPago(fechaPago),
    valor(valor), comentario(comentario) {}

std::string Reserva::getId() const { return id; }
Fecha Reserva::getFechaInicio() const { return fechaInicio; }
Fecha Reserva::getFechaSalida() const { return fechaInicio.sumarNoches(noches); }
char Reserva::getDocCliente() const { return docCliente; }
std::string Reserva::getIdAlojamiento() const { return idAlojamiento; }
std::string Reserva::getMetodoPago() const { return metodoPago; }
std::string Reserva::getComentario() const { return comentario; }
double Reserva::getValor() const { return valor; }

bool Reserva::fechaEnUso(Fecha inicio, unsigned int nochesNueva) const {
    Fecha finActual = getFechaSalida();
    Fecha finNueva = inicio.sumarNoches(nochesNueva);
    return !(Fecha::compararFecha(&finNueva, &fechaInicio) ||
             Fecha::compararFecha(&finActual, &inicio));
}

void Reserva::mostrarResumen() const {
    std::cout << "Reserva: " << id << ", Alojamiento: " << idAlojamiento
              << ", Cliente: " << docCliente << ", Valor: " << valor << std::endl;
}

Reserva* Reserva::cargarDesdeLinea(const std::string& linea) {
    std::stringstream ss(linea);
    std::string id, fechaIniStr, idAloj, metodo, fechaPagoStr, comentario;
    Fecha fi, fp;
    unsigned int noches;
    char docCli;
    double valor;

    ss >> id >> fechaIniStr >> noches >> idAloj >> docCli >> metodo >> fechaPagoStr >> valor;
    std::getline(ss, comentario); // toma todo lo restante como comentario

    fi.cargarDesdeCadena(fechaIniStr);
    fp.cargarDesdeCadena(fechaPagoStr);

    return new Reserva(id, fi, noches, idAloj, docCli, metodo, fp, valor, comentario);
}

std::string Reserva::aLinea() const {
    std::stringstream ss;
    ss << id << " " << fechaInicio.aCadena() << " " << noches << " "
       << idAlojamiento << " " << docCliente << " " << metodoPago << " "
       << fechaPago.aCadena() << " " << valor << " " << comentario;
    return ss.str();
}
