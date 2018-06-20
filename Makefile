default: build

OBJ = main.o elements.o snakeGame.o player.o
DEPS = -lncurses
output_name = snakeGame

build: clean $(OBJ)
	gcc $(OBJ) $(DEPS) -o $(output_name) && mkdir obj && mv *.o obj;

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
	@[ -f ./obj/main.o ] && (rm -r obj && rm $(output_name)) || true

purge:
	@[ -f ./snakeGame ] && rm -r * || true

help:
	echo "\n\t\tmake run = compile and run\n\t\tmake build = just compile"
