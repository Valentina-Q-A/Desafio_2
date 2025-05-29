#include "Administrador.h" //Cabecera
#include <sstream> //Para usar stringstream (Conversion o procesamiento de strings)
#include "medicionString.h" //Medicion de recursos
using namespace std;

/*
* Constructor de la clase Administrador.
* Inicializa un objeto con documento, experiencia y estrellas.
* Ademas, reserva memoria para un arreglo de punteros a alojamientos con capacidad inicial para 5 elementos que se duplica segun sea necesario.
*/
Administrador::Administrador(string documento, short int exp, float estrellas):documento(documento), exp(exp), estrellas(estrellas), numAlojamientos(0), capacidad(5)
{
    alojamientos = new Alojamiento*[capacidad];// Reserva de memoria dinámica para almacenar hasta 5 punteros a alojamientos
}

/*
* Destructor de la clase Administrador.
* Libera la memoria reservada para el arreglo de punteros a alojamientos.
*/
Administrador::~Administrador() {
    delete[] alojamientos; // Liberación del arreglo de punteros (no de los objetos apuntados)
}


/*
* Metodo que muestra la informacion de todos los alojamientos asociados a un administrador.
* Recorre el arreglo dinámico de punteros a Alojamiento y llama a su método 'mostrar()' para imprimir detalles.
*/
void Administrador::mostrarAlojamientos() const {
    for (int i = 0; i < numAlojamientos; i++) // Recorrer todos los alojamientos registrados
        alojamientos[i]->mostrar(); // Llamar a mostrar de cada alojamiento
}


/*
* Metodos getters y setters de la clase Administrador.
* Permiten acceder y modificar los atributos privados: documento, experiencia, estrellas y numero de alojamientos.
*/
//Getters
string Administrador::getDocumento() const { return documento; } // Devuelve el documento del administrador
short int Administrador::getExp() const { return exp; } // Devuelve la experiencia (en años)
float Administrador::getEstrellas() const { return estrellas; } // Devuelve la puntuación promedio del administrador
short int Administrador::getNumAlojamientos() const { return numAlojamientos; } // Devuelve la cantidad de alojamientos registrados
//Setters
void Administrador::setDocumento(string d) { documento = d; } // Establece un nuevo valor para el documento
void Administrador::setExp(short int e) { exp = e; } // Establece un nuevo valor para la experiencia
void Administrador::setEstrellas(float est) { estrellas = est; } // Establece un nuevo valor para la puntuacion

/*
 * Metodo estatico que carga un objeto Administrador a partir de una linea de texto con formato: documento|experiencia|estrellas
 * Utiliza stringstream para separar los campos por el caracter '|'
 * Retorna un puntero al nuevo objeto Administrador creado dinamicamente
 */
Administrador* Administrador::cargarDesdeLinea(const string& linea) {
    stringstream ss(linea); // Crear un stream para leer la linea completa
    string doc, expStr, estStr; // Variables para guardar los campos extraidos
    CONTAR_GETLINE();// Contar el uso de getline
    getline(ss, doc, '|'); // Leer el documento hasta |
    CONTAR_GETLINE();
    getline(ss, expStr, '|'); // Leer la exp hasta |
    CONTAR_GETLINE();
    getline(ss, estStr, '|'); // Leer las estrellas hasta |

    return new Administrador(doc, stoi(expStr), stof(estStr));  // Crear y retornar un nuevo objeto Administrador con los valores convertidos a sus tipos respectivosx|
}

/*
 * Metodo que agrega un nuevo alojamiento al arreglo del administrador.
 * Si la cantidad de alojamientos alcanza la capacidad actual del arreglo, se redimensiona al doble.
 * Utiliza memoria dinamica para crear un nuevo arreglo de mayor tamaño, copia los elementos previos
 * y libera el arreglo antiguo antes de insertar el nuevo alojamiento.
 */
void Administrador::agregarAlojamiento(Alojamiento* a) {
    CONTAR_STRING_EQ();
    if (numAlojamientos == capacidad) { // Verificar si se ha alcanzado la capacidad maxima actual del arreglo
        capacidad *= 2; // Duplicar capacidad
        Alojamiento** nuevo = new Alojamiento*[capacidad]; // Crear un nuevo arreglo de punteros con la nueva capacidad
        for (int i = 0; i < numAlojamientos; i++)// Copiar los punteros existentes al nuevo arreglo
            nuevo[i] = alojamientos[i];
        delete[] alojamientos; // Liberar el arreglo antiguo (no los objetos apuntados)
        alojamientos = nuevo; // Asignar el nuevo arreglo redimensionado
    }
    alojamientos[numAlojamientos++] = a; // Agregar el nuevo alojamiento en la siguiente posicion disponible
}

/*
 * Metodo que retorna un puntero al alojamiento del administrador segun el indice proporcionado.
 * Si el indice esta fuera del rango valido (menor que 0 o mayor o igual al numero de alojamientos), retorna nullptr.
 */
Alojamiento* Administrador::getAlojamiento(int index) const {
    if (index >= 0 && index < numAlojamientos) { // Verifica si el indice esta dentro del rango valido
        return alojamientos[index]; // Retorna el puntero al alojamiento correspondiente
    }
    return nullptr; // Retorna nulo si el indice no es valido
}


