/* basedatos-configuracion.c
 *
 * Copyright 2020 Antonio Francisco Alonso Valerdi <unknown@domain.org>
 *
 * This program is free softwareribute it and/or modify
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

#include "basedatos-configuracion.h"
#include "basedatos-conexion.h"

struct _BasedatosConfiguracion
{
  GObject parent_instance;
  gchar *nombre_archivo;
};

G_DEFINE_TYPE (BasedatosConfiguracion, basedatos_configuracion, G_TYPE_OBJECT)

enum {
  PROP_0,
  PROP_NOMBRE_ARCHIVO,
  N_PROPS
};

static GParamSpec *properties [N_PROPS];

BasedatosConfiguracion *
basedatos_configuracion_new (void)
{
  return g_object_new (BASEDATOS_TYPE_CONFIGURACION, NULL);
}

static void
basedatos_configuracion_finalize (GObject *object)
{
  BasedatosConfiguracion *self = (BasedatosConfiguracion *)object;
  
  g_free (self->nombre_archivo);

  G_OBJECT_CLASS (basedatos_configuracion_parent_class)->finalize (object);
}

static void
basedatos_configuracion_get_property (GObject    *object,
                                      guint       prop_id,
                                      GValue     *value,
                                      GParamSpec *pspec)
{
  BasedatosConfiguracion *self = BASEDATOS_CONFIGURACION (object);

  switch (prop_id)
    {
      case PROP_NOMBRE_ARCHIVO:
        g_value_set_string(value, basedatos_configuracion_get_nombre_archivo(self));
        break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
basedatos_configuracion_set_property (GObject      *object,
                                      guint         prop_id,
                                      const GValue *value,
                                      GParamSpec   *pspec)
{
  BasedatosConfiguracion *self = BASEDATOS_CONFIGURACION (object);

  switch (prop_id)
    {
      case PROP_NOMBRE_ARCHIVO:
        self->nombre_archivo = g_value_dup_string (value);
        break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
basedatos_configuracion_class_init (BasedatosConfiguracionClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->finalize = basedatos_configuracion_finalize;
  object_class->get_property = basedatos_configuracion_get_property;
  object_class->set_property = basedatos_configuracion_set_property;
  
  properties[PROP_NOMBRE_ARCHIVO] =
    g_param_spec_string ("archivo-configuracion",
                         "Archivo Configuracion",
                         "Archivo donde viene la configuracion de la conexion",
                         "configuracion.ini",
                         G_PARAM_READWRITE | G_PARAM_CONSTRUCT | G_PARAM_STATIC_STRINGS);
  
  g_object_class_install_properties (object_class, N_PROPS, properties);
}

static void
basedatos_configuracion_init (BasedatosConfiguracion *self)
{
}

void  basedatos_configuracion_set_nombre_archivo    (BasedatosConfiguracion *self,
                                                     char *nombre_archivo)
{
  g_free (self->nombre_archivo);
  self->nombre_archivo = g_strdup (nombre_archivo);
}

char  *basedatos_configuracion_get_nombre_archivo   (BasedatosConfiguracion *self)
{
  return self->nombre_archivo;
}

GSList *basedatos_configuracion_carga (BasedatosConfiguracion *self, GError **gerror)
{ 
  GKeyFile *key_file = g_key_file_new ();
  GSList *lista = NULL;
  gchar **grupo = NULL;
  gchar *servidor = NULL;
  gchar *puerto = NULL;
  gchar *usuario = NULL;
  gchar *contrasenia = NULL;
  gchar *basedatos = NULL;
  BasedatosConexion *basedatos_conexion;
  if (!g_key_file_load_from_file (key_file, self->nombre_archivo, G_KEY_FILE_NONE, gerror))
    {
      return NULL;
    }
  grupo = g_key_file_get_groups (key_file, NULL);
  if (*grupo == NULL)
    {
      g_set_error_literal(gerror, g_quark_from_string("Sin ambientes"), 1, "El archivo de configuracion no contiene ambientes");
      return NULL;
    }
  else
    {
      gchar **copy = grupo;
      GError *gerror_local = NULL;
      while (*grupo)
        {
          basedatos_conexion = basedatos_conexion_new ();
          servidor = g_key_file_get_value (key_file, *grupo, "servidor", &gerror_local);
          if (servidor == NULL && g_error_matches (gerror_local, G_KEY_FILE_ERROR, G_KEY_FILE_ERROR_KEY_NOT_FOUND))
            {
              g_set_error (gerror, g_quark_from_string("Sin servidor"), 1, "Para el ambientes:%s no tiene el valor:%s", *grupo, "servidor");
              return NULL;
            }
          gerror_local = NULL;
          puerto = g_key_file_get_value (key_file, *grupo, "puerto", &gerror_local);
          if (puerto == NULL && g_error_matches (gerror_local, G_KEY_FILE_ERROR, G_KEY_FILE_ERROR_KEY_NOT_FOUND))
            {
              g_set_error (gerror, g_quark_from_string("Sin servidor"), 1, "Para el ambientes:%s no tiene el valor:%s", *grupo, "puerto");
              return NULL;
            }
          gerror_local = NULL;
          usuario = g_key_file_get_value (key_file, *grupo, "usuario", &gerror_local);
          if (usuario == NULL && g_error_matches (gerror_local, G_KEY_FILE_ERROR, G_KEY_FILE_ERROR_KEY_NOT_FOUND))
            {
              g_set_error (gerror, g_quark_from_string("Sin servidor"), 1, "Para el ambientes:%s no tiene el valor:%s", *grupo, "usuario");
              return NULL;
            }
          gerror_local = NULL;
          contrasenia = g_key_file_get_value (key_file, *grupo, "contrasenia", &gerror_local);
          if (contrasenia == NULL && g_error_matches (gerror_local, G_KEY_FILE_ERROR, G_KEY_FILE_ERROR_KEY_NOT_FOUND))
            {
              g_set_error (gerror, g_quark_from_string("Sin servidor"), 1, "Para el ambientes:%s no tiene el valor:%s", *grupo, "contrasenia");
              return NULL;
            }
          gerror_local = NULL;
          basedatos = g_key_file_get_value (key_file, *grupo, "basedatos", &gerror_local);
          if (basedatos == NULL && g_error_matches (gerror_local, G_KEY_FILE_ERROR, G_KEY_FILE_ERROR_KEY_NOT_FOUND))
            {
              g_set_error (gerror, g_quark_from_string("Sin servidor"), 1, "Para el ambientes:%s no tiene el valor:%s", *grupo, "basedatos");
              return NULL;
            }
          grupo++;
          basedatos_conexion_datos (basedatos_conexion, servidor, *grupo, puerto, usuario, contrasenia, basedatos);
          lista = g_slist_append (lista, basedatos_conexion);
        }
      grupo = copy;
      g_strfreev (grupo);
      g_free (servidor);
      g_free (puerto);
      g_free (usuario);
      g_free (contrasenia);
      g_free (basedatos);
    }
  g_key_file_unref (key_file);
  return lista;
}
