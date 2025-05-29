#include "medicionString.h"
#include <iostream>
using namespace std;

// Definición de los contadores
int contadorGetline = 0;
int contadorComparacionesString = 0;
int contadorAsignacionesString = 0;
int contadorToString = 0;
int contadorConcatenaciones = 0;
int contadorCopiasString = 0;

/*
 * Funcion que muestra por consola los contadores de uso de funciones string.
 * Se utiliza al final de cada funcionalidad para evaluar el consumo de recursos
 * asociados a operaciones con cadenas de caracteres.
 */
void mostrarContadoresString(const string& nombreFuncionalidad) {
    cout << "\nMedicion String: " << nombreFuncionalidad << "\n";
    cout << "Getline usados: " << contadorGetline << endl;
    cout << "Comparaciones: " << contadorComparacionesString << endl;
    cout << "Asignaciones: " << contadorAsignacionesString << endl;
    cout << "to_string usados: " << contadorToString << endl;
    cout << "Concatenaciones: " << contadorConcatenaciones << endl;
    cout << "Copias: " << contadorCopiasString << endl;
    cout << "----------";
}
