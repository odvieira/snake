default: build

OBJ = main.o elements.o snakeGame.o player.o
DEPS = -lncurses
output_name = snakeGame

build: $(OBJ)
	gcc $(OBJ) $(DEPS) -o $(output_name)

main.o: src/main.c
	gcc -c src/main.c

elements.o: src/elements.c
	gcc -c src/elements.c

snakeGame.o: src/snakeGame.c
	gcc -c src/snakeGame.c

player.o: src/player.c
	gcc -c src/player.c

run: build
	./$(output_name)

clean:
	rm $(output_name); rm *.o

purge:
	rm *.*; rm */*.*; rmdir *;

help:
	echo "\n\t\tmake run = compile and run\n\t\tmake build = just compile"