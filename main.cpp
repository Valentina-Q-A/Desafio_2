#include "lectura.h"
#include <iostream>
using namespace std;

int main() {
    /*
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

    return 0;
}
