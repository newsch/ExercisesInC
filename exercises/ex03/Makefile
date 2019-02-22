CC=gcc
CFLAGS += -Wall

shtee : shtee.c
	$(CC) $(CFLAGS) -o shtee shtee.c

# target-specific variables: https://www.gnu.org/software/make/manual/make.html#Target_002dspecific
debug : CFLAGS += -DDEBUG -g
debug : shtee

clean :
	rm shtee
