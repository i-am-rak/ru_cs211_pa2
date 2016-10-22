all: calc.c format.c
	gcc -Wall -g -o calc calc.c
	gcc -Wall -g -o format format.c
calc:
	gcc -Wall -g -o calc calc.c
format:
	gcc -Wall -g -o format format.c
clean:
	rm format calc
