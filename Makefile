default: build

OBJ = main.o elements.o snakeGame.o player.o
DEPS = -lncurses
output_name = snakesv

build: purge $(OBJ)
	gcc $(OBJ) $(DEPS) -o $(output_name) && mkdir obj && mv *.o obj;
	chmod +x ./data/sc_script.sh && ./data/sc_script.sh;
	chmod +x ~/Desktop/$(output_name).desktop;

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
	@[ -f ./obj/main.o ] && ( rm -r ./obj && rm $(output_name) ) || true;

purge: clean
	@[ -f ~/Desktop/$(output_name) ] && rm ~/Desktop/$(output_name).desktop || true;
	@[ -d usr/games/$(output_name) ] && sudo rm -r usr/games/$(output_name) || true;

help:
	echo "\n\t\tmake run = compile and run\n\t\tmake build = just compile"
