/* basedatos-aplicacion.c
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
#include <gtk-3.0/gtk/gtk.h>
#include "basedatos-aplicacion.h"
#include "basedatos-ventana.h"

struct _BasedatosAplicacion
{
  GtkApplication parent_instance;
};

G_DEFINE_TYPE (BasedatosAplicacion, basedatos_aplicacion, GTK_TYPE_APPLICATION)

enum {
  PROP_0,
  N_PROPS
};

static GParamSpec *properties [N_PROPS];

BasedatosAplicacion *
basedatos_aplicacion_new (void)
{
  return g_object_new (BASEDATOS_TYPE_APLICACION, 
                       "application-id", "org.gtk.basedatos",
                       "flags", G_APPLICATION_HANDLES_OPEN,
                       NULL);

}

static void
basedatos_aplicacion_finalize (GObject *object)
{
  BasedatosAplicacion *self = (BasedatosAplicacion *)object;

  G_OBJECT_CLASS (basedatos_aplicacion_parent_class)->finalize (object);
}

static void
basedatos_aplicacion_get_property (GObject    *object,
                                   guint       prop_id,
                                   GValue     *value,
                                   GParamSpec *pspec)
{
  BasedatosAplicacion *self = BASEDATOS_APLICACION (object);

  switch (prop_id)
    {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
basedatos_aplicacion_set_property (GObject      *object,
                                   guint         prop_id,
                                   const GValue *value,
                                   GParamSpec   *pspec)
{
  BasedatosAplicacion *self = BASEDATOS_APLICACION (object);

  switch (prop_id)
    {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
basedatos_aplicacion_class_init (BasedatosAplicacionClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->finalize = basedatos_aplicacion_finalize;
  object_class->get_property = basedatos_aplicacion_get_property;
  object_class->set_property = basedatos_aplicacion_set_property;
}

static void
basedatos_aplicacion_init (BasedatosAplicacion *self)
{
}

static void
basedatos_aplicacion_active (GApplication *gapplication)
{
  BasedatosVentana *basedatos_ventana = NULL;
  basedatos_ventana = basedatos_ventana_new (BASEDATOS_APLICACION(gapplication));
  gtk_window_present (GTK_WINDOW (basedatos_ventana));
}

static void
basedatos_aplicacion_open (GApplication  *gapplication)
{
  GList *ventanas = NULL;
  BasedatosVentana *basedatos_ventana = NULL;
  ventanas = gtk_application_get_windows (GTK_APPLICATION (gapplication));
  if (ventanas)
    {
      basedatos_ventana = BASEDATOS_TYPE_VENTANA (ventanas->data);
    }
  else
    {
      basedatos_ventana = basedatos_ventana_new (BASEDATOS_APLICACION(gapplication));
    }
  gtk_window_present (GTK_WINDOW (basedatos_ventana));
}

BasedatosAplicacion *
basedatos_aplicacion_new (void)
{
  return g_object_new (BASEDATOS_TYPE_APLICACION, 
                       "application-id", "org.gtk.exampleapp",
                       "flags", G_APPLICATION_HANDLES_OPEN,
                       NULL);
}
