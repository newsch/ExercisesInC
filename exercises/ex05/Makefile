CC=gcc
CFLAGS += -Wall

# CCOMMAND=$(CC) $(CFLAGS) $^ -o $@

shapes: shapes.c
	$(CCOMMAND)
test_shapes: shapes.o
# CCOMMAND = $(CC) $(CFLAGS) $^ -o $@

test1: rand.o
test2: rand.o
test3: rand.o
test4: rand.o
time_rand: time_rand.c rand.o

%.o: CFLAGS += -c
%.o: %.c %.h
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm *.o shapes test_shapes test? time_rand
