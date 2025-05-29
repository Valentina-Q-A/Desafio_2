#include "Fecha.h" //Cabecera
#include <sstream> //Para usar stringstream (Conversion o procesamiento de strings)
#include <iomanip> // Permite manipular formatos de salida, por ejemplo en fechas con ceros a la izquierda
#include "medicionString.h" //Medicion de recursos
using namespace std;

/*
 * Constructor que inicializa una fecha con dia, mes y año especificados.
 */
Fecha::Fecha(short int d, short int m, short int a) {
    dia = d;
    mes = m;
    anio = a;
}

/*
 * Funcion que determina si un año es bisiesto o no.
 * Recibe un año (entero) y retorna un booleano: true si es bisiesto, false en caso contrario.
 * Un año es bisiesto si es divisible por 4 y no por 100, o si es divisible por 400.
 */
bool Fecha::esBisiesto(int anio) const {
    CONTAR_STRING_EQ();
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}

/*
 * Funcion que retorna una nueva fecha luego de sumar una cantidad dada de noches.
 * Parte de la fecha actual (this) y avanza dia a dia respetando la cantidad de dias de cada mes,
 * incluyendo la logica de años bisiestos.
 * Recibe un entero (noches) y retorna un objeto Fecha con la fecha resultante.
 */
Fecha Fecha::sumarNoches(int noches) const {
    Fecha nueva = *this; // Copiamos la fecha actual en un nuevo objeto para no modificar el original

    while (noches > 0) { // Mientras falten noches por agregar
        int diasMes;
        // Determinar cuantos dias tiene el mes actual
        if (nueva.mes == 4 || nueva.mes == 6 || nueva.mes == 9 || nueva.mes == 11) {
            diasMes = 30; // Abril, junio, septiembre, noviembre
        } else if (nueva.mes == 2) {
            diasMes = esBisiesto(nueva.anio) ? 29 : 28; // Febrero segun si el año es bisiesto o no
        } else {
            diasMes = 31; // Meses con 31 dias
        }

        // Cuantos dias faltan para terminar el mes actual
        int diasRestantesMes = diasMes - nueva.dia;

        if (noches <= diasRestantesMes) {
            // Se pueden sumar las noches sin pasar al siguiente mes
            nueva.dia += noches;
            noches = 0;
        } else {
            // Si no caben avanzar al primer dia del siguiente mes
            noches -= (diasRestantesMes + 1);
            nueva.dia = 1;
            nueva.mes++;

            // Si se pasa de diciembre, avanzar el año
            if (nueva.mes > 12) {
                nueva.mes = 1;
                nueva.anio++;
            }
        }
    }

    return nueva; // Retornar la nueva fecha con las noches sumadas
}

/*
 * Funcion estatica que compara dos fechas dadas por puntero.
 * Retorna:
 *   -1 si f1 es anterior a f2,
 *    1 si f1 es posterior a f2,
 *    0 si ambas fechas son iguales.
 * Se compara primero el año, luego el mes y finalmente el dia.
 */
int Fecha::compararFecha(const Fecha* f1, const Fecha* f2) {
    if (f1->anio < f2->anio) return -1; // Si el año de f1 es menor, f1 es anterior
    if (f1->anio > f2->anio) return 1; // Si el año de f1 es mayor, f1 es posterior
    if (f1->mes < f2->mes) return -1; // Si los año son iguales, comparar meses
    if (f1->mes > f2->mes) return 1;
    if (f1->dia < f2->dia) return -1; // Si meses iguales, comparar dias
    if (f1->dia > f2->dia) return 1;
    return 0; // Fechas exactamente iguales
}

/*
 * Metodo que retorna la fecha en formato de cadena "dd/mm/aaaa".
 * Usa ostringstream y manipuladores de formato para asegurar dos digitos en dia y mes.
 */
string Fecha::mostrarFechaFormato() const {
    ostringstream oss; // Flujo de salida para construir la cadena
    oss << setw(2) << setfill('0') << dia << "/" // Dia con 2 digitos, rellenado con '0' si es necesario
        << setw(2) << setfill('0') << mes << "/" // Mes con 2 digitos, relleno igual que el dia
        << anio; // Anio tal como esta (4 digitos)
    return oss.str();
}

/*
 * Metodo que carga una fecha desde una cadena con formato "dd/mm/aaaa".
 * Usa un stringstream para extraer los valores numericos separados por slashes.
 * Retorna true si la lectura fue exitosa, false si hubo error.
 */
bool Fecha::cargarDesdeCadena(const string& cadena) {
    stringstream ss(cadena); // Crear flujo de entrada desde la cadena recibida
    char slash; // Variable para capturar los caracteres '/' entre los numeros
    ss >> dia >> slash >> mes >> slash >> anio; // Extraer dia, slash, mes, slash, y año
    return !ss.fail(); // Retornar true si la lectura fue exitosa, false si fallo
}

/*
 * Metodo que convierte la fecha actual en una cadena de texto con formato "dd/mm/aaaa".
 * Internamente reutiliza la funcion mostrarFechaFormato().
 * Retorna un string representando la fecha.
 */
string Fecha::aCadena() const {
    return mostrarFechaFormato(); // Llama al metodo que formatea la fecha y la retorna como string
}

// Getters para obtener los atributos de fecha
int Fecha::getDia() const { return dia; }
int Fecha::getMes() const { return mes; }
int Fecha::getAnio() const { return anio; }

// Setters para modificar atributos
void Fecha::setDia(int d) { dia = d; }
void Fecha::setMes(short int m) { mes = m; }
void Fecha::setAnio(short int a) { anio = a; }

/*
 * Sobrecarga del operador de salida << para objetos de tipo Fecha.
 * Permite imprimir una Fecha directamente usando cout o cualquier ostream.
 * Internamente llama al metodo aCadena() para obtener la representacion en texto de la fecha.
 * Retorna la referencia al flujo de salida original para permitir encadenamiento.
 */
ostream& operator<<(ostream& os, const Fecha& f) {
    os << f.aCadena(); // Inserta la cadena de la fecha al flujo
    return os; // Retorna el flujo de salida
}

/*
 * Sobrecarga del operador de entrada >> para objetos de tipo Fecha.
 * Permite leer una Fecha directamente desde un flujo de entrada (ej. cin).
 * Internamente lee una cadena, luego utiliza el metodo cargarDesdeCadena() para convertirla en una Fecha.
 * Retorna la referencia al flujo de entrada original para permitir encadenamiento.
 */
istream& operator>>(istream& is, Fecha& f) {
    string s; // Variable para almacenar la cadena leida
    is >> s; // Leer la cadena desde el flujo
    f.cargarDesdeCadena(s); // Convertir la cadena en una Fecha usando el metodo correspondiente
    return is; // Retornar el flujo de entrada
}
