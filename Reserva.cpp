#include "Reserva.h"
#include <sstream>
#include <iostream>
using namespace std;

Reserva::Reserva() {}

Reserva::Reserva(string id, Fecha fi, unsigned int noches,
                 string idAlojamiento, string docCliente,
                 string metodoPago, Fecha fechaPago,
                 double valor, string comentario)
    : id(id), fechaInicio(fi), noches(noches),
    idAlojamiento(idAlojamiento), docCliente(docCliente),
    metodoPago(metodoPago), fechaPago(fechaPago),
    valor(valor), comentario(comentario) {}

string Reserva::getId() const { return id; }
Fecha Reserva::getFechaInicio() const { return fechaInicio; }
Fecha Reserva::getFechaSalida() const { return fechaInicio.sumarNoches(noches); }
string Reserva::getDocCliente() const { return docCliente; }
string Reserva::getIdAlojamiento() const { return idAlojamiento; }
string Reserva::getMetodoPago() const { return metodoPago; }
string Reserva::getComentario() const { return comentario; }
double Reserva::getValor() const { return valor; }

bool Reserva::fechaEnUso(Fecha inicio, unsigned int nochesNueva) const {
    Fecha finActual = getFechaSalida();
    Fecha finNueva = inicio.sumarNoches(nochesNueva);
    return !(Fecha::compararFecha(&finNueva, &fechaInicio) ||
             Fecha::compararFecha(&finActual, &inicio));
}

void Reserva::mostrarResumen() const {
    cout << "Reserva: " << id << ", Alojamiento: " << idAlojamiento
         << ", Cliente: " << docCliente << ", Valor: " << valor << endl;
}

Reserva* Reserva::cargarDesdeLinea(const string& linea) {
    stringstream ss(linea);
    string id, fechaIniStr, idAloj, metodo, fechaPagoStr, comentario;
    Fecha fi, fp;
    unsigned int noches;
    string docCli;
    double valor;

    ss >> id >> fechaIniStr >> noches >> idAloj >> docCli >> metodo >> fechaPagoStr >> valor;
    getline(ss, comentario); // Toma el resto como comentario (hasta 1000 caracteres)

    fi.cargarDesdeCadena(fechaIniStr);
    fp.cargarDesdeCadena(fechaPagoStr);

    return new Reserva(id, fi, noches, idAloj, docCli, metodo, fp, valor, comentario);
}

string Reserva::aLinea() const {
    stringstream ss;
    ss << id << " " << fechaInicio.aCadena() << " " << noches << " "
       << idAlojamiento << " " << docCliente << " " << metodoPago << " "
       << fechaPago.aCadena() << " " << valor << " " << comentario;
    return ss.str();
}

