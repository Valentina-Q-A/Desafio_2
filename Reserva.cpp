#include "Reserva.h"
#include <sstream>
#include <iostream>
#include "medicionString.h"
using namespace std;

/*
 * Constructor por defecto de la clase Reserva.
 * Se define vacío porque puede ser necesario crear un objeto sin inicializar
 * para luego asignarle los valores por separado, por ejemplo al cargar desde archivo.
 */
Reserva::Reserva() {}

/*
 * Constructor parametrizado de la clase Reserva.
 * Inicializa todos los atributos de la reserva usando una lista de inicialización.
 * Parámetros:
 * - id: identificador único de la reserva, como "Rxx"
 * - fi: fecha de inicio de la reserva (objeto Fecha)
 * - noches: cantidad de noches reservadas
 * - idAlojamiento: identificador del alojamiento reservado
 * - docCliente: documento del huésped que hace la reserva
 * - metodoPago: cadena con el método de pago usado
 * - fechaPago: fecha en la que se realizó el pago
 * - valor: monto total de la reserva
 * - comentario: texto adicional de la reserva
 */
Reserva::Reserva(string id, Fecha fi, unsigned int noches,
                 string idAlojamiento, string docCliente,
                 string metodoPago, Fecha fechaPago,
                 double valor, string comentario)
    : id(id), fechaInicio(fi), noches(noches),
    idAlojamiento(idAlojamiento), docCliente(docCliente),
    metodoPago(metodoPago), fechaPago(fechaPago),
    valor(valor), comentario(comentario) {
    // Se están haciendo 5 copias de string
    CONTAR_COPIA_STRING(); // id
    CONTAR_COPIA_STRING(); // idAlojamiento
    CONTAR_COPIA_STRING(); // docCliente
    CONTAR_COPIA_STRING(); // metodoPago
    CONTAR_COPIA_STRING(); // comentario
}
// Devuelve el ID de la reserva
string Reserva::getId() const { CONTAR_COPIA_STRING();
    return id; }
Fecha Reserva::getFechaInicio() const { return fechaInicio; } //Devuelve la fecha de inicio de la reserva.

/*
 * Calcula y devuelve la fecha de salida sumando las noches a la fecha de inicio.
 * Se usa el método sumarNoches() de la clase Fecha.
 */
Fecha Reserva::getFechaSalida() const { return fechaInicio.sumarNoches(noches); }

// Devuelve el documento del cliente que hizo la reserva.
string Reserva::getDocCliente() const { CONTAR_COPIA_STRING();
    return docCliente; }

//Devuelve el ID del alojamiento reservado.
string Reserva::getIdAlojamiento() const { CONTAR_COPIA_STRING();
    return idAlojamiento; }

// Devuelve el método de pago utilizado para la reserva.
string Reserva::getMetodoPago() const { CONTAR_COPIA_STRING();
    return metodoPago; }

// Devuelve el comentario registrado en la reserva.
string Reserva::getComentario() const { CONTAR_COPIA_STRING();
    return comentario; }

// Devuelve el valor total en dinero de la reserva.
double Reserva::getValor() const { return valor; }

/*
 * Metodo que determina si una nueva reserva se solapa (se cruza en fechas) con la reserva actual.
 * Parametros:
 *  - inicio: Fecha de inicio propuesta para la nueva reserva.
 *  - noches: Nueva Cantidad de noches que durara la nueva reserva.
 * retorno: true si hay traslape con la reserva actual, false si no hay conflicto de fechas.
 */
bool Reserva::fechaEnUso(Fecha inicio, unsigned int nochesNueva) const {
    Fecha finActual = getFechaSalida();  // Calcula la fecha de salida de la reserva actual
    Fecha finNueva = inicio.sumarNoches(nochesNueva); // Calcula la fecha de salida de la nueva reserva propuesta

    // No hay solapamiento si la nueva reserva termina antes o cuando comienza la actual,
    // o si comienza después o cuando termina la actual
    if (Fecha::compararFecha(&finNueva, &fechaInicio) <= 0 ||
        Fecha::compararFecha(&inicio, &finActual) >= 0) {
        return false; // no hay solapamiento
    }

    return true; // hay solapamiento
}

/*
 * Metodo que muestra un resumen basico de la reserva por consola.
 * Se utiliza principalmente para visualizaciones rapidas sin mostrar detalles completos.
 */
void Reserva::mostrarResumen() const {
    cout << "Reserva: " << id << endl;
    cout << "Alojamiento: " << idAlojamiento <<endl;
    cout << "Cliente: " << docCliente << endl;
    cout << "Valor: " << valor << endl;
    cout << "-----" << endl;
}

/*
 * Metodo estatico que crea un objeto Reserva a partir de una linea de texto con campos separados por '|'.
 * Cada campo se extrae usando getline y luego se convierte al tipo adecuado.
 * Se usa principalmente para reconstruir objetos Reserva desde archivos.
 */
Reserva* Reserva::cargarDesdeLinea(const string& linea) {
    stringstream ss(linea); // Se usa un stringstream para facilitar la extraccion campo a campo desde la linea
    string id, fechaIniStr, nochesStr, idAloj, docCli, metodo, fechaPagoStr, valorStr, comentario; // Se declaran variables auxiliares para cada campo de la reserva
    // Extraccion de cada campo separado por '|'
    CONTAR_GETLINE();
    CONTAR_STRING_ASSIGN();
    getline(ss, id, '|');
    CONTAR_GETLINE();
    CONTAR_STRING_ASSIGN();
    getline(ss, fechaIniStr, '|');
    CONTAR_GETLINE();
    CONTAR_STRING_ASSIGN();
    getline(ss, nochesStr, '|');
    CONTAR_GETLINE();
    CONTAR_STRING_ASSIGN();
    getline(ss, idAloj, '|');
    CONTAR_GETLINE();
    CONTAR_STRING_ASSIGN();
    getline(ss, docCli, '|');
    CONTAR_GETLINE();
    CONTAR_STRING_ASSIGN();
    getline(ss, metodo, '|');
    CONTAR_GETLINE();
    CONTAR_STRING_ASSIGN();
    getline(ss, fechaPagoStr, '|');
    CONTAR_GETLINE();
    CONTAR_STRING_ASSIGN();
    getline(ss, valorStr, '|');
    CONTAR_GETLINE();
    CONTAR_STRING_ASSIGN();
    getline(ss, comentario, '|');

    Fecha fi, fp; // Se crean objetos Fecha para la fecha de inicio y la fecha de pago
    fi.cargarDesdeCadena(fechaIniStr); // convierte fecha en string a objeto Fecha
    fp.cargarDesdeCadena(fechaPagoStr);

    // Se crea un nuevo objeto Reserva usando los valores convertidos.
    // stoi y stod convierten strings a int y double respectivamente.
    return new Reserva(id, fi, stoi(nochesStr), idAloj, docCli, metodo, fp, stod(valorStr), comentario);
}

/*
 * Metodo que convierte un objeto Reserva a una cadena de texto con el formato utilizado en los archivos del sistema.
 * Cada campo se concatena en orden y separado por el caracter '|'.
 * Este metodo es el inverso de cargarDesdeLinea y permite guardar una reserva en archivo de texto.
 */
string Reserva::aLinea() const {
    stringstream ss;
    ss << id << "|"
       << fechaInicio.aCadena() << "|"
       << noches << "|"
       << idAlojamiento << "|"
       << docCliente << "|"
       << metodoPago << "|"
       << fechaPago.aCadena() << "|"
       << valor << "|"
       << comentario;
    CONTAR_COPIA_STRING();
    return ss.str(); // Se retorna la linea ya construida en formato plano
}

/*
 * Metodo getter que devuelve la cantidad de noches de la reserva.
 * Este valor representa la duracion de la estadia del cliente.
 */
int Reserva::getNoches() const {
    return noches;
}
