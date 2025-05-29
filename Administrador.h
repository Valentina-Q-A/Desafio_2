#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H

#include "Alojamiento.h" // Gestionar la relacion entre administrador y sus alojamientos
#include <string>
using namespace std;

/*
 * Clase que representa un administrador en el sistema UdeAStay.
 * Cada administrador tiene un documento identificador, experiencia, puntuacion y un conjunto de alojamientos que administra.
 */
class Administrador {
private:
    string documento; //Id del admin
    short int exp; //Experiencia
    float estrellas; //Calificacion
    Alojamiento** alojamientos; // Arreglo dinamico de punteros a alojamientos de cada admin
    short int numAlojamientos; //Cantidad de alojamientos
    int capacidad; //Redimensionable

public:
    Administrador(string documento = "-", short int exp = 0, float estrellas = 0.0); // Constructor. Inicializa atributos basicos y reserva memoria para alojamientos
    ~Administrador(); // Destructor. Libera el arreglo de punteros a alojamientos (no los objetos en si)
    void mostrarAlojamientos() const; // Muestra en pantalla todos los alojamientos del administrador

    // Getters para acceder a los atributos privados
    string getDocumento() const;
    short int getExp() const;
    float getEstrellas() const;
    short int getNumAlojamientos() const;

    // Setters para modificar los atributos privados
    void setDocumento(string d);
    void setExp(short int e);
    void setEstrellas(float est);

    // Metodo estatico que permite construir un objeto Administrador desde una linea de texto con formato
    static Administrador* cargarDesdeLinea(const string& linea);

    void agregarAlojamiento(Alojamiento* a); // Agrega un puntero a alojamiento al arreglo de alojamientos
    Alojamiento* getAlojamiento(int index) const; // Retorna el puntero al alojamiento segun su posicion en el arreglo (si es valido)
};

#endif
