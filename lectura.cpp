#include "lectura.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>
#include "Administrador.h"
#include <ctime>

using namespace std;

int cargarUsuarios(const string& nombreArchivo, Usuario**& usuarios) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo de usuarios: " << nombreArchivo << endl;
        usuarios = nullptr;
        return 0;
    }

    int capacidad = 10;
    int cantidad = 0;
    usuarios = new Usuario*[capacidad];

    string linea;
    while (getline(archivo, linea)) {
        if (cantidad == capacidad) {
            capacidad *= 2;
            Usuario** nuevo = new Usuario*[capacidad];
            for (int i = 0; i < cantidad; i++)
                nuevo[i] = usuarios[i];
            delete[] usuarios;
            usuarios = nuevo;
        }

        usuarios[cantidad++] = Usuario::cargarDesdeLinea(linea);
    }

    archivo.close();
    return cantidad;
}

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
    while (getline(archivo, linea)) {
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
    while (getline(archivo, linea)) {
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

void asociarAlojamientos(Administrador** admins, int cantAdmins, Alojamiento** alojamientos, int cantAlojamientos) {
    for (int i = 0; i < cantAlojamientos; i++) {
        Alojamiento* a = alojamientos[i];
        string doc = a->getAnfitrionDoc();

        for (int j = 0; j < cantAdmins; j++) {
            if (admins[j]->getDocumento() == doc) {
                admins[j]->agregarAlojamiento(a);
                break;
            }
        }
    }
}

int cargarReservas(const string& nombreArchivo, Reserva**& reservas) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo de reservas: " << nombreArchivo << endl;
        reservas = nullptr;
        return 0;
    }

    int capacidad = 20;
    int cantidad = 0;
    reservas = new Reserva*[capacidad];

    string linea;
    while (getline(archivo, linea)) {
        if (cantidad == capacidad) {
            capacidad *= 2;
            Reserva** nuevo = new Reserva*[capacidad];
            for (int i = 0; i < cantidad; i++)
                nuevo[i] = reservas[i];
            delete[] reservas;
            reservas = nuevo;
        }

        reservas[cantidad++] = Reserva::cargarDesdeLinea(linea);
    }

    archivo.close();
    return cantidad;
}

void asociarReservas(Reserva** reservas, int cantReservas, Usuario** usuarios, int cantUsuarios, Alojamiento** alojamientos, int cantAlojamientos) {
    for (int i = 0; i < cantReservas; i++) {
        Reserva* r = reservas[i];

        // Asociar al usuario (huésped)
        string doc = r->getDocCliente();
        for (int j = 0; j < cantUsuarios; j++) {
            if (usuarios[j]->getDocumento() == doc) {
                usuarios[j]->agregarReserva(r);
                break;
            }
        }

        // Asociar al alojamiento
        string idAloj = r->getIdAlojamiento();
        for (int j = 0; j < cantAlojamientos; j++) {
            if (alojamientos[j]->getCodigo() == idAloj) {
                // Aquí lo asociamos también al alojamiento
                alojamientos[j]->agregarReserva(r);
                break;
            }

        }
    }
}

/*
 *Funcion para actualizar archivo de reservas cuando se haga una cancelación
 */

void guardarReservas(const string& ruta, Reserva** reservas, int numReservas) {
    ofstream archivo(ruta);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de reservas para escritura.\n";
        return;
    }

    for (int i = 0; i < numReservas; i++) {
        archivo << reservas[i]->aLinea() << endl;
    }

    archivo.close();
}

/*
 *Funcion para distinguir mayusuclas y minusculas#include <cctype>
 */
string aMinusculas(const string& s) {
    string resultado = s;
    for (size_t i = 0; i < resultado.length(); i++) {
        resultado[i] = tolower(resultado[i]);
    }
    return resultado;
}

bool fechaDentroDelRango(const Fecha& f) {
    time_t t = time(nullptr);
    tm* ahora = localtime(&t);

    // Fecha actual
    Fecha hoy(ahora->tm_mday, ahora->tm_mon + 1, ahora->tm_year + 1900);

    // Fecha máxima: hoy + 1 año
    Fecha maximo(hoy.getDia(), hoy.getMes(), hoy.getAnio() + 1);

    // Validar que f ∈ [hoy, maximo]
    // Es decir: hoy <= f <= maximo
    bool esMayorOIgualAHoy = !Fecha::compararFecha(&f, &hoy);       // f >= hoy
    bool esMenorOIgualMax = !Fecha::compararFecha(&maximo, &f);     // f <= maximo

    return esMayorOIgualAHoy && esMenorOIgualMax;
}

string fechaExtendida(const Fecha& f) {
    tm estructura = {};
    estructura.tm_mday = f.getDia();
    estructura.tm_mon = f.getMes() - 1;
    estructura.tm_year = f.getAnio() - 1900;

    mktime(&estructura);  // Completa campos automáticos

    const char* dias[] = { "Domingo", "Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado" };
    const char* meses[] = { "enero", "febrero", "marzo", "abril", "mayo", "junio",
                           "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre" };

    string resultado = dias[estructura.tm_wday];
    resultado += ", " + to_string(f.getDia()) + " de " + meses[estructura.tm_mon];
    resultado += " del " + to_string(f.getAnio());
    return resultado;
}


