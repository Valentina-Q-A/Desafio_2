#ifndef ALOJAMIENTO_H
#define ALOJAMIENTO_H

#include "Reserva.h" // Para manejar el arreglo de reservas del alojamiento
#include <string>
using namespace std;

/*
 * Clase que representa un alojamiento ofertado por un anfitrion.
 * Contiene informacion basica del alojamiento, su disponibilidad, reservas asociadas
 * y metodos para gestionarlas.
 */
class Alojamiento {
private:
    string codigo;            // Codigo unico del alojamiento
    string nombre;            // Nombre del alojamiento
    bool tipo;                // Tipo de alojamiento: true = Casa, false = Apartamento
    string direccion;         // Direccion fisica del alojamiento
    string municipio;         // Municipio donde se ubica
    string departamento;      // Departamento donde se ubica
    double precioPorNoche;    // Precio por noche en COP
    string anfitrionDoc;      // Documento del anfitrion (para asociarlo)
    string amenidades;        // Cadena con lista de amenidades separadas por comas

    Reserva** reservas;       // Arreglo dinamico de punteros a reservas asociadas
    int cantidadReservas;     // Cantidad actual de reservas asociadas
    int capacidad;            // Capacidad actual del arreglo de reservas
    int cantAmenidades;       // Cantidad de amenidades (no se usa activamente, reservado para mejoras)

public:

    //Constructor que inicializa los atributos basicos y reserva espacio inicial para las reservas.
    Alojamiento(string codigo, string nombre, bool tipo, string direccion, string municipio, string departamento, double precio, string anfitrionDoc, string amenidades);

    //Destructor que libera la memoria ocupada por el arreglo de reservas y sus objetos.
    ~Alojamiento();

    void mostrarDisponibilidad(); //Mostrar disponibilidad
    bool estaDisponible(Fecha, int); // Verifica si el alojamiento esta disponible a partir de una fecha dada y por cierta cantidad de noches.

    // Getters a atributos del alojamiento.
    string getCodigo() const;
    bool getTipo() const;
    double getPrecio() const;
    string getMunicipio() const;
    string getAmenidades() const;
    int getCantReservas() const;

    // Setters para modifiacion de atributos del alojamiento
    void setPrecio(double);
    void setDireccion(const string&);
    void setTipo(bool);

    //Mostrar info basica del alojamiento
    void mostrar() const;

    string getAnfitrionDoc() const; // Devuelve el documento del anfitrion asociado a este alojamiento.

    // Metodo estatico que permite crear un objeto Alojamiento a partir de una linea de archivo (formato .txt).
    static Alojamiento* cargarDesdeLinea(const string& linea);

    void agregarReserva(Reserva* r); // Agrega una nueva reserva al alojamiento.
    Reserva* getReserva(int index) const; // Retorna la reserva en la posicion indicada si es valida, o nullptr si no lo es.
    void mostrarReservasPorRango(const Fecha& desde, const Fecha& hasta) const; //  Muestra las reservas activas dentro de un rango de fechas dado.
    bool eliminarReserva(const string& id); // Elimina una reserva del alojamiento a partir de su ID.

};

#endif
