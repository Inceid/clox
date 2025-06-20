CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LIBS = -lreadline -lncurses
DEBUG_FLAGS ?=
SRC = main.c compiler.c scanner.c vm.c \
	  object.c value.c chunk.c table.c \
	  memory.c debug.c

all:
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o lox $(SRC) $(LIBS) && echo 'success'

clean:
	rm -f lox
