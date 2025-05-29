#ifndef MEDICIONSTRING_H
#define MEDICIONSTRING_H

#include <string>
using namespace std;

// Declaracion de contadores globales para uso de funciones string
extern int contadorGetline;
extern int contadorComparacionesString;
extern int contadorAsignacionesString;
extern int contadorToString;
extern int contadorConcatenaciones;
extern int contadorCopiasString;

// Muestra los resultados por consola
void mostrarContadoresString(const string& nombre);

// Macros para incrementar los contadores
#define CONTAR_GETLINE() contadorGetline++
#define CONTAR_STRING_EQ() contadorComparacionesString++
#define CONTAR_STRING_ASSIGN() contadorAsignacionesString++
#define CONTAR_TOSTRING() contadorToString++
#define CONTAR_CONCAT() contadorConcatenaciones++
#define CONTAR_COPIA_STRING() contadorCopiasString++

// Mostrar los resultados y resetear
void mostrarContadoresString(const string& funcionalidad);
#endif
