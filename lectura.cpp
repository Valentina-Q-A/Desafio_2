#include "lectura.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "Administrador.h"

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


