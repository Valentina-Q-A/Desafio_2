#include "Fecha.h"
#include <sstream>
#include <iomanip>

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

std::string Fecha::mostrarFechaFormato() const {
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << dia << "/"
        << std::setw(2) << std::setfill('0') << mes << "/"
        << anio;
    return oss.str();
}

bool Fecha::cargarDesdeCadena(const std::string& cadena) {
    std::stringstream ss(cadena);
    char slash;
    ss >> dia >> slash >> mes >> slash >> anio;
    return !ss.fail();
}

std::string Fecha::aCadena() const {
    return mostrarFechaFormato();
}

int Fecha::getDia() const { return dia; }
int Fecha::getMes() const { return mes; }
int Fecha::getAnio() const { return anio; }

void Fecha::setDia(int d) { dia = d; }
void Fecha::setMes(short int m) { mes = m; }
void Fecha::setAnio(short int a) { anio = a; }

std::ostream& operator<<(std::ostream& os, const Fecha& f) {
    os << f.aCadena();
    return os;
}

std::istream& operator>>(std::istream& is, Fecha& f) {
    std::string s;
    is >> s;
    f.cargarDesdeCadena(s);
    return is;
}
