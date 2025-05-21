#ifndef LECTURA_H
#define LECTURA_H

#include "Usuario.h"
#include "Administrador.h"
#include "Alojamiento.h"
#include "Reserva.h"

// Cargar usuarios desde archivo
int cargarUsuarios(const string& nombreArchivo, Usuario**& usuarios);

int cargarAdministradores(const string& nombreArchivo, Administrador**& admins);

int cargarAlojamientos(const string& nombreArchivo, Alojamiento**& alojamientos);

void asociarAlojamientos(Administrador** admins, int cantAdmins, Alojamiento** alojamientos, int cantAlojamientos);

// Cargar reservas desde archivo
int cargarReservas(const string& nombreArchivo, Reserva**& reservas);

#endif
