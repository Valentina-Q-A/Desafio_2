#ifndef USUARIO_H
#define USUARIO_H

#include "Reserva.h"
#include <string>
using namespace std;

/*
 * Clase Usuario
 * Representa un cliente que puede realizar reservas en alojamientos.
 * Cada usuario tiene un documento, experiencia, puntuacion y un arreglo dinamico de reservas.
 */
class Usuario {
private:
    string documento;            // Cedula o identificador del usuario
    short int exp;               // Anios de experiencia como usuario de la plataforma
    float estrellas;             // Calificacion promedio del usuario (de 0 a 5)
    Reserva** reservaciones;     // Arreglo dinamico de punteros a reservas
    short int numReservas;       // Cantidad de reservas actuales
    int capacidad;               // Capacidad maxima del arreglo actual

public:
    // Constructor con valores por defecto para inicializar un usuario vacio
    Usuario(string documento = "-", short int exp = 0, float estrellas = 0.0);

    // Destructor para liberar memoria dinamica
    ~Usuario();

    void agregarReserva(Reserva* r);// Agrega una reserva al arreglo (redimensiona si es necesario)
    bool fechaDisponible(Fecha f, int noches);// Verifica si el usuario tiene disponibilidad en un rango de fechas
    void mostrarReservas() const;// Muestra todas las reservas asociadas al usuario
    bool eliminarReserva(const string& id); // Elimina una reserva por ID (sin liberar memoria de la reserva)

    //Getters para obener atributos
    string getDocumento() const;
    short int getExp() const;
    float getEstrellas() const;
    short int getNumReservas() const;

    //Setters para modificar atributos
    void setDocumento(string d);
    void setExp(short int e);
    void setEstrellas(float est);

    // Metodo estatico para crear un usuario a partir de una linea de archivo
    static Usuario* cargarDesdeLinea(const string& linea);
};

#endif
