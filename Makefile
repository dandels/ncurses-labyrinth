all:
	gcc labyrinth.c -lncurses -ltinfo -o labyrinth \
	-pedantic \
	-Wall \
	-Wshadow \
	-Wpointer-arith \
	-Wcast-qual \
	-Wcast-align \
	-Wstrict-prototypes \
	-Wmissing-prototypes \
	-Wconversion \

clean:
	rm labyrinth
