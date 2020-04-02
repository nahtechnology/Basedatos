/* basedatos-ventana.c
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

#include "basedatos-ventana.h"

struct _BasedatosVentana
{
  GtkApplicationWindow parent_instance;
};

G_DEFINE_TYPE (BasedatosVentana, basedatos_ventana, GTK_TYPE_APPLICATION_WINDOW)

enum {
  PROP_0,
  N_PROPS
};

static GParamSpec *properties [N_PROPS];

BasedatosVentana *
basedatos_ventana_new (void)
{
  return g_object_new (BASEDATOS_TYPE_VENTANA, NULL);
}

static void
basedatos_ventana_finalize (GObject *object)
{
  BasedatosVentana *self = (BasedatosVentana *)object;

  G_OBJECT_CLASS (basedatos_ventana_parent_class)->finalize (object);
}

static void
basedatos_ventana_get_property (GObject    *object,
                                guint       prop_id,
                                GValue     *value,
                                GParamSpec *pspec)
{
  BasedatosVentana *self = BASEDATOS_VENTANA (object);

  switch (prop_id)
    {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
basedatos_ventana_set_property (GObject      *object,
                                guint         prop_id,
                                const GValue *value,
                                GParamSpec   *pspec)
{
  BasedatosVentana *self = BASEDATOS_VENTANA (object);

  switch (prop_id)
    {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
basedatos_ventana_class_init (BasedatosVentanaClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->finalize = basedatos_ventana_finalize;
  object_class->get_property = basedatos_ventana_get_property;
  object_class->set_property = basedatos_ventana_set_property;
}

static void
basedatos_ventana_init (BasedatosVentana *self)
{
}
