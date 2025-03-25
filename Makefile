CC=gcc
CFLAGS=-Wall -Iinclude
SRC=src/main.c src/bluetooth.c src/joystick.c src/utils.c
OBJ=$(SRC:.c=.o)
EXEC=bluetooth_joystick

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
