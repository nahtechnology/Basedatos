/* basedatos-respaldo.c
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

#include "basedatos-respaldo.h"

struct _BasedatosRespaldo
{
  GObject parent_instance;
  gchar *esquema;
};

G_DEFINE_TYPE (BasedatosRespaldo, basedatos_respaldo, G_TYPE_OBJECT)

enum {
  PROP_0,
  ESQUEMA,
  N_PROPS
};

static GParamSpec *properties [N_PROPS];

BasedatosRespaldo *basedatos_respaldo_new ()
{
  return g_object_new (BASEDATOS_TYPE_RESPALDO, NULL);
}

BasedatosRespaldo *basedatos_respaldo_new_esquema (const gchar *esquema)
{
  return g_object_new (BASEDATOS_TYPE_RESPALDO, "esquema", esquema, NULL);
}

static void
basedatos_respaldo_finalize (GObject *object)
{
  BasedatosRespaldo *self = (BasedatosRespaldo *)object;
  
  g_free (self->esquema);

  G_OBJECT_CLASS (basedatos_respaldo_parent_class)->finalize (object);
}

static void
basedatos_respaldo_get_property (GObject    *object,
                                 guint       prop_id,
                                 GValue     *value,
                                 GParamSpec *pspec)
{
  BasedatosRespaldo *self = BASEDATOS_RESPALDO (object);

  switch (prop_id)
    {
      case ESQUEMA:
        g_value_set_string(value, self->esquema);
        break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
basedatos_respaldo_set_property (GObject      *object,
                                 guint         prop_id,
                                 const GValue *value,
                                 GParamSpec   *pspec)
{
  BasedatosRespaldo *self = BASEDATOS_RESPALDO (object);

  switch (prop_id)
    {
      case ESQUEMA:
        self->esquema = g_value_dup_string (value);
        break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
basedatos_respaldo_class_init (BasedatosRespaldoClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->finalize = basedatos_respaldo_finalize;
  object_class->get_property = basedatos_respaldo_get_property;
  object_class->set_property = basedatos_respaldo_set_property;
  
  properties[ESQUEMA] =
    g_param_spec_string ("esquema",
                         "Esquema",
                         "Esquema al cual se va a recuperar los datos",
                         NULL,
                         G_PARAM_READWRITE | G_PARAM_CONSTRUCT | G_PARAM_STATIC_STRINGS);
  
  g_object_class_install_properties (object_class, N_PROPS, properties);
}

static void
basedatos_respaldo_init (BasedatosRespaldo *self)
{
}

gboolean basedatos_respaldo_inicio(BasedatosRespaldo *basedatos_respaldo,
                                   GError *gerror,
                                   PGconn *pgconn)
{
  
}
