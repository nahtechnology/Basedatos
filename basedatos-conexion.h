/* basedatos-conexion.h
 *
 * Copyright 2020 Antonio Francisco Alonso Valerdi <unknown@domain.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <glib-2.0/glib-object.h>
#include <postgresql/libpq-fe.h>

G_BEGIN_DECLS

#define BASEDATOS_TYPE_CONEXION (basedatos_conexion_get_type())

G_DECLARE_FINAL_TYPE (BasedatosConexion, basedatos_conexion, BASEDATOS, CONEXION, GObject)

BasedatosConexion *basedatos_conexion_new (void);

void basedatos_conexion_datos (BasedatosConexion *self,
                               gchar *servidor,
                               gchar *ambiente,
                               gchar *puerto,
                               gchar *usuario,
                               gchar *contrasenia,
                               gchar *basedatos);

gchar *basedatos_conexion_cadena (BasedatosConexion *self);

PGconn *basedatos_conexion_crea_conexion(BasedatosConexion *self);

gchar *basedatos_conexion_ping (BasedatosConexion *self);

G_END_DECLS
