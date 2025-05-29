#include "Alojamiento.h"
#include <iostream>
#include <sstream> //Para usar stringstream (Conversion o procesamiento de strings)
#include "medicionString.h" //Medicion de recursos
using namespace std;

/*
 * Constructor de la clase Alojamiento.
 * Inicializa todos los atributos basicos de un alojamiento y reserva memoria dinamica
 * para el arreglo de punteros a reservas.

 * Parametros:
 * - codigo: identificador único del alojamiento
 * - nombre: nombre del alojamiento
 * - tipo: true (1) para casa, false(0) para apartamento
 * - direccion: dirección exacta
 * - municipio: municipio donde se encuentra
 * - departamento: departamento donde se encuentra
 * - precio: precio por noche
 * - anfitrionDoc: documento del administrador asociado
 * - amenidades: lista de amenidades como cadena separada
 */
Alojamiento::Alojamiento(string codigo, string nombre, bool tipo, string direccion, string municipio, string departamento, double precio, string anfitrionDoc, string amenidades)
    : codigo(codigo), nombre(nombre), tipo(tipo), direccion(direccion), municipio(municipio), departamento(departamento), precioPorNoche(precio), anfitrionDoc(anfitrionDoc), amenidades(amenidades), cantidadReservas(0), capacidad(5), cantAmenidades(0)
{
    reservas = new Reserva*[capacidad]; // Reserva espacio dinámico para apuntar a 5 reservas
}

/*
 * Destructor de la clase Alojamiento.
 * Libera la memoria dinamica utilizada para almacenar las reservas asociadas a este alojamiento.
 */
Alojamiento::~Alojamiento() {
    // Recorre el arreglo de reservas y libera cada reserva apuntada
    for (int i = 0; i < cantidadReservas; i++)
        delete reservas[i];

    // Libera el arreglo de punteros a Reserva
    delete[] reservas;
}

/*
 * Metodo que verifica si el alojamiento esta disponible en una fecha determinada.
 * Recorre todas las reservas actuales del alojamiento y comprueba si alguna se solapa con el rango de fechas dado.
 * Parametros:
 *   - f: Fecha de inicio solicitada por el usuario.
 *   - noches: Numero de noches de la reserva solicitada.
 * Retorna:
 *   - true si el alojamiento esta libre durante ese periodo.
 *   - false si hay traslape con alguna reserva existente.
 */
bool Alojamiento::estaDisponible(Fecha f, int noches) {
    for (int i = 0; i < cantidadReservas; i++) {
        if (reservas[i]->fechaEnUso(f, noches))
            return false;
    }
    return true;
}

/*
 * Metodo que muestra un mensaje indicando que el alojamiento esta disponible.
 * Se utiliza como mensaje informativo durante el proceso de seleccion de alojamiento.
 */
void Alojamiento::mostrarDisponibilidad() {
    cout << "Disponible\n";
}

/*
 * Metodo que imprime en pantalla la informacion general del alojamiento.
 * Muestra el nombre, precio por noche y la lista de amenidades separadas por coma.
 */
void Alojamiento::mostrar() const {
    cout << "Alojamiento: " << nombre << "\n";
    cout << "Precio por noche: COP$" << precioPorNoche << "\n";
    cout << "Amenidades:\n";

    string amenidad;
    stringstream ss(amenidades); // Se utiliza stringstream para separar las amenidades por coma
    CONTAR_GETLINE();
    while (getline(ss, amenidad, ',')) {// Itera sobre cada amenidad separada por coma
        cout << "  - " << amenidad << "\n";
    }
}

//Getters para acceder a las caracterisiticas
string Alojamiento::getCodigo() const { return codigo; }
bool Alojamiento::getTipo() const { return tipo; }
double Alojamiento::getPrecio() const { return precioPorNoche; }
string Alojamiento::getMunicipio() const { return municipio; }
string Alojamiento::getAmenidades() const { return amenidades; }
int Alojamiento::getCantReservas() const { return cantidadReservas; }

//Setter para actualizar las caracteristicas
void Alojamiento::setPrecio(double p) { precioPorNoche = p; }
void Alojamiento::setDireccion(const string& d) { direccion = d; }
void Alojamiento::setTipo(bool t) { tipo = t; }

/*
 * Metodo estatico que permite crear un objeto Alojamiento a partir de una linea de texto.
 * La linea debe tener los campos separados por el caracter '|', en el siguiente orden:
 * codigo | nombre | tipo | direccion | municipio | departamento | precio | documentoAnfitrion | amenidades
 * Retorna un puntero a un nuevo objeto Alojamiento creado con los datos extraidos.
 */
Alojamiento* Alojamiento::cargarDesdeLinea(const string& linea) {
    stringstream ss(linea); // Crear flujo de entrada a partir de la linea
    string codigo, nombre, direccion, municipio, departamento, anfitrionDoc;
    string tipoStr, precioStr, amenidadesStr;

    // Obtener cada campo separado por '|' y contar string
    CONTAR_GETLINE();
    getline(ss, codigo, '|');
    CONTAR_GETLINE();
    getline(ss, nombre, '|');
    CONTAR_GETLINE();
    getline(ss, tipoStr, '|');
    CONTAR_GETLINE();
    getline(ss, direccion, '|');
    CONTAR_GETLINE();
    getline(ss, municipio, '|');
    CONTAR_GETLINE();
    getline(ss, departamento, '|');
    CONTAR_GETLINE();
    getline(ss, precioStr, '|');
    CONTAR_GETLINE();
    getline(ss, anfitrionDoc, '|');
    CONTAR_GETLINE();
    getline(ss, amenidadesStr, '|');

    CONTAR_STRING_EQ();
    bool tipo = (tipoStr == "1"); // Convertir a booleano: "1" -> true (casa), otro -> false (apartamento)
    double precio = stod(precioStr);// Convertir precio de string a double

    // Retornar el nuevo objeto Alojamiento con los datos extraidos
    return new Alojamiento(codigo, nombre, tipo, direccion, municipio, departamento, precio, anfitrionDoc, amenidadesStr);
}

/*
 * Metodo que retorna el documento del anfitrion asociado al alojamiento.
 * No recibe parametros.
 * Retorna una cadena (string) con el documento del anfitrion.
 */
string Alojamiento::getAnfitrionDoc() const {
    return anfitrionDoc;
}

/*
 * Metodo que agrega una nueva reserva al alojamiento.
 * Si el arreglo actual de reservas esta lleno, lo redimensiona al doble de capacidad.
 * Recibe un puntero a objeto Reserva que sera agregado al arreglo.
 */
void Alojamiento::agregarReserva(Reserva* r) {
    CONTAR_STRING_EQ();
    // Si el arreglo esta lleno, se duplica la capacidad y se crea un nuevo arreglo
    if (cantidadReservas == capacidad) {
        capacidad *= 2;
        Reserva** nuevo = new Reserva*[capacidad];
        // Copia todas las reservas existentes al nuevo arreglo
        for (int i = 0; i < cantidadReservas; i++)
            nuevo[i] = reservas[i];
        delete[] reservas; // Libera la memoria del arreglo anterior
        reservas = nuevo; // Actualiza el puntero para que apunte al nuevo arreglo
    }
    // Agrega la nueva reserva al final del arreglo y actualiza el contador
    reservas[cantidadReservas++] = r;
}

/*
 * Metodo que devuelve el puntero a una reserva del alojamiento segun su posicion en el arreglo.
 * Verifica que el indice este dentro de los limites antes de acceder.
 * Retorna un puntero a Reserva si el indice es valido, o nullptr en caso contrario.
 */
Reserva* Alojamiento::getReserva(int index) const {
    if (index >= 0 && index < cantidadReservas) { // Verifica que el indice sea valido
        return reservas[index]; // Retorna la reserva en la posicion indicada
    }
    return nullptr; // Retorna nullptr si el indice esta fuera de rango
}

/*
 * Metodo que muestra por pantalla las reservas del alojamiento que se traslapan con un rango de fechas dado.
 * Recibe dos fechas: 'desde' y 'hasta', que representan el rango de interes.
 * Para cada reserva, verifica si su rango de fechas intersecta con el rango dado y la muestra si es asi.
 */
void Alojamiento::mostrarReservasPorRango(const Fecha& desde, const Fecha& hasta) const {
    for (int i = 0; i < cantidadReservas; i++) {
        Fecha ini = reservas[i]->getFechaInicio(); // Fecha de inicio de la reserva actual
        Fecha fin = reservas[i]->getFechaSalida(); // Fecha de salida (fin) de la reserva actual
        // Mostrar si hay traslape con el rango dado

        int cmpFinDesde = Fecha::compararFecha(&fin, &desde);  // Comparar fin de la reserva actual con la fecha 'desde'
        int cmpHastaIni = Fecha::compararFecha(&hasta, &ini);  // Comparar 'hasta' con el inicio de la reserva actual

        // Si no se cumple que fin < desde ni que hasta < inicio, entonces hay traslape
        if (!(cmpFinDesde < 0 || cmpHastaIni < 0)) {
            reservas[i]->mostrarResumen(); // Mostrar resumen de la reserva si hay traslape
        }
    }
}

/*
 * Metodo que elimina una reserva del alojamiento segun su ID.
 * Recibe el ID de la reserva a eliminar.
 * Busca la reserva con el ID especificado y, si la encuentra, la elimina desplazando el arreglo.
 * Retorna true si se elimina correctamente, false si no se encuentra la reserva.
 */
bool Alojamiento::eliminarReserva(const string& id) {
    for (int i = 0; i < cantidadReservas; i++) {
        CONTAR_STRING_EQ();
        if (reservas[i]->getId() == id) {  // Si se encuentra la reserva con el ID dado
            for (int j = i; j < cantidadReservas - 1; j++)
                reservas[j] = reservas[j + 1]; // Desplazar las reservas posteriores una posicion hacia atras
            cantidadReservas--; // Disminuir el contador de reservas
            return true; // Si no se encontro la reserva, retornar false
        }
    }
    return false;
}


