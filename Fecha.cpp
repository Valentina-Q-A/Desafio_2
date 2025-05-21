#include "Fecha.h"
#include <sstream>
#include <iomanip>
using namespace std;

Fecha::Fecha(short int d, short int m, short int a) {
    dia = d;
    mes = m;
    anio = a;
}

bool Fecha::esBisiesto(int anio) const {
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}

Fecha Fecha::sumarNoches(unsigned int noches) const {
    // Implementación simplificada: solo suma días (sin ajuste de mes)
    Fecha nueva = *this;
    nueva.dia += noches;
    return nueva;
}

bool Fecha::compararFecha(Fecha* f1, Fecha* f2) {
    if (f1->anio != f2->anio) return f1->anio < f2->anio;
    if (f1->mes != f2->mes) return f1->mes < f2->mes;
    return f1->dia < f2->dia;
}

string Fecha::mostrarFechaFormato() const {
    ostringstream oss;
    oss << setw(2) << setfill('0') << dia << "/"
        << setw(2) << setfill('0') << mes << "/"
        << anio;
    return oss.str();
}

bool Fecha::cargarDesdeCadena(const string& cadena) {
    stringstream ss(cadena);
    char slash;
    ss >> dia >> slash >> mes >> slash >> anio;
    return !ss.fail();
}

string Fecha::aCadena() const {
    return mostrarFechaFormato();
}

int Fecha::getDia() const { return dia; }
int Fecha::getMes() const { return mes; }
int Fecha::getAnio() const { return anio; }

void Fecha::setDia(int d) { dia = d; }
void Fecha::setMes(short int m) { mes = m; }
void Fecha::setAnio(short int a) { anio = a; }

ostream& operator<<(ostream& os, const Fecha& f) {
    os << f.aCadena();
    return os;
}

istream& operator>>(istream& is, Fecha& f) {
    string s;
    is >> s;
    f.cargarDesdeCadena(s);
    return is;
}
