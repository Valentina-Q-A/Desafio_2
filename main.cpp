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
            cout << "Entrada invalida. Intente nuevamente.\n";
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
                    cout << "2. Cancelar una reserva"<<endl;
                    cout << "3. Actualizar historico"<<endl;
                    cout << "4. Volver al menu principal\n";
                    cout << "Seleccione una opcion: ";
                    cin >> opAdmin;

                    if (cin.fail()) {
                        limpiarBufferEntrada();
                        cout << "Entrada invalida. Intente nuevamente.\n";
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


                    else if (opAdmin == 2) {
                        string cod;
                        cout << "Ingrese el código del alojamiento a consultar: ";
                        cin >> cod;

                        Alojamiento* a = nullptr;
                        for (int i = 0; i < admin->getNumAlojamientos(); i++) {
                            if (admin->getAlojamiento(i)->getCodigo() == cod) {
                                a = admin->getAlojamiento(i);
                                break;
                            }
                        }

                        if (a == nullptr) {
                            cout << "El alojamiento no pertenece a este administrador.\n";
                            continue;
                        }

                        string desdeStr, hastaStr;
                        Fecha desde, hasta;
                        cout << "Fecha inicial (DD/MM/AAAA): ";
                        cin >> desdeStr;
                        cout << "Fecha final (DD/MM/AAAA): ";
                        cin >> hastaStr;

                        desde.cargarDesdeCadena(desdeStr);
                        hasta.cargarDesdeCadena(hastaStr);

                        cout << "\nReservas activas:\n";
                        a->mostrarReservasPorRango(desde, hasta);

                        cout << "Ingrese el ID de la reserva a cancelar: ";
                        string id;
                        cin >> id;

                        Reserva* reservaABorrar = nullptr;
                        for (int i = 0; i < numReservas; i++) {
                            if (reservas[i]->getId() == id) {
                                reservaABorrar = reservas[i];
                                for (int j = i; j < numReservas - 1; j++) {
                                    reservas[j] = reservas[j + 1];
                                }
                                numReservas--;
                                break;
                            }
                        }

                        if (reservaABorrar != nullptr) {
                            a->eliminarReserva(id);

                            for (int i = 0; i < numUsuarios; i++) {
                                if (usuarios[i]->getDocumento() == reservaABorrar->getDocCliente()) {
                                    usuarios[i]->eliminarReserva(id);
                                    break;
                                }
                            }

                            delete reservaABorrar;
                            guardarReservas("reservas.txt", reservas, numReservas);
                            cout << "Reserva cancelada exitosamente.\n";
                            cout << "----------";
                        } else {
                            cout << "Reserva no encontrada.\n";
                        }
                    }

                    else if (opAdmin == 3) {
                        cout << "\n=== ACTUALIZAR HISTORICO DE RESERVAS ===\n";
                        string fechaStr;
                        cout << "Ingrese la fecha de corte (DD/MM/AAAA): ";
                        cin >> fechaStr;
                        Fecha fechaCorte;
                        fechaCorte.cargarDesdeCadena(fechaStr);

                        // Paso 1: cargar histórico existente
                        Reserva** historicas = nullptr;
                        int numHistoricas = cargarReservas("historico.txt", historicas);

                        // Paso 2: crear arreglo temporal para nuevas históricas
                        Reserva** nuevasHistoricas = new Reserva*[numReservas];
                        int numNuevasHistoricas = 0;

                        int totalMovidas = 0;

                        // Paso 3: recorrer arreglo global de reservas
                        int i = 0;
                        while (i < numReservas) {
                            Reserva* r = reservas[i];

                            // Verificar si el alojamiento pertenece al admin actual
                            bool pertenece = false;
                            for (int j = 0; j < admin->getNumAlojamientos(); j++) {
                                if (admin->getAlojamiento(j)->getCodigo() == r->getIdAlojamiento()) {
                                    pertenece = true;
                                    break;
                                }
                            }

                            if (!pertenece) {
                                i++;
                                continue;
                            }

                            // Verificar si ya terminó
                            Fecha salida = r -> getFechaSalida(); //Se copia el resultado en una variable
                            if (Fecha::compararFecha(&salida, &fechaCorte)) {
                                // 1. Eliminar del usuario
                                Usuario* u = buscarUsuario(usuarios, numUsuarios, r->getDocCliente());
                                if (u != nullptr) u->eliminarReserva(r->getId());

                                // 2. Eliminar del alojamiento
                                for (int j = 0; j < numAlojamientos; j++) {
                                    if (alojamientos[j]->getCodigo() == r->getIdAlojamiento()) {
                                        alojamientos[j]->eliminarReserva(r->getId());
                                        break;
                                    }
                                }

                                // 3. Guardar como histórica
                                nuevasHistoricas[numNuevasHistoricas++] = r;

                                // 4. Eliminar del arreglo global
                                for (int j = i; j < numReservas - 1; j++) {
                                    reservas[j] = reservas[j + 1];
                                }
                                numReservas--;
                                totalMovidas++;
                                // No incrementamos i porque ya se desplazaron los elementos
                            } else {
                                i++;
                            }
                        }

                        // Paso 4: unir históricos y guardar en archivo
                        Reserva** todasHistoricas = new Reserva*[numHistoricas + numNuevasHistoricas];
                        for (int i = 0; i < numHistoricas; i++)
                            todasHistoricas[i] = historicas[i];
                        for (int i = 0; i < numNuevasHistoricas; i++)
                            todasHistoricas[numHistoricas + i] = nuevasHistoricas[i];

                        // Guardar resultados
                        guardarReservas("reservas.txt", reservas, numReservas);
                        guardarReservas("historico.txt", todasHistoricas, numHistoricas + numNuevasHistoricas);

                        // Liberar memoria
                        delete[] nuevasHistoricas;
                        delete[] todasHistoricas;
                        delete[] historicas;

                        cout << totalMovidas << " reservas movidas al historico.\n";
                        limpiarBufferEntrada();
                    }

                } while (opAdmin != 4);

            } else {
                cout << "Administrador no encontrado.\n";
            }
        }

        else if (opcion == 2) {
            string docUsuario;
            cout << "Ingrese su documento de usuario: ";
            cin >> docUsuario;

            Usuario* usuario = buscarUsuario(usuarios, numUsuarios, docUsuario);
            if (usuario) {
                cout << "\nBienvenido, usuario " << usuario->getDocumento() << endl;

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
                        cout << "Entrada invalida. Intente nuevamente.\n";
                        continue;
                    }

                    if (opUsuario == 1) {
                        cout << "\n=== Reservas activas de " << usuario->getDocumento() << " ===\n";
                        usuario->mostrarReservas();
                        cout << "\n(Presione ENTER para continuar...)\n";
                        limpiarBufferEntrada();
                    }

                    else if (opUsuario == 2) {
                        cout << "\n=== Cancelacion de reserva ===\n";
                        usuario->mostrarReservas();

                        cout << "Ingrese el ID de la reserva a cancelar: ";
                        string idCancelar;
                        cin >> idCancelar;

                        // Paso 1: Buscar la reserva global y extraer puntero
                        Reserva* reservaABorrar = nullptr;
                        for (int i = 0; i < numReservas; i++) {
                            if (reservas[i]->getId() == idCancelar) {
                                reservaABorrar = reservas[i];
                                for (int j = i; j < numReservas - 1; j++) {
                                    reservas[j] = reservas[j + 1];
                                }
                                numReservas--;
                                break;
                            }
                        }

                        // Paso 2: eliminar de alojamiento y usuario
                        bool fueEliminada = false;
                        if (reservaABorrar != nullptr) {
                            for (int i = 0; i < numAlojamientos; i++) {
                                alojamientos[i]->eliminarReserva(idCancelar);
                            }

                            fueEliminada = usuario->eliminarReserva(idCancelar);

                            delete reservaABorrar;
                            guardarReservas("reservas.txt", reservas, numReservas);

                            if (fueEliminada) {
                                cout << "Reserva cancelada exitosamente.\n";
                            } else {
                                cout << "Error interno: se encontro en el arreglo global pero no en el usuario.\n";
                            }
                        } else {
                            cout << "No se encontró ninguna reserva con ese ID.\n";
                        }

                        cout << "\n(Presione ENTER para continuar...)\n";
                        limpiarBufferEntrada();
                    }

                    else if (opUsuario == 3) {
                        cout << "\n=== NUEVA RESERVA ===\n";
                        cout << "Seleccione el tipo de búsqueda:\n";
                        cout << "1. Buscar por filtros (municipio, precio, puntuación)\n";
                        cout << "2. Buscar directamente por código\n";
                        cout << "Opción: ";
                        int tipoBusqueda;
                        cin >> tipoBusqueda;

                        if (tipoBusqueda != 1 && tipoBusqueda != 2) {
                            cout << "Opción inválida.\n";
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
                            // 1. Solicitar criterios de búsqueda

                            cout << "Municipio deseado: ";
                            cin >> municipio;
                            string fechaStr;
                            cout << "Fecha de inicio (DD/MM/AAAA): ";
                            cin >> fechaStr;
                            fechaInicio.cargarDesdeCadena(fechaStr);

                            if (!fechaDentroDelRango(fechaInicio)) {
                                cout << "La fecha ingresada debe estar entre hoy y los proximos 12 meses.\n";
                                cout << "----------"<<endl;
                                limpiarBufferEntrada();
                                continue;
                            }


                            cout << "Cantidad de noches: ";
                            cin >> noches;

                            cout << "Precio maximo por noche (0 para ignorar): ";
                            cin >> precioMax;
                            if (precioMax == 0) precioMax = 999999999;

                            cout << "Puntuacion minima del anfitrion (0 a 5.0, 0 para ignorar): ";
                            cin >> puntuacionMin;

                            // 2. Mostrar alojamientos que cumplen
                            //Alojamiento* seleccion = nullptr;
                            bool hayCoincidencias = false;

                            cout << "\nAlojamientos disponibles que cumplen con los criterios:\n";
                            for (int i = 0; i < numAlojamientos; i++) {
                                Alojamiento* a = alojamientos[i];
                                if (aMinusculas(a->getMunicipio()) == aMinusculas(municipio) &&
                                    a->getPrecio() <= precioMax &&
                                    a->estaDisponible(fechaInicio, noches)) {

                                    Administrador* anfitrion = buscarAdministrador(admins, numAdmins, a->getAnfitrionDoc());
                                    if (anfitrion != nullptr && anfitrion->getEstrellas() >= puntuacionMin) {
                                        cout << "\nCodigo: " << a->getCodigo()
                                             << "\nNombre: "; a->mostrar();
                                        cout << "Precio por noche: $" << a->getPrecio()
                                             << "\nPuntuacion del anfitrion: " << anfitrion->getEstrellas() << endl;
                                        hayCoincidencias = true;
                                    }
                                }
                            }

                            if (!hayCoincidencias) {
                                cout << "\nNo se encontraron alojamientos con los criterios seleccionados.\n"<<endl;
                                limpiarBufferEntrada();
                                cout << "----------";
                                continue;
                            }
                        }

                        else if (tipoBusqueda == 2) {
                            cout << "Ingrese el código del alojamiento: ";
                            string codSeleccionado;
                            cin >> codSeleccionado;

                            //seleccion = nullptr;
                            for (int i = 0; i < numAlojamientos; i++) {
                                if (alojamientos[i]->getCodigo() == codSeleccionado) {
                                    seleccion = alojamientos[i];
                                    break;
                                }
                            }

                            if (seleccion == nullptr) {
                                cout << "No se encontró un alojamiento con ese código.\n";
                                cout << "----------";
                                continue;
                            }

                            cout << "Fecha de inicio (DD/MM/AAAA): ";
                            string fechaStr;
                            cin >> fechaStr;
                            fechaInicio.cargarDesdeCadena(fechaStr);

                            if (!fechaDentroDelRango(fechaInicio)) {
                                cout << "La fecha ingresada debe estar entre hoy y los próximos 12 meses.\n";
                                cout << "(Presione ENTER para continuar...)\n";
                                limpiarBufferEntrada();
                                continue;
                            }

                            cout << "Cantidad de noches: ";
                            cin >> noches;

                            if (!seleccion->estaDisponible(fechaInicio, noches)) {
                                cout << "El alojamiento no está disponible en ese rango.\n";
                                continue;
                            }

                            if (!usuario->fechaDisponible(fechaInicio, noches)) {
                                cout << "Usted ya tiene una reserva activa en esas fechas.\n";
                                continue;
                            }
                        }

                        // 3. Selección del alojamiento
                        cout << "\nIngrese el codigo del alojamiento que desea reservar: ";
                        string codSeleccionado;
                        cin >> codSeleccionado;

                        seleccion = nullptr;
                        for (int i = 0; i < numAlojamientos; i++) {
                            if (alojamientos[i]->getCodigo() == codSeleccionado) {
                                seleccion = alojamientos[i];
                                break;
                            }
                        }

                        if (seleccion == nullptr) {
                            cout << "Codigo invalido.\n";
                            continue;
                        }

                        // 4. Validar disponibilidad en usuario
                        if (!usuario->fechaDisponible(fechaInicio, noches)) {
                            cout << "Usted ya tiene una reserva activa en esas fechas.\n";
                            continue;
                        }

                        // 5. Confirmar datos de reserva
                        string metodoPago, comentario;
                        double valor = seleccion->getPrecio() * noches;
                        Fecha fechaPago = fechaInicio;

                        cout << "Metodo de pago (PSE/Tarjeta): ";
                        cin >> metodoPago;
                        metodoPago = aMinusculas(metodoPago);

                        if (metodoPago != "pse" && metodoPago != "tarjeta") {
                            cout << "Metodo de pago invalido.\n";
                            continue;
                        }

                        cout << "Comentarios: ";
                        cin.ignore();
                        getline(cin, comentario);

                        // 6. Crear ID único (simple)
                        string idReserva = "R" + to_string(1000 + numReservas);

                        // 7. Crear y agregar la reserva
                        Reserva* nueva = new Reserva(idReserva, fechaInicio, noches,
                                                     seleccion->getCodigo(), usuario->getDocumento(),
                                                     metodoPago, fechaPago, valor, comentario);

                        usuario->agregarReserva(nueva);
                        seleccion->agregarReserva(nueva);
                        reservas[numReservas++] = nueva;

                        // 8. Guardar en archivo
                        guardarReservas("reservas.txt", reservas, numReservas);

                        cout << "\n=== COMPROBANTE DE RESERVA ===\n";
                        cout << "ID: " << idReserva << endl;
                        cout << "Usuario: " << usuario->getDocumento() << endl;
                        cout << "Alojamiento: " << seleccion->getCodigo() << endl;
                        cout << "Fecha de inicio: " << fechaExtendida(fechaInicio) << endl;
                        cout << "Fecha de salida: " << fechaExtendida(fechaInicio.sumarNoches(noches)) << endl;
                        cout << "Total: $" << valor << endl;

                        limpiarBufferEntrada();
                    }
                } while (opUsuario != 4);

            } else {
                cout << "Usuario no encontrado.\n";
            }
        }

    } while (opcion != 3);

    cout << "\nGracias por usar nuestros servicios.\n";
    return 0;
}
