#include "lectura.h"// Cabecera
#include <fstream>  // Para manejo de archivos de texto (ifstream, ofstream)
#include <iostream>
#include <cctype>   // Para funciones de manipulacion de caracteres (tolower, isdigit)
#include "Administrador.h"  // Para instanciar y manipular objetos de tipo Administrador
#include <ctime> // Para funciones de fecha y hora del sistema (mktime, time)
#include "Fecha.h" // Para el manejo de fechas personalizadas
#include <string> // Para uso de la clase string
#include "medicionString.h" // Medicion de recursos
#include <cstdlib>  // Para funciones de conversion como stoi, stof

using namespace std;

/*
* Funcion para cargar los usuarios desde un archivo de texto.
* Cada linea del archivo representa un usuario codificado, que se interpreta usando el metodo cargarDesdeLinea.
* El arreglo de punteros a Usuario se redimensiona dinamicamente si es necesario.
* Retorna la cantidad de usuarios cargados. Si no se puede abrir el archivo, retorna 0 y pone el puntero en nullptr.
*/
int cargarUsuarios(const string& nombreArchivo, Usuario**& usuarios) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) { // Si no se puede abrir el archivo, se muestra un mensaje de error
        cerr << "Error, no se pudo abrir el archivo de usuarios: " << nombreArchivo << endl;
        usuarios = nullptr; // Se asigna nullptr para indicar que no hay usuarios cargados
        return 0; // Retorna 0 indicando que no se cargaron usuarios
    }

    int capacidad = 10; // Capacidad inicial del arreglo dinamico
    int cantidad = 0; // Contador de usuarios cargados
    usuarios = new Usuario*[capacidad]; // Se reserva memoria para el arreglo de punteros

    string linea;
    CONTAR_GETLINE();
    while (getline(archivo, linea)) { // Lee cada linea del archivo
        CONTAR_STRING_EQ();
        // Si se alcanza la capacidad, se redimensiona el arreglo
        if (cantidad == capacidad) {
            capacidad *= 2;
            Usuario** nuevo = new Usuario*[capacidad];
            for (int i = 0; i < cantidad; i++)
                nuevo[i] = usuarios[i]; // Copia de los punteros antiguos al nuevo arreglo
            delete[] usuarios;
            usuarios = nuevo;
        }
        // Se crea un nuevo usuario a partir de la linea leida
        usuarios[cantidad++] = Usuario::cargarDesdeLinea(linea);
    }

    archivo.close();
    return cantidad; // Se retorna la cantidad total de usuarios cargados
}

/*
* Funcion para cargar administradores desde un archivo de texto.
* Cada linea del archivo contiene la informacion de un administrador que se convierte en objeto usando cargarDesdeLinea().
* El arreglo de punteros a Administrador se redimensiona dinamicamente si se llena.
* Retorna la cantidad de administradores cargados. Si hay error al abrir el archivo, retorna 0 y deja el puntero en nullptr.
* Misma logica que para usuarios.
*/
int cargarAdministradores(const string& nombreArchivo, Administrador**& admins) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo de administradores: " << nombreArchivo << endl;
        admins = nullptr;
        return 0;
    }

    int capacidad = 10;
    int cantidad = 0;
    admins = new Administrador*[capacidad];

    string linea;
    CONTAR_GETLINE();
    while (getline(archivo, linea)) {
        CONTAR_STRING_EQ();
        if (cantidad == capacidad) {
            capacidad *= 2;
            Administrador** nuevo = new Administrador*[capacidad];
            for (int i = 0; i < cantidad; i++)
                nuevo[i] = admins[i];
            delete[] admins;
            admins = nuevo;
        }

        admins[cantidad++] = Administrador::cargarDesdeLinea(linea);
    }

    archivo.close();
    return cantidad;
}

/*
* Funcion para cargar alojamientos desde un archivo de texto.
* Cada linea del archivo contiene los datos de un alojamiento, que se convierte en objeto usando Alojamiento::cargarDesdeLinea().
* El arreglo de punteros a Alojamiento se redimensiona dinamicamente si se alcanza su capacidad.
* Retorna la cantidad de alojamientos cargados. Si ocurre un error al abrir el archivo, retorna 0 y el puntero queda en nullptr.
* Misma logica que para usuarios y administradores.
*/
int cargarAlojamientos(const string& nombreArchivo, Alojamiento**& alojamientos) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo de alojamientos: " << nombreArchivo << endl;
        alojamientos = nullptr;
        return 0;
    }

    int capacidad = 20;
    int cantidad = 0;
    alojamientos = new Alojamiento*[capacidad];

    string linea;
    CONTAR_GETLINE();
    while (getline(archivo, linea)) {
        CONTAR_STRING_EQ();
        if (cantidad == capacidad) {
            capacidad *= 2;
            Alojamiento** nuevo = new Alojamiento*[capacidad];
            for (int i = 0; i < cantidad; i++)
                nuevo[i] = alojamientos[i];
            delete[] alojamientos;
            alojamientos = nuevo;
        }

        alojamientos[cantidad++] = Alojamiento::cargarDesdeLinea(linea);
    }

    archivo.close();
    return cantidad;
}

/*
* Funcion que asocia cada alojamiento con su administrador correspondiente.
* Utiliza el documento del anfitrion (almacenado en cada alojamiento) para encontrar el administrador correspondiente
* y agrega dicho alojamiento a la lista de alojamientos del administrador.
* No se realiza medicion de recursos porque esta funcion se ejecuta una sola vez durante la carga.
*/
void asociarAlojamientos(Administrador** admins, int cantAdmins, Alojamiento** alojamientos, int cantAlojamientos) {
    for (int i = 0; i < cantAlojamientos; i++) {
        Alojamiento* a = alojamientos[i]; // Alojamiento actual
        string doc = a->getAnfitrionDoc(); // Documento del administrador (anfitrion) correspondiente

        for (int j = 0; j < cantAdmins; j++) { // Busca el administrador con el mismo documento
            CONTAR_STRING_EQ();
            // Si encuentra al administrador correspondiente, asocia el alojamiento
            if (admins[j]->getDocumento() == doc) {
                admins[j]->agregarAlojamiento(a);
                break;
            }
        }
    }
}

/*
* Funcion para cargar todas las reservas desde un archivo de texto.
* Cada linea del archivo representa una reserva, codificada con separador '|'.
* Se almacena dinamicamente cada objeto Reserva usando el metodo estatico cargarDesdeLinea().
* La funcion redimensiona el arreglo si se supera la capacidad inicial.
* Retorna la cantidad total de reservas cargadas, y actualiza el puntero doble pasado por referencia.
*/
int cargarReservas(const string& nombreArchivo, Reserva**& reservas) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo de reservas: " << nombreArchivo << endl;
        reservas = nullptr;
        return 0;
    }

    int capacidad = 20; // Capacidad inicial del arreglo de reservas
    int cantidad = 0;   // Contador de reservas cargadas
    reservas = new Reserva*[capacidad]; // Reserva memoria inicial para el arreglo

    string linea;
    CONTAR_GETLINE();
    // Lee cada linea del archivo hasta el final
    while (getline(archivo, linea)) {
        CONTAR_STRING_EQ();
        // Redimensiona el arreglo si se alcanza la capacidad
        if (cantidad == capacidad) {
            capacidad *= 2;
            Reserva** nuevo = new Reserva*[capacidad]; // Nuevo arreglo con mayor capacidad
            for (int i = 0; i < cantidad; i++)
                nuevo[i] = reservas[i];
            delete[] reservas; // Libera memoria del arreglo anterior
            reservas = nuevo; // Actualiza el puntero al nuevo arreglo
        }

        reservas[cantidad++] = Reserva::cargarDesdeLinea(linea); // Crea la nueva reserva y la almacena en el arreglo
    }

    archivo.close();
    return cantidad;
}

/*
* Funcion que asocia cada reserva a su respectivo usuario y alojamiento.
* La asociacion se realiza recorriendo todos los arreglos y buscando coincidencia por documento (usuario)
* y por codigo de alojamiento.
* Se actualiza cada objeto Usuario y Alojamiento con un puntero a la reserva correspondiente.
* La operacion se realiza en dos fases por reserva:
*   1. Asociar al usuario por su documento.
*   2. Asociar al alojamiento por su codigo.
*/
void asociarReservas(Reserva** reservas, int cantReservas, Usuario** usuarios, int cantUsuarios, Alojamiento** alojamientos, int cantAlojamientos) {
    for (int i = 0; i < cantReservas; i++) {
        Reserva* r = reservas[i]; // Reserva actual

        // Se asocia al usuario
        string doc = r->getDocCliente(); // Documento del cliente que hizo la reserva
        for (int j = 0; j < cantUsuarios; j++) {
            CONTAR_STRING_EQ();
            if (usuarios[j]->getDocumento() == doc) {
                usuarios[j]->agregarReserva(r); // Se agrega la reserva al usuario correspondiente
                break;
            }
        }

        // Se asocia al alojamiento
        string idAloj = r->getIdAlojamiento(); // Codigo del alojamiento reservado
        for (int j = 0; j < cantAlojamientos; j++) {
            CONTAR_STRING_EQ();
            if (alojamientos[j]->getCodigo() == idAloj) {
                alojamientos[j]->agregarReserva(r); // Se agrega la reserva al alojamiento correspondiente
                break;
            }

        }
    }
}

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
void guardarReservas(const string& ruta, Reserva** reservas, int numReservas) {
    ofstream archivo(ruta);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de reservas para escribir.\n";
        return;
    }

    for (int i = 0; i < numReservas; i++) {
        archivo << reservas[i]->aLinea() << endl; // Convierte la reserva a linea y la escribe
    }

    archivo.close();
}

/*
 *Funcion para distinguir mayusuclas y minusculas
 */
string aMinusculas(const string& s) {
    string resultado = s; // Copia de la cadena original para no modificar la entrada
    for (size_t i = 0; i < resultado.length(); i++) {
        resultado[i] = tolower(resultado[i]); // Función estándar de C++ para conversión de caracteres
    }
    return resultado;
}

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
bool fechaDentroDelRango(const Fecha& f) {
    Fecha fechaCorte = leerFechaCorte("fecha_corte.txt"); // Se lee la fecha de corte desde el archivo correspondiente
    Fecha maximo = fechaCorte.sumarNoches(365); // Se calcula la fecha maxima permitida (12 meses despues de la fecha de corte)

    cout << "Fecha ingresada: " << f.aCadena() << endl;
    cout << "Corte: " << fechaCorte.aCadena() << " | Max: " << maximo.aCadena() << endl;

    // Verificamos si la fecha f es mayor o igual a la fecha de corte
    bool esMayorOIgualCorte = Fecha::compararFecha(&f, &fechaCorte) >= 0;
    // Verificamos si la fecha f es menor o igual a la fecha maxima
    bool esMenorOIgualMax   = Fecha::compararFecha(&f, &maximo) <= 0;

    return esMayorOIgualCorte && esMenorOIgualMax; // La fecha es valida si cumple ambas condiciones
}

/*
* Funcion que convierte una fecha en formato numerico a una representacion extendida,
* incluyendo el nombre del dia de la semana y el mes por su nombre.
* Ejemplo: para una fecha 28/05/2025 retorna "Miercoles, 28 de Mayo del 2025".
* Parametros:
*  - f: objeto Fecha con dia, mes y anio.
* Retorna:
*  - Cadena con la fecha en formato extendido.
*/
string fechaExtendida(const Fecha& f) {
    tm estructura = {}; // Estructura tm para representar fecha y hora (inicializada en cero)
    // Se asignan los valores desde el objeto Fecha
    estructura.tm_mday = f.getDia();
    estructura.tm_mon = f.getMes() - 1;
    estructura.tm_year = f.getAnio() - 1900;

    // Se ajustan automaticamente los campos faltantes de la estructura tm, incluyendo tm_wday
    mktime(&estructura);  // Completa campos automáticos

    // Arreglos con nombres de los dias y meses para traducir a texto
    const char* dias[] = { "Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado" };
    const char* meses[] = { "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre" };

    // Se obtiene el nombre del dia de la semana a partir de tm_wday
    string resultado = dias[estructura.tm_wday];
    CONTAR_TOSTRING();
    CONTAR_CONCAT();

    // Se arma la primera parte: "Dia, <numero> de <Mes>"
    resultado += ", " + to_string(f.getDia()) + " de " + meses[estructura.tm_mon];
    CONTAR_TOSTRING();
    CONTAR_CONCAT();

    // Se agrega el anio: " del <año>"
    resultado += " del " + to_string(f.getAnio());
    return resultado;
}

/*
 * Funcion que lee la fecha de corte desde un archivo de texto.
 * Esta fecha se utiliza como referencia para validar si una reserva futura
 * se encuentra dentro del rango permitido (365 dias despues de la fecha de corte).
 * Si el archivo no existe o no puede abrirse, retorna por defecto la fecha 01/01/2000.
 */
Fecha leerFechaCorte(const string& ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        // Por si no existe el archivo, se puso una fecha por defecto -> 01/01/2000
        return Fecha(1, 1, 2000);
    }

    string linea;
    CONTAR_GETLINE();
    getline(archivo, linea); // Se lee la primera linea del archivo
    archivo.close();

    Fecha fecha;
    fecha.cargarDesdeCadena(linea); // Se convierte la cadena leida en objeto Fecha
    return fecha;
}

/*
 * Funcion que guarda la nueva fecha de corte en un archivo de texto.
 * Esta fecha marca el limite inferior del rango de fechas permitidas
 * para realizar nuevas reservas dentro del sistema.
 * Si el archivo no puede abrirse, se muestra un mensaje de error.
 * El contenido anterior del archivo es sobrescrito.
 */
void guardarFechaCorte(const string& ruta, const Fecha& fecha) {
    ofstream archivo(ruta);
    if (!archivo.is_open()) {
        cerr << "Error al guardar la fecha de corte.\n";
        return;
    }

    archivo << fecha.aCadena(); // Se escribe la fecha en formato cadena (ej. 12/05/2025)
    archivo.close();
}

/*
 * Funcion que obtiene el mayor numero de identificador de las reservas existentes,
 * considerando tanto las reservas actuales como las historicas.
 * Esto permite generar un nuevo ID unico para la proxima reserva.
 * Se asume que el formato del ID es "R<number>", por ejemplo "R104".
 */
int obtenerUltimoNumeroReserva(Reserva** actuales, int nActuales, Reserva** historicas, int nHistoricas) {
    int maxID = 0; // Variable para almacenar el mayor numero encontrado

    // Recorrido de las reservas actuales
    for (int i = 0; i < nActuales; ++i) {
        string id = actuales[i]->getID(); // Obtener ID de la reserva
        if (id.length() > 1 && id[0] == 'R') { // Verificar formato valido (empieza con 'R')
            int numero = stoi(id.substr(1)); // Se quita la R
            if (numero > maxID) maxID = numero; // Actualizar si es mayor que el actual
        }
    }
    // Recorrido de las reservas historicas, con misma logica anterior
    for (int i = 0; i < nHistoricas; ++i) {
        string id = historicas[i]->getID();
        if (id.length() > 1 && id[0] == 'R') {
            int numero = stoi(id.substr(1));
            if (numero > maxID) maxID = numero;
        }
    }

    return maxID; // Devolver el mayor numero encontrado
}

