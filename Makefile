CC = gcc
#CFLAGS=-std=c11 `pkg-config --cflags glib-2.0 gio-2.0 gobject-2.0`
#LDFLAGS=`pkg-config --libs glib-2.0 gio-2.0 gobject-2.0`
PKGCONFIG = $(shell which pkg-config)
CFLAGS = $(shell $(PKGCONFIG) --cflags gtk+-3.0)
LIBS = $(shell $(PKGCONFIG) --libs gtk+-3.0)

SRC = basedatos.c basedatos-aplicacion.h

OBJS = $(SRC:.c=.o)

all: basedatosaplicacion

%.o: %.c
	$(CC) -c -o $(@F) $(CFLAGS) $<

basedatosaplicacion: $(OBJS)
	$(CC) -o $(@F) $(OBJS) $(LIBS)

clean:
	rm -f $(OBJS)
	rm -f basedatosaplicacion
