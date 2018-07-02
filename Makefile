default: build

OBJ = main.o elements.o snakeGame.o player.o
DEPS = -lncurses
output_name = snakesv
desktop_name = SnakeSV

build: clean $(OBJ)
	gcc $(OBJ) $(DEPS) -o $(output_name) && mkdir obj && mv *.o obj;
	chmod +x ./data/sc_script.sh && ./data/sc_script.sh;
	if [ -e ~/Desktop/$(desktop_name).desktop ]; then chmod +x ~/Desktop/$(desktop_name).desktop; fi;

main.o: src/main.c
	gcc -c src/main.c

elements.o: src/elements.c
	gcc -c src/elements.c

snakeGame.o: src/snakeGame.c
	gcc -c src/snakeGame.c

player.o: src/player.c
	gcc -c src/player.c

run: build
	if [ -e ./$(output_name ]; then ./$(output_name); fi;

clean:
	@[ -f ./obj/main.o ] && ( rm -r ./obj && rm $(output_name) ) || true;

purge: clean
	@[ -f ~/Desktop/$(desktop_name).desktop ] && rm ~/Desktop/$(desktop_name).desktop || true;
	if [ -d /usr/games/$(output_name) ]; then sudo rm -r /usr/games/$(output_name); fi;

help:
	echo "\n\t\tmake run = compile and run\n\t\tmake build = just compile"
