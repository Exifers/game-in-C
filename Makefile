CC=gcc
LDFLAGS= -lSDL2
CPPFLAGS= -I/usr/include/SDL2 -I.

NAME=game
SOURCES:=$(shell find $(SOURCEDIR) -name '*.c')

build:
	gcc \
	-g \
	main.c \
	structs/vector.c \
	structs/color.c \
	structs/entity.c \
	structs/scene.c \
	structs/events.c \
	scene/scene.c \
	globals/globals.c \
	io/window.c \
	io/screen.c \
	io/io.c \
	load/load.c \
	events/events.c \
	-I/usr/include/SDL2 -I. -lSDL2 -o game

run:
	./game
