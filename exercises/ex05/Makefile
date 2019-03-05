CC=gcc
CFLAGS += -Wall

CCOMMAND=$(CC) $(CFLAGS) $^ -o $@

shapes: shapes.c
	$(CCOMMAND)
test_shapes: test_shapes.c shapes.o
CCOMMAND = $(CC) $(CFLAGS) $^ -o $@

test1: test1.c rand.o
	$(CCOMMAND)
test2: test1.c rand.o
	$(CCOMMAND)
time_rand: time_rand.c rand.o
	$(CCOMMAND)

%.o: CFLAGS += -c
%.o: %.c %.h
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm *.o shapes test_shapes test? time_rand
