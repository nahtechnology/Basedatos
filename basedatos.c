/* basedatos.c
 *
 * Copyright 2020 Antonio Francisco Alonso Valerdi
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
 */


#include <stdio.h>
#include <stdlib.h>
#include <glib-2.0/glib.h>
#include "basedatos-configuracion.h"
#include "basedatos-conexion.h"
#include "basedatos-respaldo.h"

int
main (int argc,
      char *argv[])
{
  GError *gerror = NULL;
  BasedatosConfiguracion *basedatosConfiguracion = basedatos_configuracion_new ();
  GSList *lista = basedatos_configuracion_carga (basedatosConfiguracion, &gerror);
  gchar *estatus = basedatos_conexion_ping (lista->data);
  if (lista == NULL)
    {
      printf("%s\n", gerror->message);
    }
  else
    {
      printf("%s\n", estatus);
    }
  BasedatosRespaldo *basedatos_resplado = basedatos_respaldo_new ("administracion");
  return EXIT_SUCCESS;
}
