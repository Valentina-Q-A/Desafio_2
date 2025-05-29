#ifndef RESERVA_H
#define RESERVA_H

#include "Fecha.h"
#include <string>
using namespace std;

/*
 * Clase Reserva
 * Representa una reserva de alojamiento en el sistema.
 * Contiene informacion sobre fechas, cliente, metodo de pago y valor.
 */
class Reserva {
private:
    string id;                // Identificador unico de la reserva
    Fecha fechaInicio;        // Fecha de inicio de la reserva
    unsigned int noches;      // Cantidad de noches reservadas
    string idAlojamiento;     // Codigo del alojamiento reservado
    string docCliente;        // Documento del cliente que hizo la reserva
    string metodoPago;        // Metodo de pago utilizado
    Fecha fechaPago;          // Fecha en la que se realizo el pago
    double valor;             // Valor total de la reserva
    string comentario;        // Comentario adicional
public:
    //Constructor por defecto
    Reserva();
    //COnstructor con parametros
    Reserva(string id, Fecha fi, unsigned int noches,string idAlojamiento, string docCliente,string metodoPago, Fecha fechaPago, double valor, string comentario);

    // Getters para acceder a los atributos
    string getId() const;
    Fecha getFechaInicio() const;
    Fecha getFechaSalida() const;
    string getDocCliente() const;
    string getIdAlojamiento() const;
    string getMetodoPago() const;
    string getComentario() const;
    double getValor() const;
    string getID() const { return id; }

    //Verifica si la reserva se solapa con una nueva fecha y duracion
    bool fechaEnUso(Fecha inicio, unsigned int nochesNueva) const;

    // Imprime un resumen de la reserva
    void mostrarResumen() const;

    static Reserva* cargarDesdeLinea(const string& linea); // Crea una reserva desde una linea de texto
    string aLinea() const; // Convierte los datos a una linea de texto

    //Retorna el numero de noches de la reserva
    int getNoches() const;

};

#endif
