CC = gcc
CFLAGS = -Wall
SRC = src/game_of_life.c src/utils.c
HEADERS = src/game_of_life.h src/utils.h src/definitions.h
OBJ = main.o $(SRC:.c=.o)
EXEC = game_of_life

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra de limpeza
clean:
	rm -f $(OBJ) $(EXEC)

# Regra de limpeza profunda (opcional, remove arquivos adicionais se houver)
clean-all: clean
	rm -f *~
