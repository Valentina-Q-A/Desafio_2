#ifndef ALOJAMIENTO_H
#define ALOJAMIENTO_H

#include "Reserva.h"
#include <string>

class Alojamiento {
private:
    std::string codigo;
    std::string nombre;
    bool tipo;
    std::string direccion;
    std::string municipio;
    std::string departamento;
    double precioPorNoche;
    char anfitrionDoc;
    std::string amenidades;
    Reserva** reservas;
    int cantidadReservas;
    int capacidad;
    int cantAmenidades;

public:
    Alojamiento(std::string codigo, std::string nombre, bool tipo,
                std::string direccion, std::string municipio,
                std::string departamento, double precio,
                char anfitrionDoc);

    ~Alojamiento();

    void mostrarDisponibilidad();
    bool estaDisponible(Fecha, int);

    std::string getCodigo() const;
    bool getTipo() const;
    double getPrecio() const;
    std::string getMunicipio() const;
    std::string getAmenidades() const;
    int getCantReservas() const;

    void setPrecio(double);
    void setDireccion(const std::string&);
    void setTipo(bool);
    void mostrar() const;

    static Alojamiento* cargarDesdeLinea(const std::string& linea);
};

#endif
