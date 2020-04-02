/* basedatos-configuracion.h
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

#include "basedatos-conexion.h"
#include <glib-2.0/glib-object.h>

G_BEGIN_DECLS

#define BASEDATOS_TYPE_CONFIGURACION (basedatos_configuracion_get_type())

G_DECLARE_FINAL_TYPE (BasedatosConfiguracion, basedatos_configuracion, BASEDATOS, CONFIGURACION, GObject)

BasedatosConfiguracion *basedatos_configuracion_new (void);

void  basedatos_configuracion_set_nombre_archivo    (BasedatosConfiguracion *self,
                                                     char *nombre_archivo);

char  *basedatos_configuracion_get_nombre_archivo   (BasedatosConfiguracion *self);

GSList *basedatos_configuracion_carga (BasedatosConfiguracion *self, 
                                         GError **gerror);

G_END_DECLS
