CC=-gcc
CFLAGS=-Wall

# glib flags
GLIBCFLAGS=$(shell pkg-config --cflags glib-2.0)
GLIBLDLIBS=$(shell pkg-config --libs glib-2.0)

ex_compile: CFLAGS+=$(GLIBCFLAGS)
ex_compile: LDLIBS+=$(GLIBLDLIBS)

word_count: CFLAGS+=$(GLIBCFLAGS)
word_count: LDLIBS+=$(GLIBLDLIBS)
