CC = gcc
CFLAGS = -g -Wall -Iinclude `sdl2-config --cflags`
CLIBS = `sdl2-config --libs` -lSDL2_ttf

SRC = $(wildcard src/*.c)
INC = $(wildcard include/*.h)
OBJ = $(SRC:src/%.c=build/%.o)

TARGET = bin/graphSim

build: $(TARGET)

$(TARGET): $(OBJ) $(INC) $(SRC)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET) $(CLIBS)

build/%.o: src/%.c $(INC) 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -fr build/*.o

run:
	#i3-msg workspace 4
	./$(TARGET)

debug:
	gdb --tui ./$(TARGET)
