CC=gcc
CFLAGS += -Wall

shtee : shtee.c
	$(CC) $(CFLAGS) -o shtee shtee.c

debug : CFLAGS += -DDEBUG -g  # target-specific variables: https://www.gnu.org/software/make/manual/make.html#Target_002dspecific
debug : clean shtee

clean :
	rm shtee
