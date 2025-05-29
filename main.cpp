#include <iostream>
#include <string>
#include <cstdlib>
#include "Usuario.h"
#include "Administrador.h"
#include "Alojamiento.h"
#include "Fecha.h"
#include "Reserva.h"
#include "lectura.h"
#include "medicionString.h"
using namespace std;


// MEDICIÓN DE RECURSOS
unsigned long long iteracionesTotales = 0;
//unsigned long long memoriaTotal = 0;
long long memoriaDurante = 0;
long long memoriaFinal = 0;


// Macros para facilitar la contabilización
#define CONTAR_ITERACION() iteracionesTotales++
// Logica para calcular el valor absoluto manualmente
#define CONTAR_MEMORIA(bytes)                                  \
memoriaDurante += ((long long)(bytes) >= 0 ? (long long)(bytes) : -(long long)(bytes)); \
    memoriaFinal += (long long)(bytes);


// Funcion para imprimir y resetear a los contadores
void mostrarMedicion(const string& nombreFuncionalidad) {
    cout << "\nMedicion de recursos: " << nombreFuncionalidad << "\n";
    cout << "Iteraciones realizadas: " << iteracionesTotales << endl;
    cout << "Memoria total usada durante: " << memoriaDurante << " bytes\n";
    cout << "Memoria ocupada al finalizar: " << memoriaFinal << " bytes\n";
    iteracionesTotales = 0;
    memoriaDurante = 0;
    memoriaFinal = 0;
}

// Para descartar caracteres hasta el salto de línea
void limpiarBufferEntrada() {
    cin.clear();
    CONTAR_STRING_EQ();
    while (cin.get() != '\n');
}

Administrador* buscarAdministrador(Administrador** admins, int numAdmins, const string& doc) {
    for (int i = 0; i < numAdmins; i++) {
        CONTAR_ITERACION();
        CONTAR_STRING_EQ();
        if (admins[i]->getDocumento() == doc)
            return admins[i];
    }
    return nullptr;
}

Usuario* buscarUsuario(Usuario** usuarios, int numUsuarios, const string& doc) {
    for (int i = 0; i < numUsuarios; i++) {
        CONTAR_ITERACION();
        CONTAR_STRING_EQ();
        if (usuarios[i]->getDocumento() == doc)
            return usuarios[i];
    }
    return nullptr;
}

void guardarFechaCorte(const string&, const Fecha&);


/*
 * MENU PRINCIPAL:
 */

int main() {

    // Variables de sistema cargado
    Usuario** usuarios = nullptr;
    Administrador** admins = nullptr;
    Alojamiento** alojamientos = nullptr;
    Reserva** reservas = nullptr;

    int numUsuarios = cargarUsuarios("usuarios.txt", usuarios);
    int numAdmins = cargarAdministradores("administradores.txt", admins);
    int numAlojamientos = cargarAlojamientos("alojamientos.txt", alojamientos);
    int numReservas = cargarReservas("reservas.txt", reservas);

    mostrarMedicion("Carga inicial datos desde archivos");
    mostrarContadoresString("Cantidad strings en carga inicial");


    asociarAlojamientos(admins, numAdmins, alojamientos, numAlojamientos);
    asociarReservas(reservas, numReservas, usuarios, numUsuarios, alojamientos, numAlojamientos);
    int opcion = 0;

    do {
        cout << "\n----- MENU PRINCIPAL -----\n";
        cout << "1. Ingresar como administrador\n";
        cout << "2. Ingresar como usuario\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            limpiarBufferEntrada();
            cout << "La entrada es invalida, intente nuevamente\n";
            continue;
        }

        if (opcion == 1) {
            string docAdmin;
            cout << "Ingrese su documento de administrador: ";
            cin >> docAdmin;

            Administrador* admin = buscarAdministrador(admins, numAdmins, docAdmin);
            if (admin) {
                cout << "\nBienvenido, " << admin->getDocumento() << endl;

                int opAdmin = 0;
                do {
                    cout << "\n--- Menu Administrador ---\n";
                    cout << "1. Consultar reservas por rango de fechas\n";
                    cout << "2. Cancelar una reserva"<<endl;
                    cout << "3. Actualizar historico"<<endl;
                    cout << "4. Volver al menu principal\n";
                    cout << "Seleccione una opcion: ";
                    cin >> opAdmin;

                    if (cin.fail()) {
                        limpiarBufferEntrada();
                        cout << "La entrada es invalida, intente nuevamente\n";
                        continue;
                    }

                    else if (opAdmin == 1) {
                        cout << "\n--- CONSULTAR RESERVAS POR RANGO ---\n";

                        string desdeStr, hastaStr;
                        Fecha desde, hasta;

                        cout << "Ingrese fecha inicial (DD/MM/AAAA): ";
                        cin >> desdeStr;
                        cout << "Ingrese fecha final (DD/MM/AAAA): ";
                        cin >> hastaStr;

                        desde.cargarDesdeCadena(desdeStr);
                        hasta.cargarDesdeCadena(hastaStr);

                        CONTAR_MEMORIA(sizeof(Fecha) * 2); // desde y hasta

                        for (int i = 0; i < admin->getNumAlojamientos(); i++) {
                            CONTAR_ITERACION(); // Para cada alojamiento recorrido
                            Alojamiento* a = admin->getAlojamiento(i);
                            cout << "\nAlojamiento " << a->getCodigo() << " - Reservas en el rango:\n";
                            a->mostrarReservasPorRango(desde, hasta);
                        }

                        mostrarMedicion("Consultar reservas rango de fechas (administrador)");
                        mostrarContadoresString("Cantidad strings consultar por rango de fechas (administrador)");

                        limpiarBufferEntrada();
                    }


                    else if (opAdmin == 2) {
                        string cod;
                        cout << "Ingrese el código del alojamiento a consultar: ";
                        cin >> cod;

                        Alojamiento* a = nullptr;
                        for (int i = 0; i < admin->getNumAlojamientos(); i++) {
                            CONTAR_ITERACION();  // Comparación de códigos
                            CONTAR_STRING_EQ();
                            if (admin->getAlojamiento(i)->getCodigo() == cod) {
                                a = admin->getAlojamiento(i);
                                break;
                            }
                        }
                        CONTAR_STRING_EQ();
                        if (a == nullptr) {
                            cout << "El alojamiento no pertenece a este administrador\n";
                            mostrarMedicion("Cancelar reserva (administrador)");
                            mostrarContadoresString("Cantidad strings cancelar reserva (administrador)");

                            continue;
                        }

                        // Mostrar TODAS las reservas del alojamiento
                        bool hayReservas = false;
                        cout << "\nReservas activas:\n";
                        for (int i = 0; i < numReservas; i++) {
                            CONTAR_ITERACION();
                            CONTAR_STRING_EQ();
                            if (reservas[i]->getIdAlojamiento() == cod) {
                                reservas[i]->mostrarResumen();
                                CONTAR_MEMORIA(sizeof(Reserva));
                                hayReservas = true;
                            }
                        }

                        if (!hayReservas) {
                            cout << "Este alojamiento no tiene reservas activas\n";
                            mostrarMedicion("Cancelar reserva (administrador)");
                            mostrarContadoresString("Cantidad strings cancelar reserva (administrador)");

                            continue;
                        }

                        cout << "Ingrese el ID de la reserva para cancelar: ";
                        string id;
                        cin >> id;

                        Reserva* reservaABorrar = nullptr;
                        for (int i = 0; i < numReservas; i++) {
                            CONTAR_ITERACION();
                            CONTAR_STRING_EQ();
                            if (reservas[i]->getId() == id) {
                                reservaABorrar = reservas[i];

                                for (int j = i; j < numReservas - 1; j++) {
                                    reservas[j] = reservas[j + 1];
                                    CONTAR_ITERACION();
                                }
                                numReservas--;
                                break;
                            }
                        }
                        CONTAR_STRING_EQ();
                        if (reservaABorrar != nullptr) {
                            a->eliminarReserva(id);

                            for (int i = 0; i < numUsuarios; i++) {
                                CONTAR_ITERACION();
                                CONTAR_STRING_EQ();
                                if (usuarios[i]->getDocumento() == reservaABorrar->getDocCliente()) {
                                    usuarios[i]->eliminarReserva(id);
                                    break;
                                }
                            }

                            delete reservaABorrar;
                            CONTAR_MEMORIA(-sizeof(Reserva));
                            guardarReservas("reservas.txt", reservas, numReservas);

                            cout << "La reserva fue cancelada exitosamente\n";
                        } else {
                            cout << "La reserva no fue encontrada\n";
                        }

                        mostrarMedicion("Cancelar reserva (administrador)");
                        mostrarContadoresString("Cantidad strings cancelar reserva (administrador)");

                    }



                    else if (opAdmin == 3) {
                        cout << "\n--- ACTUALIZAR HISTORICO ---\n";

                        // Leer la ultima fecha de corte
                        Fecha ultimaCorte = leerFechaCorte("fecha_corte.txt");
                        cout << "Ultima fecha de corte registrada: " << ultimaCorte.aCadena() << endl;

                        cout << "Ingrese la nueva fecha de corte (DD/MM/AAAA): ";
                        string corteStr;
                        cin >> corteStr;

                        Fecha nuevaCorte;
                        nuevaCorte.cargarDesdeCadena(corteStr);

                        if (Fecha::compararFecha(&nuevaCorte, &ultimaCorte) < 0) {
                            cout << "La nueva fecha no puede ser anterior a la última fecha de corte registrada\n";
                            mostrarMedicion("Actualizar histórico");
                            mostrarContadoresString("Cantidad strings actualizar histórico)");

                            continue;
                        }

                        int nuevasHistoricas = 0;
                        Reserva** nuevasHistoricasArr = new Reserva*[numReservas];
                        CONTAR_MEMORIA(sizeof(Reserva*) * numReservas);

                        for (int i = 0; i < numReservas; ++i) {
                            CONTAR_ITERACION();
                            Fecha fechaInicio = reservas[i]->getFechaInicio();
                            Fecha fechaSalida = fechaInicio;
                            fechaSalida.sumarNoches(reservas[i]->getNoches());

                            if (Fecha::compararFecha(&fechaSalida, &nuevaCorte) < 0) {
                                nuevasHistoricasArr[nuevasHistoricas++] = reservas[i];
                                CONTAR_MEMORIA(sizeof(Reserva));
                            }
                        }

                        // Reubicar reservas restantes, no historicas
                        int nuevasActivas = 0;
                        Reserva** nuevasActivasArr = new Reserva*[numReservas - nuevasHistoricas];
                        CONTAR_MEMORIA(sizeof(Reserva*) * (numReservas - nuevasHistoricas));

                        for (int i = 0; i < numReservas; ++i) {
                            CONTAR_ITERACION();
                            bool esHistorica = false;
                            for (int j = 0; j < nuevasHistoricas; ++j) {
                                CONTAR_STRING_EQ();
                                if (reservas[i] == nuevasHistoricasArr[j]) {
                                    esHistorica = true;
                                    break;
                                }
                            }
                            if (!esHistorica) {
                                nuevasActivasArr[nuevasActivas++] = reservas[i];
                            }
                        }

                        // Sobrescribe el archivo reservas.txt y actualiza el arreglo global
                        guardarReservas("reservas.txt", nuevasActivasArr, nuevasActivas);

                        // Cargar reservas existentes del histórico
                        Reserva** historicas = nullptr;
                        int numHistoricas = cargarReservas("historico.txt", historicas);
                        CONTAR_MEMORIA(sizeof(Reserva*) * numHistoricas);

                        // Se unen ambos arreglos
                        Reserva** totalHistoricas = new Reserva*[numHistoricas + nuevasHistoricas];
                        CONTAR_MEMORIA(sizeof(Reserva*) * (numHistoricas + nuevasHistoricas));

                        for (int i = 0; i < numHistoricas; ++i) {
                            CONTAR_ITERACION();
                            totalHistoricas[i] = historicas[i];
                        }
                        for (int i = 0; i < nuevasHistoricas; ++i) {
                            CONTAR_ITERACION();
                            totalHistoricas[numHistoricas + i] = nuevasHistoricasArr[i];
                        }

                        guardarReservas("historico.txt", totalHistoricas, numHistoricas + nuevasHistoricas);
                        guardarFechaCorte("fecha_corte.txt", nuevaCorte);

                        // Actualiza variables globales
                        delete[] reservas;
                        reservas = nuevasActivasArr;
                        numReservas = nuevasActivas;

                        delete[] historicas;
                        delete[] nuevasHistoricasArr;
                        delete[] totalHistoricas;

                        cout << "Historico actualizado exitosamente - Reservas movidas: " << nuevasHistoricas << endl;
                        mostrarMedicion("Actualizar historico");
                        mostrarContadoresString("Cantidad strings actualizar historico)");
                    }

                } while (opAdmin != 4);
            } else {
                cout << "El administrador no fue encontrado\n";
            }
            mostrarMedicion("Ingreso administrador");

            mostrarContadoresString("Cantidad strings Ingreso administrador");
        }

        else if (opcion == 2) {
            string docUsuario;
            cout << "Ingrese su documento de usuario: ";
            cin >> docUsuario;

            Usuario* usuario = buscarUsuario(usuarios, numUsuarios, docUsuario);
            if (usuario) {
                cout << "\nBienvenido, " << usuario->getDocumento() << endl;

                int opUsuario = 0;
                do {
                    cout << "\n--- Menu Usuario ---\n";
                    cout << "1. Consultar mis reservas\n";
                    cout << "2. Cancelar una reserva\n";
                    cout << "3. Hacer una nueva reserva\n";
                    cout << "4. Volver al menu principal\n";
                    cout << "Seleccione una opcion: ";
                    cin >> opUsuario;

                    if (cin.fail()) {
                        limpiarBufferEntrada();
                        cout << "Entrada invalida, intente nuevamente\n";
                        continue;
                    }

                    if (opUsuario == 1) {
                        cout << "\nReservas activas de " << usuario->getDocumento() << " \n";

                        usuario->mostrarReservas();

                        mostrarMedicion("Consultar reservas usuario");
                        mostrarContadoresString("Cantidad de strings consultar reservas usuario");

                        limpiarBufferEntrada();
                    }

                    else if (opUsuario == 2) {
                        cout << "\n-- Cancelacion de reserva ---\n";

                        // Mostrar reservas activas con conteo de recursos
                        usuario->mostrarReservas();

                        cout << "Ingrese el ID de la reserva que va a cancelar: ";
                        string idCancelar;
                        cin >> idCancelar;

                        // Paso 1: Buscar la reserva en el arreglo global
                        Reserva* reservaABorrar = nullptr;
                        for (int i = 0; i < numReservas; i++) {
                            CONTAR_ITERACION();
                            CONTAR_STRING_EQ();
                            if (reservas[i]->getId() == idCancelar) {
                                reservaABorrar = reservas[i];
                                for (int j = i; j < numReservas - 1; j++) {
                                    reservas[j] = reservas[j + 1];
                                    CONTAR_ITERACION();  // Desplazamiento de elementos
                                }
                                numReservas--;
                                break;
                            }
                        }

                        // Elimina de alojamiento y usuario
                        bool fueEliminada = false;
                        CONTAR_STRING_EQ();
                        if (reservaABorrar != nullptr) {
                            for (int i = 0; i < numAlojamientos; i++) {
                                CONTAR_ITERACION();  // Iteracion por alojamientos
                                alojamientos[i]->eliminarReserva(idCancelar);
                            }

                            fueEliminada = usuario->eliminarReserva(idCancelar);

                            delete reservaABorrar;
                            CONTAR_MEMORIA(-sizeof(Reserva));  // Liberar memoria de reserva

                            guardarReservas("reservas.txt", reservas, numReservas);

                            if (fueEliminada) {
                                cout << "Reserva fue cancelada exitosamente\n";
                            } else {
                                cout << "Error, se encontro en el arreglo global pero no en el usuario\n";
                            }
                        } else {
                            cout << "No se encontro ninguna reserva con ese ID\n";
                        }

                        // Mostrar medición de recursos
                        mostrarMedicion("Cancelar reserva (usuario)");
                        mostrarContadoresString("Cantidad strings cancelar reserva(usuario)");

                        limpiarBufferEntrada();
                    }

                    else if (opUsuario == 3) {
                        cout << "\n--- NUEVA RESERVA ---\n";
                        cout << "Seleccione el tipo de busqueda:\n";
                        cout << "1. Buscar por filtros (municipio, precio, puntuacion)\n";
                        cout << "2. Buscar directamente por codigo\n";
                        cout << "Opcion: ";
                        int tipoBusqueda;
                        cin >> tipoBusqueda;
                        CONTAR_ITERACION(); // lectura de opcion

                        if (tipoBusqueda != 1 && tipoBusqueda != 2) {
                            cout << "Opcion invalida\n";
                            limpiarBufferEntrada();
                            continue;
                        }

                        Alojamiento* seleccion = nullptr;
                        Fecha fechaInicio;
                        int noches;
                        string municipio;
                        double precioMax = 999999999;
                        float puntuacionMin = 0.0;

                        if (tipoBusqueda == 1) {
                            cout << "Municipio deseado: ";
                            cin.ignore();
                            CONTAR_GETLINE();
                            getline(cin, municipio);
                            string fechaStr;
                            cout << "Fecha de inicio (DD/MM/AAAA): ";
                            cin >> fechaStr;
                            fechaInicio.cargarDesdeCadena(fechaStr);
                            CONTAR_ITERACION();

                            if (!fechaDentroDelRango(fechaInicio)) {
                                cout << "La fecha ingresada debe estar entre hoy y los proximos 12 meses" << endl;
                                limpiarBufferEntrada();
                                continue;
                            }

                            cout << "Cantidad de noches: ";
                            cin >> noches;
                            CONTAR_ITERACION();

                            cout << "Precio maximo por noche (0 para ignorar): ";
                            cin >> precioMax;
                            if (precioMax == 0) precioMax = 999999999;

                            cout << "Puntuacion minima del anfitrion (0 a 5.0, 0 para ignorar): ";
                            cin >> puntuacionMin;

                            bool hayCoincidencias = false;
                            cout << "\nAlojamientos disponibles con los filtros:\n";
                            for (int i = 0; i < numAlojamientos; i++) {
                                CONTAR_ITERACION();
                                Alojamiento* a = alojamientos[i];
                                CONTAR_STRING_EQ();
                                if (aMinusculas(a->getMunicipio()) == aMinusculas(municipio) &&
                                    a->getPrecio() <= precioMax &&
                                    a->estaDisponible(fechaInicio, noches)) {

                                    Administrador* anfitrion = buscarAdministrador(admins, numAdmins, a->getAnfitrionDoc());
                                    CONTAR_ITERACION(); // de buscarAdministrador
                                    CONTAR_STRING_EQ();
                                    if (anfitrion != nullptr && anfitrion->getEstrellas() >= puntuacionMin) {
                                        cout << "\nCodigo: " << a->getCodigo()
                                        << "\nNombre: "; a->mostrar();
                                        cout << "Precio por noche: COP$" << a->getPrecio()
                                             << "\nPuntuacion del anfitrion: " << anfitrion->getEstrellas() << endl;
                                        hayCoincidencias = true;
                                    }
                                }
                            }

                            if (!hayCoincidencias) {
                                cout << "\nNo se encontraron alojamientos con los filtros seleccionados\n" << endl;
                                limpiarBufferEntrada();
                                continue;
                            }
                        } else if (tipoBusqueda == 2) {
                            cout << "Ingrese el codigo del alojamiento: ";
                            string codSeleccionado;
                            cin >> codSeleccionado;

                            for (int i = 0; i < numAlojamientos; i++) {
                                CONTAR_ITERACION();
                                CONTAR_STRING_EQ();
                                if (alojamientos[i]->getCodigo() == codSeleccionado) {
                                    seleccion = alojamientos[i];
                                    break;
                                }
                            }
                            CONTAR_STRING_EQ();
                            if (seleccion == nullptr) {
                                cout << "No se encontro un alojamiento con ese codigo\n";

                                continue;
                            }

                            cout << "Fecha de inicio (DD/MM/AAAA): ";
                            string fechaStr;
                            cin >> fechaStr;
                            fechaInicio.cargarDesdeCadena(fechaStr);
                            CONTAR_ITERACION();

                            if (!fechaDentroDelRango(fechaInicio)) {
                                cout << "La fecha ingresada debe estar entre hoy y los proximos 12 meses\n";
                                limpiarBufferEntrada();
                                continue;
                            }

                            cout << "Cantidad de noches: ";
                            cin >> noches;
                            CONTAR_ITERACION();

                            if (!seleccion->estaDisponible(fechaInicio, noches)) {
                                cout << "El alojamiento no esta disponible en ese rango\n";
                                continue;
                            }

                            if (!usuario->fechaDisponible(fechaInicio, noches)) {
                                cout << "Usted ya tiene una reserva activa en esas fechas\n";
                                continue;
                            }
                        }

                        cout << "\nConfirme el codigo del alojamiento que desea reservar: ";
                        string codSeleccionado;
                        cin >> codSeleccionado;

                        seleccion = nullptr;
                        for (int i = 0; i < numAlojamientos; i++) {
                            CONTAR_ITERACION();
                            CONTAR_STRING_EQ();
                            if (alojamientos[i]->getCodigo() == codSeleccionado) {
                                seleccion = alojamientos[i];
                                break;
                            }
                        }
                        CONTAR_STRING_EQ();
                        if (seleccion == nullptr) {
                            cout << "Codigo invalido.\n";
                            continue;
                        }

                        if (!usuario->fechaDisponible(fechaInicio, noches)) {
                            cout << "Usted ya tiene una reserva activa en esas fechas\n";
                            continue;
                        }

                        string metodoPago, comentario;
                        double valor = seleccion->getPrecio() * noches;
                        Fecha fechaPago = fechaInicio;

                        cout << "Metodo de pago (PSE/Tarjeta): ";
                        cin >> metodoPago;
                        metodoPago = aMinusculas(metodoPago);
                        CONTAR_STRING_EQ();

                        if (metodoPago != "pse" && metodoPago != "tarjeta") {
                            cout << "Metodo de pago invalido\n";
                            continue;
                        }

                        cout << "Comentarios: ";
                        cin.ignore();
                        CONTAR_GETLINE();
                        getline(cin, comentario);

                        // Declaraciones
                        int nuevoNumero = 0;
                        string idReserva = "";

                        // Cargar reservas históricas para calcular ID de reserva
                        Reserva** historicas = new Reserva*[1000]; // capacidad provisional
                        int numHistoricas = cargarReservas("historico.txt", historicas);

                        // Calcular el nuevo numero de reserva unico
                        CONTAR_CONCAT();
                        CONTAR_STRING_ASSIGN();
                        nuevoNumero = obtenerUltimoNumeroReserva(reservas, numReservas, historicas, numHistoricas) + 1;
                        idReserva = "R" + to_string(nuevoNumero);

                        // Liberar memoria de reservas historicas
                        for (int i = 0; i < numHistoricas; i++) {
                            delete historicas[i];
                        }
                        delete[] historicas;

                        Reserva* nueva = new Reserva(idReserva, fechaInicio, noches,
                                                     seleccion->getCodigo(), usuario->getDocumento(),
                                                     metodoPago, fechaPago, valor, comentario);
                        CONTAR_MEMORIA(sizeof(Reserva)); //  Medición de memoria dinamica

                        usuario->agregarReserva(nueva);
                        seleccion->agregarReserva(nueva);
                        reservas[numReservas++] = nueva;

                        guardarReservas("reservas.txt", reservas, numReservas);

                        cout << "\n--- COMPROBANTE DE RESERVA ---\n";
                        cout << "ID: " << idReserva << endl;
                        cout << "Usuario: " << usuario->getDocumento() << endl;
                        cout << "Alojamiento: " << seleccion->getCodigo() << endl;
                        cout << "Fecha de inicio: " << fechaExtendida(fechaInicio) << endl;
                        cout << "Fecha de salida: " << fechaExtendida(fechaInicio.sumarNoches(noches)) << endl;
                        cout << "Total: COP$" << valor << endl;

                        mostrarMedicion("Hacer reserva (usuario)");
                        mostrarContadoresString("Cantidad strings hacer reserva (usuario)");

                        limpiarBufferEntrada();
                    }

                } while (opUsuario != 4);

            } else {
                cout << "Usuario no encontrado\n";
            }
            mostrarMedicion("Ingreso como usuario");
            mostrarContadoresString("Cantidad strings Ingreso usuario");


        }

    } while (opcion != 3);

    cout << "\nGracias por reservar con UdeAStay, vuelva pronto\n";
    return 0;
}


