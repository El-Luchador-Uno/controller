CC=gcc
CFLAGS=-Wall -Iinclude
SRC=$(wildcard src/*.c src/gpio/*.c src/utils/*.c)
OBJ=$(SRC:.c=.o)
EXEC=start_bot

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ) -l wiringPi -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
