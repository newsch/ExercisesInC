CFLAGS+=-Wall


counter: counter.c
	gcc -Wall -o counter counter.c -lpthread

counter_array: LDLIBS+=-lpthread
counter_array: mutex.o

counter_array_mutex: LDLIBS+=-lpthread
counter_array_mutex: mutex.o

counter_mutex: counter_mutex.c
	gcc -Wall -o counter_mutex counter_mutex.c -lpthread

barrier: barrier.c utils.c
	gcc -Wall -std=c99 -o barrier barrier.c utils.c -lpthread

barrier_soln: barrier_soln.c utils.c
	gcc -Wall -std=c99 -o barrier_soln barrier_soln.c utils.c -lpthread

read_write: read_write.c utils.c
	gcc -Wall -std=c99 -o read_write read_write.c utils.c -lpthread

read_write_soln: read_write_soln.c utils.c
	gcc -Wall -std=c99 -o read_write_soln read_write_soln.c utils.c -lpthread
