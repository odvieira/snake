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
Exec=gnome-terminal -e /usr/games/snakesv/snakesv
Icon=utilities-terminal
Terminal=true
Type=Application" >> sc.txt
	if [ ! -d /usr/games/snakesv ]; then
		sudo mkdir /usr/games/snakesv
	fi
	sudo cp -r ./* /usr/games/snakesv
	rm -r ./obj && rm snakesv
	sudo mv ./sc.txt /home/$USER/Desktop/SnakeSV.desktop
else
	echo "Builded!"
fi
