#include "Usuario.h"
#include <iostream>
#include <sstream>
#include "medicionString.h"
using namespace std;

/*
 * Variables globales externas declaradas en main.cpp
 * Se usan para medir consumo de recursos
 */
extern long long iteracionesTotales;
extern long long memoriaDurante;
extern long long memoriaFinal;


//Macros para facilitar el conteo de recursos
#define CONTAR_ITERACION() iteracionesTotales++ // Incrementa el contador global de iteraciones

// Incrementa los contadores de memoria durante y final
// El valor puede ser positivo (asignacion) o negativo (liberacion)
#define CONTAR_MEMORIA(bytes) \
memoriaDurante += ((long long)(bytes) >= 0 ? (long long)(bytes) : -(long long)(bytes)); \
    memoriaFinal += (long long)(bytes);

/*
 * Constructor de la clase Usuario.
 * Inicializa los atributos con los valores recibidos por parametro,
 * y crea un arreglo dinamico para almacenar hasta 5 reservas inicialmente.
 */
Usuario::Usuario(string documento, short int exp, float estrellas)
    : documento(documento), exp(exp), estrellas(estrellas),
    numReservas(0), capacidad(5)
{
    CONTAR_COPIA_STRING();
    reservaciones = new Reserva*[capacidad]; // Se crea el arreglo dinamico de punteros a Reserva con capacidad inicial 5
    CONTAR_STRING_ASSIGN();
}

/*
 * Destructor de la clase Usuario.
 * Libera la memoria dinamica utilizada para almacenar las reservas del usuario.
 */
Usuario::~Usuario() {
    // Se eliminan uno por uno los objetos Reserva apuntados por el arreglo
    for (int i = 0; i < numReservas; i++)
        delete reservaciones[i]; // Libera la memoria de cada reserva individual
    delete[] reservaciones; // Finalmente se libera el arreglo de punteros
}

/*
 * Metodo para agregar una reserva al usuario.
 * Si el arreglo de reservas esta lleno, se redimensiona duplicando su capacidad.
 */
void Usuario::agregarReserva(Reserva* r) {
    CONTAR_STRING_EQ();
    // Si se alcanzo la capacidad maxima del arreglo, se redimensiona
    if (numReservas == capacidad) {
        capacidad *= 2;
        Reserva** nuevo = new Reserva*[capacidad]; // Se crea un nuevo arreglo con la nueva capacidad
        for (int i = 0; i < numReservas; i++)
            nuevo[i] = reservaciones[i];
        // Se libera el arreglo anterior y se actualiza el puntero
        delete[] reservaciones;
        reservaciones = nuevo;
    }
    // Se agrega la nueva reserva y se incrementa el contador
    reservaciones[numReservas++] = r;
}

/*
 * Metodo para verificar si el usuario tiene disponibilidad en una fecha dada.
 * Recorre todas sus reservas y retorna false si alguna se solapa con el rango indicado.
 * Parametros:
 * - f: fecha de inicio propuesta para la nueva reserva.
 * - noches: cantidad de noches a verificar.
 * Retorna:
 * - true si no hay traslapes con reservas existentes, false en caso contrario.
 */
bool Usuario::fechaDisponible(Fecha f, int noches) {
    for (int i = 0; i < numReservas; i++)
        if (reservaciones[i]->fechaEnUso(f, noches))
            return false; // Hay solapamiento, no disponible
    return true;
}

/*
 * Metodo para mostrar todas las reservas asociadas a un usuario.
 * Imprime por consola un resumen de cada reserva, si esta no es nula.
 * Adicionalmente, contabiliza iteraciones, uso de memoria y comparaciones
 * para fines de medicion de recursos.
 */
void Usuario::mostrarReservas() const {
    cout << "Reservas del usuario " << documento << ":\n";
    for (int i = 0; i < numReservas; i++){
        CONTAR_ITERACION(); // Cada reserva como una iteración
        CONTAR_STRING_EQ();
        if(reservaciones[i] != nullptr){
            CONTAR_MEMORIA(sizeof(Reserva)); // Se suma memoria usada por la reserva
            reservaciones[i]->mostrarResumen(); // Se imprime el resumen de la reserva
        }
    }
    cout << endl;
}

/*
 * Metodo para eliminar una reserva del usuario, dada su ID.
 * Recorre el arreglo de reservaciones buscando coincidencia con el ID.
 * Si se encuentra, se elimina desplazando los elementos siguientes hacia la izquierda.
 * La cantidad total de reservas (`numReservas`) se decrementa en 1.
 * Retorna true si la reserva fue encontrada y eliminada, false si no se encontro.
 */
bool Usuario::eliminarReserva(const string& id) {
    for (int i = 0; i < numReservas; i++) {
        CONTAR_STRING_EQ();
        if (reservaciones[i]->getId() == id) {
            // Se elimina desplazando las reservas restantes
            for (int j = i; j < numReservas - 1; j++) {
                reservaciones[j] = reservaciones[j + 1];
            }
            numReservas--;
            return true;
        }
    }
    return false;
}

//Getters para acceder a los atributos
string Usuario::getDocumento() const { CONTAR_COPIA_STRING();
    return documento; }
short int Usuario::getExp() const { return exp; }
float Usuario::getEstrellas() const { return estrellas; }
short int Usuario::getNumReservas() const { return numReservas; }

//Setters para modificar los atributos
void Usuario::setDocumento(string d) { CONTAR_STRING_ASSIGN();
    documento = d; }
void Usuario::setExp(short int e) { exp = e; }
void Usuario::setEstrellas(float est) { estrellas = est; }

/*
 * Metodo estatico para cargar un objeto Usuario a partir de una linea de texto.
 * La linea debe tener el formato: documento|experiencia|estrellas
 * Se utiliza stringstream para separar los campos por el caracter '|'.
 */
Usuario* Usuario::cargarDesdeLinea(const string& linea) {
    stringstream ss(linea); // Se crea un flujo para leer la linea
    string doc, expStr, estStr;
    CONTAR_GETLINE();
    getline(ss, doc, '|');
    CONTAR_GETLINE();
    getline(ss, expStr, '|');
    CONTAR_GETLINE();
    getline(ss, estStr, '|');

    return new Usuario(doc, stoi(expStr), stof(estStr)); // Se convierte la experiencia y estrellas a sus respectivos tipos
}


