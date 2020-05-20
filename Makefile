
build:
	gcc main.c \
	structs/vector.c \
	structs/color.c \
	structs/entity.c \
	structs/scene.c \
	structs/events.c \
	scene/scene.c \
	io/window.c \
	io/screen.c \
	io/io.c \
	load/load.c \
	-I/usr/include/SDL2 -I. -lSDL2 -o game

run:
	./game
