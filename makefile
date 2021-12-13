all:
	+$(MAKE) -C src

setup:
	mkdir -p ./gifs
	touch log
	: > log

clean:
	rm -f sim
