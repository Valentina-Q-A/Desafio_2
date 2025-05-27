#ifndef ALOJAMIENTO_H
#define ALOJAMIENTO_H

#include "Reserva.h"
#include <string>
using namespace std;

class Alojamiento {
private:
    string codigo;
    string nombre;
    bool tipo; // true = Casa, false = Apartamento
    string direccion;
    string municipio;
    string departamento;
    double precioPorNoche;
    string anfitrionDoc;
    string amenidades;

    Reserva** reservas;
    int cantidadReservas;
    int capacidad;
    int cantAmenidades;

public:
    Alojamiento(string codigo, string nombre, bool tipo,
                string direccion, string municipio,
                string departamento, double precio,
                string anfitrionDoc);

    ~Alojamiento();

    void mostrarDisponibilidad();
    bool estaDisponible(Fecha, int);

    string getCodigo() const;
    bool getTipo() const;
    double getPrecio() const;
    string getMunicipio() const;
    string getAmenidades() const;
    int getCantReservas() const;

    void setPrecio(double);
    void setDireccion(const string&);
    void setTipo(bool);
    void mostrar() const;

    string getAnfitrionDoc() const;
    static Alojamiento* cargarDesdeLinea(const string& linea);

    void agregarReserva(Reserva* r);
    Reserva* getReserva(int index) const;
    void mostrarReservasPorRango(const Fecha& desde, const Fecha& hasta) const;
    bool eliminarReserva(const string& id);

};

#endif
