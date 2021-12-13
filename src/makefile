
CC = gcc

sim: main.c env.o spawn.o graphics.o rand.o log.o neurons.o brain.o selector.o setup.o conf.o
	$(CC) $^ -g -lm -lgd -o $@
	mv sim ../

%.o: %.c %.h
	$(CC) $^ -c

clean:
	rm -f *.o *.h.gch
