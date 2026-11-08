CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -pedantic
OBJ := main.o mini_parser.o tabla_simbolos.o

.PHONY: all clean

all: compint_a06
	@echo "Base de Actividad 6 construida correctamente."

compint_a06: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

main.o: main.c mini_parser.h tabla_simbolos.h
	$(CC) $(CFLAGS) -c main.c

mini_parser.o: mini_parser.c mini_parser.h tabla_simbolos.h
	$(CC) $(CFLAGS) -c mini_parser.c

tabla_simbolos.o: tabla_simbolos.c tabla_simbolos.h
	$(CC) $(CFLAGS) -c tabla_simbolos.c

clean:
	rm -f $(OBJ) compint_a06
