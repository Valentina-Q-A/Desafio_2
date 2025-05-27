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
    cout << "Reserva: " << id << endl;
    cout << "Alojamiento: " << idAlojamiento <<endl;
    cout << "Cliente: " << docCliente << endl;
    cout << "Valor: " << valor << endl;
    cout << "-----" << endl;
}

Reserva* Reserva::cargarDesdeLinea(const string& linea) {
    stringstream ss(linea);
    string id, fechaIniStr, nochesStr, idAloj, docCli, metodo, fechaPagoStr, valorStr, comentario;

    getline(ss, id, '|');
    getline(ss, fechaIniStr, '|');
    getline(ss, nochesStr, '|');
    getline(ss, idAloj, '|');
    getline(ss, docCli, '|');
    getline(ss, metodo, '|');
    getline(ss, fechaPagoStr, '|');
    getline(ss, valorStr, '|');
    getline(ss, comentario, '|');

    Fecha fi, fp;
    fi.cargarDesdeCadena(fechaIniStr);
    fp.cargarDesdeCadena(fechaPagoStr);

    return new Reserva(id, fi, stoi(nochesStr), idAloj, docCli, metodo, fp, stod(valorStr), comentario);
}


string Reserva::aLinea() const {
    stringstream ss;
    ss << id << "|"
       << fechaInicio.aCadena() << "|"
       << noches << "|"
       << idAlojamiento << "|"
       << docCliente << "|"
       << metodoPago << "|"
       << fechaPago.aCadena() << "|"
       << valor << "|"
       << comentario;
    return ss.str();
}
