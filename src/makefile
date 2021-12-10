
CC = gcc

graphics.o: graphics.c graphics.h
	$(CC) $^ -c

rand.o: rand.c rand.h
	$(CC) $^ -c

log.o: log.c log.h
	$(CC) $^ -c

neurons.o: neurons.c neurons.h
	$(CC) $^ -c

sim: main.c brain.c brain.h env.c env.h spawn.c spawn.h graphics.o rand.o log.o neurons.o
	$(CC) $^ -g -lm -lgd -o $@

clean:
	rm -f *.o *.h.gch
	rm ./sim
	
setup:
	mkdir -p ./gifs
	touch log	
	: > log
