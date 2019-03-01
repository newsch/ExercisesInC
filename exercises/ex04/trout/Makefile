trout: main.c trout.o util.o trout.h
	gcc -Wall -o trout main.c trout.o util.o
trout.o: trout.h trout.c
	gcc -Wall -c trout.c
util.o: trout.h util.c
	gcc -Wall -c util.c
clean:
	rm trout util.o trout.o
