CC=gcc
CFLAGS += -Wall

CCOMMAND=$(CC) $(CFLAGS) $^ -o $@

shapes: shapes.c
	$(CCOMMAND)
test_shapes: test_shapes.c shapes.o
	$(CCOMMAND)
%.o: CFLAGS += -c
%.o: %.c %.h
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm *.o shapes test_shapes
