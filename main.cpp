#include <iostream>
#include <string>
#include "Usuario.h"
#include "Administrador.h"
#include "Alojamiento.h"
#include "Fecha.h"
#include "Reserva.h"
#include "lectura.h"
using namespace std;

void limpiarBufferEntrada() {
    cin.clear();
    while (cin.get() != '\n'); // Descarta caracteres hasta el salto de línea
}

Administrador* buscarAdministrador(Administrador** admins, int numAdmins, const string& doc) {
    for (int i = 0; i < numAdmins; i++) {
        if (admins[i]->getDocumento() == doc)
            return admins[i];
    }
    return nullptr;
}

Usuario* buscarUsuario(Usuario** usuarios, int numUsuarios, const string& doc) {
    for (int i = 0; i < numUsuarios; i++) {
        if (usuarios[i]->getDocumento() == doc)
            return usuarios[i];
    }
    return nullptr;
}


int main() {
    /*PRUEBAS DE FUNCIONAMIENTO:

    Alojamiento** alojamientos = nullptr;
    int numAlojamientos = cargarAlojamientos("alojamientos.txt", alojamientos);

    cout << "Alojamientos cargados: " << numAlojamientos << endl;

    for (int i = 0; i < numAlojamientos; i++) {
        alojamientos[i]->mostrar();  // Debe mostrar nombre y precio
    }

    // Liberar memoria
    for (int i = 0; i < numAlojamientos; i++)
        delete alojamientos[i];
    delete[] alojamientos;
    */

    /*
    Administrador** admins = nullptr;
    Alojamiento** alojamientos = nullptr;

    int cantAdmins = cargarAdministradores("administradores.txt", admins);
    int cantAlojamientos = cargarAlojamientos("alojamientos.txt", alojamientos);

    asociarAlojamientos(admins, cantAdmins, alojamientos, cantAlojamientos);

    for (int i = 0; i < cantAdmins; i++) {
        cout << "\nAdministrador " << admins[i]->getDocumento() << " tiene estos alojamientos:\n";
        for (int j = 0; j < admins[i]->getNumAlojamientos(); j++) {
            Alojamiento* a = admins[i]->getAlojamiento(j);
            if (a != nullptr)
                a->mostrar();
        }
    }

    // Liberar memoria
    for (int i = 0; i < cantAdmins; i++)
        delete admins[i];
    delete[] admins;

    for (int i = 0; i < cantAlojamientos; i++)
        delete alojamientos[i];
    delete[] alojamientos;
    */

    /*
    Usuario** usuarios = nullptr;
    Administrador** admins = nullptr;
    Alojamiento** alojamientos = nullptr;
    Reserva** reservas = nullptr;

    int numUsuarios = cargarUsuarios("usuarios.txt", usuarios);
    int numAdmins = cargarAdministradores("administradores.txt", admins);
    int numAlojamientos = cargarAlojamientos("alojamientos.txt", alojamientos);
    int numReservas = cargarReservas("reservas.txt", reservas);

    asociarAlojamientos(admins, numAdmins, alojamientos, numAlojamientos);
    asociarReservas(reservas, numReservas, usuarios, numUsuarios, alojamientos, numAlojamientos);

    // Mostrar reservas asociadas a cada usuario
    for (int i = 0; i < numUsuarios; i++) {
        cout << "\nUsuario " << usuarios[i]->getDocumento() << " tiene estas reservas:\n";
        usuarios[i]->mostrarReservas();
    }

    cout << "\n======= RESERVAS POR ALOJAMIENTO =======\n";
    for (int i = 0; i < numAlojamientos; i++) {
        Alojamiento* a = alojamientos[i];
        cout << "Alojamiento: " << a->getCodigo() << " (" << a->getMunicipio() << ")\n";
        for (int j = 0; j < a->getCantReservas(); j++) {
            a->getReserva(j)->mostrarResumen();
        }
        cout << endl;
    }

    Fecha desde, hasta;
    desde.cargarDesdeCadena("15/06/2025");
    hasta.cargarDesdeCadena("15/07/2025");

    cout << "\n======= CONSULTA DE RESERVAS EN RANGO =======\n";
    for (int i = 0; i < numAlojamientos; i++) {
        Alojamiento* a = alojamientos[i];
        cout << "Alojamiento: " << a->getCodigo() << " - Reservas entre 15/06/2025 y 15/07/2025:\n";
        a->mostrarReservasPorRango(desde, hasta);
        cout << endl;
    }
    */

    /*
     * MENU PRINCIPAL:
     */

    // Variables de sistema cargado
    Usuario** usuarios = nullptr;
    Administrador** admins = nullptr;
    Alojamiento** alojamientos = nullptr;
    Reserva** reservas = nullptr;

    int numUsuarios = cargarUsuarios("usuarios.txt", usuarios);
    int numAdmins = cargarAdministradores("administradores.txt", admins);
    int numAlojamientos = cargarAlojamientos("alojamientos.txt", alojamientos);
    int numReservas = cargarReservas("reservas.txt", reservas);

    asociarAlojamientos(admins, numAdmins, alojamientos, numAlojamientos);
    asociarReservas(reservas, numReservas, usuarios, numUsuarios, alojamientos, numAlojamientos);
    int opcion = 0;

    do {
        cout << "\n========== MENU PRINCIPAL ==========\n";
        cout << "1. Ingresar como administrador\n";
        cout << "2. Ingresar como usuario\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            limpiarBufferEntrada();
            cout << "Entrada inválida. Intente nuevamente.\n";
            continue;
        }

        if (opcion == 1) {
            string docAdmin;
            cout << "Ingrese su documento de administrador: ";
            cin >> docAdmin;

            Administrador* admin = buscarAdministrador(admins, numAdmins, docAdmin);
            if (admin) {
                cout << "\nBienvenido, administrador " << admin->getDocumento() << endl;

                int opAdmin = 0;
                do {
                    cout << "\n--- Menu Administrador ---\n";
                    cout << "1. Consultar reservas por rango de fechas\n";
                    cout << "2. Volver al menú principal\n";
                    cout << "Seleccione una opción: ";
                    cin >> opAdmin;

                    if (cin.fail()) {
                        limpiarBufferEntrada();
                        cout << "Entrada inválida. Intente nuevamente.\n";
                        continue;
                    }

                    if (opAdmin == 1) {
                        string desdeStr, hastaStr;
                        Fecha desde, hasta;

                        cout << "Ingrese fecha inicial (DD/MM/AAAA): ";
                        cin >> desdeStr;
                        cout << "Ingrese fecha final (DD/MM/AAAA): ";
                        cin >> hastaStr;

                        desde.cargarDesdeCadena(desdeStr);
                        hasta.cargarDesdeCadena(hastaStr);

                        for (int i = 0; i < admin->getNumAlojamientos(); i++) {
                            Alojamiento* a = admin->getAlojamiento(i);
                            cout << "\nAlojamiento " << a->getCodigo() << " - Reservas en el rango:\n";
                            a->mostrarReservasPorRango(desde, hasta);
                        }
                    }

                } while (opAdmin != 2);

            } else {
                cout << "Administrador no encontrado.\n";
            }

        } else if (opcion == 2) {
            string docUsuario;
            cout << "Ingrese su documento de usuario: ";
            cin >> docUsuario;

            Usuario* usuario = buscarUsuario(usuarios, numUsuarios, docUsuario);
            if (usuario) {
                cout << "\nBienvenido, usuario " << usuario->getDocumento() << endl;

                int opUsuario = 0;
                do {
                    cout << "\n--- Menú Usuario ---\n";
                    cout << "1. Consultar mis reservas\n";
                    cout << "2. Volver al menú principal\n";
                    cout << "Seleccione una opción: ";
                    cin >> opUsuario;

                    if (cin.fail()) {
                        limpiarBufferEntrada();
                        cout << "Entrada inválida. Intente nuevamente.\n";
                        continue;
                    }

                    if (opUsuario == 1) {
                        cout << "\n=== Reservas activas de " << usuario->getDocumento() << " ===\n";
                        usuario->mostrarReservas();
                    }

                } while (opUsuario != 2);

            } else {
                cout << "Usuario no encontrado.\n";
            }
        }

    } while (opcion != 3);

    cout << "\nGracias por usar el sistema. Hasta pronto.\n";

    return 0;
}

