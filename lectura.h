#ifndef LECTURA_H
#define LECTURA_H

#include "Usuario.h"
#include "Administrador.h"
#include "Alojamiento.h"
#include "Reserva.h"

/*
* Funcion para cargar los usuarios desde un archivo de texto.
* Cada linea del archivo representa un usuario codificado, que se interpreta usando el metodo cargarDesdeLinea.
* El arreglo de punteros a Usuario se redimensiona dinamicamente si es necesario.
* Retorna la cantidad de usuarios cargados. Si no se puede abrir el archivo, retorna 0 y pone el puntero en nullptr.
*/
int cargarUsuarios(const string& nombreArchivo, Usuario**& usuarios);

/*
* Funcion para cargar administradores desde un archivo de texto.
* Cada linea del archivo contiene la informacion de un administrador que se convierte en objeto usando cargarDesdeLinea().
* El arreglo de punteros a Administrador se redimensiona dinamicamente si se llena.
* Retorna la cantidad de administradores cargados. Si hay error al abrir el archivo, retorna 0 y deja el puntero en nullptr.
* Misma logica que para usuarios.
*/
int cargarAdministradores(const string& nombreArchivo, Administrador**& admins);

/*
* Funcion para cargar alojamientos desde un archivo de texto.
* Cada linea del archivo contiene los datos de un alojamiento, que se convierte en objeto usando Alojamiento::cargarDesdeLinea().
* El arreglo de punteros a Alojamiento se redimensiona dinamicamente si se alcanza su capacidad.
* Retorna la cantidad de alojamientos cargados. Si ocurre un error al abrir el archivo, retorna 0 y el puntero queda en nullptr.
* Misma logica que para usuarios y administradores.
*/
int cargarAlojamientos(const string& nombreArchivo, Alojamiento**& alojamientos);

/*
* Funcion que asocia cada alojamiento con su administrador correspondiente.
* Utiliza el documento del anfitrion (almacenado en cada alojamiento) para encontrar el administrador correspondiente
* y agrega dicho alojamiento a la lista de alojamientos del administrador.
* No se realiza medicion de recursos porque esta funcion se ejecuta una sola vez durante la carga.
*/
void asociarAlojamientos(Administrador** admins, int cantAdmins, Alojamiento** alojamientos, int cantAlojamientos);

/*
* Funcion para cargar todas las reservas desde un archivo de texto.
* Cada linea del archivo representa una reserva, codificada con separador '|'.
* Se almacena dinamicamente cada objeto Reserva usando el metodo estatico cargarDesdeLinea().
* La funcion redimensiona el arreglo si se supera la capacidad inicial.
* Retorna la cantidad total de reservas cargadas, y actualiza el puntero doble pasado por referencia.
*/
int cargarReservas(const string& nombreArchivo, Reserva**& reservas);

/*
* Funcion que asocia cada reserva a su respectivo usuario y alojamiento.
* La asociacion se realiza recorriendo todos los arreglos y buscando coincidencia por documento (usuario)
* y por codigo de alojamiento.
* Se actualiza cada objeto Usuario y Alojamiento con un puntero a la reserva correspondiente.
* La operacion se realiza en dos fases por reserva:
*   1. Asociar al usuario por su documento.
*   2. Asociar al alojamiento por su codigo.
*/
void asociarReservas(Reserva** reservas, int cantReservas, Usuario** usuarios,
                     int cantUsuarios, Alojamiento** alojamientos, int cantAlojamientos);

/*
* Funcion para guardar todas las reservas actuales en un archivo de texto.
* Cada reserva se convierte a una linea con el formato definido mediante el metodo aLinea(),
* y se escribe en una nueva linea del archivo.
*
* Parametros:
*  - ruta: nombre del archivo o ruta completa donde se desea guardar la informacion.
*  - reservas: arreglo de punteros a objetos Reserva que se desea almacenar.
*  - numReservas: cantidad de reservas presentes en el arreglo.
*/
void guardarReservas(const string& ruta, Reserva** reservas, int numReservas);

/*
 *Funcion para distinguir mayusuclas y minusculas
 */
string aMinusculas(const string& s);

/*
* Funcion que verifica si una fecha dada se encuentra dentro del rango valido:
* desde la fecha de corte (leida desde archivo) hasta 365 dias despues de esta.
* Parametros:
*  - f: fecha que se desea validar.
* Retorna:
*  - true si la fecha esta dentro del rango [fechaCorte, fechaCorte + 365 dias]
*  - false en caso contrario.
* Se utiliza la funcion auxiliar leerFechaCorte() para obtener la fecha base.
*/
bool fechaDentroDelRango(const Fecha& f);

/*
* Funcion que convierte una fecha en formato numerico a una representacion extendida,
* incluyendo el nombre del dia de la semana y el mes por su nombre.
* Ejemplo: para una fecha 28/05/2025 retorna "Miercoles, 28 de Mayo del 2025".
* Parametros:
*  - f: objeto Fecha con dia, mes y anio.
* Retorna:
*  - Cadena con la fecha en formato extendido.
*/
string fechaExtendida(const Fecha& f);

/*
 * Funcion que lee la fecha de corte desde un archivo de texto.
 * Esta fecha se utiliza como referencia para validar si una reserva futura
 * se encuentra dentro del rango permitido (365 dias despues de la fecha de corte).
 * Si el archivo no existe o no puede abrirse, retorna por defecto la fecha 01/01/2000.
 */
Fecha leerFechaCorte(const string& ruta);

/*
 * Funcion que guarda la nueva fecha de corte en un archivo de texto.
 * Esta fecha marca el limite inferior del rango de fechas permitidas
 * para realizar nuevas reservas dentro del sistema.
 * Si el archivo no puede abrirse, se muestra un mensaje de error.
 * El contenido anterior del archivo es sobrescrito.
 */
void guardarFechaCorte(const string& ruta, const Fecha& fecha);

/*
 * Funcion que obtiene el mayor numero de identificador de las reservas existentes,
 * considerando tanto las reservas actuales como las historicas.
 * Esto permite generar un nuevo ID unico para la proxima reserva.
 * Se asume que el formato del ID es "R<number>", por ejemplo "R104".
 */
int obtenerUltimoNumeroReserva(Reserva** actuales, int nActuales, Reserva** historicas, int nHistoricas);

#endif
