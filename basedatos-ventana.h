/* basedatos-ventana.h
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

#ifndef __BASEDATOSVENTANA_H
#define __BASEDATOSVENTANA_H

#include <gtk-3.0/gtk/gtk.h>

G_BEGIN_DECLS

#define BASEDATOS_TYPE_VENTANA (basedatos_ventana_get_type())

G_DECLARE_FINAL_TYPE (BasedatosVentana, basedatos_ventana, BASEDATOS, VENTANA, GtkApplicationWindow)

BasedatosVentana *basedatos_ventana_new (BasedatosAplicacion *basedatos_aplicacion);
void              basedatos_ventana_open (BasedatosVentana *basedatos_ventana);

G_END_DECLS
