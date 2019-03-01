trout: main.c trout.o util.o trout.h util.h
	gcc -Wall -o trout main.c trout.o util.o
trout.o: trout.c trout.h
	gcc -Wall -c trout.c
util.o: util.c util.h
	gcc -Wall -c util.c
clean:
	rm trout util.o trout.o
