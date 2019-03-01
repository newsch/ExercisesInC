CC=gcc
CFLAGS += -Wall

trout: main.c trout.o util.o trout.h util.h
	$(CC) $(CFLAGS) $^ -o $@
%.o: CFLAGS += -c
%.o: %.c %.h
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm trout util.o trout.o
