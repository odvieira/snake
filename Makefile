default: run

OBJ = main.o elements.o snakeGame.o player.o
DEPS = -lncurses
output_name = snake
desktop_name = Snake

build: clean $(OBJ)
	@gcc -g $(OBJ) $(DEPS) -o $(output_name) && mkdir obj && mv *.o obj;

main.o: src/main.c
	@gcc -g -c src/main.c

elements.o: src/elements.c
	@gcc -g -c src/elements.c

snakeGame.o: src/snakeGame.c
	@gcc -g -c src/snakeGame.c

player.o: src/player.c
	@gcc -g -c src/player.c

run: build
	@if [ -e ./$(output_name) ]; then ./$(output_name); else /usr/games/$(output_name)/$(output_name); fi; make clean;

clean:
	@[ -f ./obj/main.o ] && ( rm -r ./obj && rm $(output_name) ) || true;

purge: clean
	@[ -f ~/Desktop/$(desktop_name).desktop ] && rm ~/Desktop/$(desktop_name).desktop || true;
	@if [ -d /usr/games/$(output_name) ]; then sudo rm -r /usr/games/$(output_name); fi;

help:
	@echo "make run: compile, run and clean\nmake build: just compile"
