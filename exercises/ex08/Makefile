CC=-gcc
CFLAGS=-Wall

ex_compile: CFLAGS+=$(shell pkg-config --cflags glib-2.0)
ex_compile: LDLIBS+=$(shell pkg-config --libs glib-2.0)
