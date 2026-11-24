CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm -lm

SRC = langton_ant.c
OUT = a.exe

all:
	$(CC) $(SRC) $(CFLAGS) -o $(OUT) $(LIBS)

run: all
	./$(OUT)

clean:
	rm -rf a.exe