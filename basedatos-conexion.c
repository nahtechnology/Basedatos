/* basedatos-conexion.c
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

#include "basedatos-conexion.h"

struct _BasedatosConexion
{
  GObject parent_instance;
  
  gchar *ambiente;
  gchar *servidor;
  gchar *puerto;
  gchar *usuario;
  gchar *contrasenia;
  gchar *basedatos;
};

G_DEFINE_TYPE (BasedatosConexion, basedatos_conexion, G_TYPE_OBJECT)

enum {
  PROP_0,
  AMBIENTE,
  SERVIDOR,
  PUERTO,
  USUARIO,
  CONTRASENIA,
  BASEDATOS,
  N_PROPS
};

static GParamSpec *properties [N_PROPS];

BasedatosConexion *
basedatos_conexion_new (void)
{
  return g_object_new (BASEDATOS_TYPE_CONEXION, NULL);
}

static void
basedatos_conexion_finalize (GObject *object)
{
  BasedatosConexion *self = (BasedatosConexion *)object;

  g_free(self->servidor);
  G_OBJECT_CLASS (basedatos_conexion_parent_class)->finalize (object);
}

static void
basedatos_conexion_get_property (GObject    *object,
                                 guint       prop_id,
                                 GValue     *value,
                                 GParamSpec *pspec)
{
  BasedatosConexion *self = BASEDATOS_CONEXION (object);

  switch (prop_id)
    {
      case SERVIDOR:
        g_value_set_string(value, self->servidor);
        break;
      case AMBIENTE:
        g_value_set_string(value, self->ambiente);
        break;
      case PUERTO:
        g_value_set_string(value, self->puerto);
        break;
      case USUARIO:
        g_value_set_string(value, self->usuario);
        break;
      case CONTRASENIA:
        g_value_set_string(value, self->contrasenia);
        break;
      case BASEDATOS:
        g_value_set_string(value, self->basedatos);
        break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
basedatos_conexion_set_property (GObject      *object,
                                 guint         prop_id,
                                 const GValue *value,
                                 GParamSpec   *pspec)
{
  BasedatosConexion *self = BASEDATOS_CONEXION (object);

  switch (prop_id)
    {
      case SERVIDOR:
        self->servidor = g_value_dup_string(value);
        break;
      case AMBIENTE:
        self->ambiente = g_value_dup_string(value);
        break;
      case PUERTO:
        self->puerto = g_value_dup_string(value);
        break;
      case USUARIO:
        self->usuario = g_value_dup_string(value);
        break;
      case CONTRASENIA:
        self->contrasenia = g_value_dup_string(value);
        break;
      case BASEDATOS:
        self->basedatos = g_value_dup_string (value);
        break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
basedatos_conexion_class_init (BasedatosConexionClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->finalize = basedatos_conexion_finalize;
  object_class->get_property = basedatos_conexion_get_property;
  object_class->set_property = basedatos_conexion_set_property;
  
  properties[SERVIDOR] = 
    g_param_spec_string ("servidor",
                         "Servidor",
                         "Dirección IP del servidor",
                         NULL,
                         G_PARAM_READWRITE | G_PARAM_CONSTRUCT | G_PARAM_STATIC_STRINGS);
  properties[AMBIENTE] =
    g_param_spec_string ("ambiente",
                         "Ambiente",
                         "Ambiente para tomar los datos",
                         NULL,
                         G_PARAM_READWRITE | G_PARAM_CONSTRUCT | G_PARAM_STATIC_STRINGS);
    properties[PUERTO] =
    g_param_spec_string ("puerto",
                         "Puerto",
                         "Número del puerto para la base da datos",
                         NULL,
                         G_PARAM_READWRITE | G_PARAM_CONSTRUCT | G_PARAM_STATIC_STRINGS);
    properties[USUARIO] =
    g_param_spec_string ("usuario",
                         "Usuario",
                         "Nombre del usuario para la base de datos",
                         NULL,
                         G_PARAM_READWRITE | G_PARAM_CONSTRUCT | G_PARAM_STATIC_STRINGS);
    properties[CONTRASENIA] =
    g_param_spec_string ("contrasenia",
                         "Contrasenia",
                         "Contrasenia para la base de datos",
                         NULL,
                         G_PARAM_READWRITE | G_PARAM_CONSTRUCT | G_PARAM_STATIC_STRINGS);
  properties[BASEDATOS] =
    g_param_spec_string ("basedatos",
                         "Basedatos",
                         "Nombre de la base de datos",
                         NULL,
                         G_PARAM_READWRITE | G_PARAM_CONSTRUCT | G_PARAM_STATIC_STRINGS);
  
  g_object_class_install_properties (object_class, N_PROPS, properties);
}

static void
basedatos_conexion_init (BasedatosConexion *self)
{
}

void basedatos_conexion_datos (BasedatosConexion *self, 
                               gchar *servidor,
                               gchar *ambiente,
                               gchar *puerto,
                               gchar *usuario,
                               gchar *contrasenia,
                               gchar *basedatos)
{
  self->servidor = g_strdup (servidor);
  self->ambiente = g_strdup (ambiente);
  self->puerto = g_strdup (puerto);
  self->usuario = g_strdup (usuario);
  self->contrasenia = g_strdup (contrasenia);
  self->basedatos = g_strdup (basedatos);
}

gchar *basedatos_conexion_cadena (BasedatosConexion *self)
{
  gchar *cadena_conexion = "";
  cadena_conexion = g_strconcat (cadena_conexion, "postgresql://", self->usuario, NULL);
  cadena_conexion = g_strconcat (cadena_conexion, ":", self->contrasenia, NULL);
  cadena_conexion = g_strconcat (cadena_conexion, "@", self->servidor, NULL);
  cadena_conexion = g_strconcat (cadena_conexion, ":", self->puerto, NULL);
  cadena_conexion = g_strconcat (cadena_conexion, "/", self->basedatos, NULL);
  return cadena_conexion;
}

PGconn *basedatos_conexion_crea_conexion(BasedatosConexion *self)
{
  return PQconnectdb (basedatos_conexion_cadena (self));
}

gchar *basedatos_conexion_ping (BasedatosConexion *self)
{
  gchar *estatus;
  PGPing ping = PQping(basedatos_conexion_cadena (self));
  switch (ping)
    {
      case PQPING_OK:
        estatus = "El servidor está corriendo y aparentemente acepta conexiones";
        break;
      case PQPING_REJECT:
        estatus = "El servidor está corriendo pero deshabilita las conexiones (iniciando, apagando o se recupera de un colapso)";
        break;
      case PQPING_NO_RESPONSE:
        estatus = "No se puede conectar con el servidor. Podría ser que el servidor no esta corriendo, que haya un error con los parámetros de conexión o problemas como la red";
        break;
      case PQPING_NO_ATTEMPT:
        estatus = "No se han hehchos intentos de conexion. Por los parametrós de conexión son in correctos o problemas del lado del cliente (No hay memoria)";
        break;
    }
  return estatus;
}
