#!/bin/bash

echo "Build location:
1. Install to /usr/games/snakesv (with a desktop shortcut) [root permission will be required]
2. Just build here"

read input

if [ $input == 1 ]; then
	echo "[Desktop Entry]
Encoding=UTF-8
Name=Snake Game
Comment=Launch SnakeGame 1.0
Exec=gnome-terminal -e /usr/games/snakesv/snake
Icon=utilities-terminal
Terminal=true
Type=Application" >> sc.txt
	sudo mkdir /usr/games/snakesv
	sudo mkdir usr/games/snakesv/data
	sudo mv ./top_player_rec.snk /usr/games/snakesv/data/
	sudo mv ../snakesv /usr/games/snakesv/
	sudo mv ./sc.txt /home/$USER/Desktop/Snake\ SV.desktop
	exit 1
else
	echo "Builded!"
	exit 2
fi
